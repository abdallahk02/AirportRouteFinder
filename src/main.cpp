#include <iostream>
#include <string>
#include <unordered_map>
#include "Airport.h"
#include "Parser.h"


using namespace std;

int main(){
    // unordered_map<int, Airport> airports;
    // unordered_map<string, int> nametoID;

    // loadAirports("data/airports.csv", airports, nametoID);

    // if(airports.empty()){
    //     cout << "Error: No aiports loaded" << endl;
    // }
    
    // loadRoutes("data/routes.csv", airports);

    
    // // Testing minDist:
    // std::vector<std::string> path;
    // int srcID;
    // int desID;


    // std::cout << "JFK->LHR" << std::endl;

    // srcID = nametoID["JFK"];
    // desID = nametoID["LHR"];

    // double distance;
    // path = minDist(srcID, desID, airports, distance);

    // if(path[0] == "404"){
    //     std::cout << "No path found" << std::endl;
    // }else{
    //     std::cout << "Path: ";
    //     for(size_t i = 0; i < path.size(); i++){
    //         if(i == path.size()-1){
    //             std::cout << path[i] << std::endl;
    //         }else{
    //             std::cout << path[i] << "->";
    //         }
    //     }
    // }

    // std::cout << "Total distance: " << distance << std::endl;

    // std::cout << "CDG->LHR" << std::endl;

    // srcID = nametoID["CDG"];
    // desID = nametoID["LHR"];

    // path = minDist(srcID, desID, airports);

    // if(path[0] == "404"){
    //     std::cout << "No path found" << std::endl;
    // }else{
    //     std::cout << "Path: ";
    //     for(size_t i = 0; i < path.size(); i++){
    //         if(i == path.size()-1){
    //             std::cout << path[i] << std::endl;
    //         }else{
    //             std::cout << path[i] << "->";
    //         }
    //     }
    // }
    // std::cout << "ATL->ORD" << std::endl;

    // srcID = nametoID["ATL"];
    // desID = nametoID["ORD"];

    // path = minDist(srcID, desID, airports);

    // if(path[0] == "404"){
    //     std::cout << "No path found" << std::endl;
    // }else{
    //     std::cout << "Path: ";
    //     for(size_t i = 0; i < path.size(); i++){
    //         if(i == path.size()-1){
    //             std::cout << path[i] << std::endl;
    //         }else{
    //             std::cout << path[i] << "->";
    //         }
    //     }
    // }
    // std::cout << "JFK->JFK" << std::endl;

    // srcID = nametoID["JFK"];
    // desID = nametoID["JFK"];

    // path = minDist(srcID, desID, airports);

    // if(path[0] == "404"){
    //     std::cout << "No path found" << std::endl;
    // }else{
    //     std::cout << "Path: ";
    //     for(size_t i = 0; i < path.size(); i++){
    //         if(i == path.size()-1){
    //             std::cout << path[i] << std::endl;
    //         }else{
    //             std::cout << path[i] << "->";
    //         }
    //     }
    // }

    // std::cout << "OSU->JFK" << std::endl;

    // srcID = nametoID["OSU"];
    // desID = nametoID["JFK"];

    // path = minDist(srcID, desID, airports);

    // if(path[0] == "404"){
    //     std::cout << "No path found" << std::endl;
    // }else{
    //     std::cout << "Path: ";
    //     for(size_t i = 0; i < path.size(); i++){
    //         if(i == path.size()-1){
    //             std::cout << path[i] << std::endl;
    //         }else{
    //             std::cout << path[i] << "->";
    //         }
    //     }
    // }
    



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
