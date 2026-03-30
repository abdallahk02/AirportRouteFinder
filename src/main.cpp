#include <iostream>
#include <string>
#include <unordered_map>
#include "Airport.h"
#include "Parser.h"


using namespace std;

int main(){
    cout << "----AIRPORT FLIGHT SIMULATOR----" << endl;


    unordered_map<int, Airport> airports;
    unordered_map<string, int> nametoID;

    loadAirports("data/airports.csv", airports, nametoID);

    if(airports.empty()){
        cout << "Error: No aiports loaded" << endl;
    }
    
    loadRoutes("data/routes.csv", airports);

    string srcInput;
    string desInput;
    cout << "--------------------------------" << endl;
    cout << "Commands:" << endl;
    cout << "1: Fewest stops" << endl;
    cout << "2: Shortest distance" << endl;
    cout << "3: Exit" << endl;
    cout << "--------------------------------" << endl;
    while(true){
        cout << endl << "Enter command: ";
        string command;
        cin >> command;
        if(command == "3"){
            break;
        }
        
        cout << "Source airport (3-letter code): ";
        cin >> srcInput;
        if(nametoID.find(srcInput) == nametoID.end()){
            cout << "Sorry, " << srcInput << " not found. Try again :)" << endl;
            continue;
        }
        cout << "Destination airport (3-letter code): ";
        cin >> desInput;
        if(nametoID.find(desInput) == nametoID.end()){
            cout << "Sorry, " << desInput << " not found. Try again :)" << endl;
            continue;
        }else if(srcInput == desInput){
            cout << "Invalid input" << endl;
            continue;
        }
        cout << endl;
        int srcID = nametoID[srcInput];
        int desID = nametoID[desInput];

        vector<string> stops;
        double distance = 0;

        if(command == "1"){stops = minStops(srcID, desID, airports, distance);}
        else{stops = minDist(srcID, desID, airports, distance);}

        if(stops[0] == "404"){
            cout << "No path found" << endl;
            continue;
        }else if (stops.size()==2){
            cout << "Direct route found: ";
        }else{
            cout << stops.size()-2 << " stop route found: ";
        }
        
        for(size_t i = 0; i < stops.size(); i++){
            if(i!=0){
                cout << " -> ";
            }
            cout << stops[i];
        }
        cout << endl << "Total travel distance: " << distance << " km" << endl;

    }


    return 0;
}
