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
    cout << "Commands: path, exit" << endl;
    while(true){
        cout << "Enter command: ";
        string command;
        cin >> command;
        if(command == "exit"){
            break;
        }else if(command != "path"){
            cout << "Command not recognized, try again" << endl;
            continue;
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
        
        vector<string> stops = minStops(srcID, desID, airports);
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
        cout << endl;

    }


    return 0;
}