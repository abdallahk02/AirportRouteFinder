#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Parser.h"
#include "Airport.h"
#include "Algorithm.h"


void loadAirports(std::string filename, std::unordered_map<int, Airport>& airports, std::unordered_map<std::string, int>& nametoID){
    std::ifstream file(filename);  
    std::string line;
    int row_num = 1;    // row tracking for debugging
    while(std::getline(file, line)){
        
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> row;
        
        while(std::getline(ss, value, ',')){    // get row data split by comma
            row.push_back(value);
        }

        if(row.size() == 14){   // check if row has all 14 elements
            if(!row[0].empty() && !row[6].empty() && !row[7].empty()){  // check if critical data is missing
                try{
                    Airport a;
                    a.id = std::stoi(row[0]);
                    a.name = row[1];
                    a.code = row[4];
                    a.latitude = std::stod(row[6]);
                    a.longitude = std::stod(row[7]);
                    airports[a.id] = a;
                    nametoID[row[4]] = a.id;
                }catch(const std::exception& e){
                    // std::cout << "loadAirports: data type conversion failed on row " << row_num << std::endl;
                    continue;
                }
            }
        }
        row_num++;
    }
    
}

void loadRoutes(std::string filename, std::unordered_map<int, Airport>& airports){
    std::ifstream file(filename);
    std::string line;
    int row_num = 1;    // row tracking for debugging

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string value;
        std::vector<std::string> row;
        
        while(std::getline(ss, value, ',')){    // get row data split by comma
            row.push_back(value);
        }

        if(row.size() == 7){
            try{
                // get source and destination
                int srcID = std::stoi(row[3]);
                int desID = std::stoi(row[5]);
                
                // calculate distance
                double distance = calculateHaversine(airports[srcID].latitude, airports[srcID].longitude, 
                                                        airports[desID].latitude, airports[desID].longitude);
                
                // link route to airport
                airports[srcID].routes.push_back({desID, distance});

            }catch(const std::exception& e){
                std::cout << "loadRoutes: data type error on row " << row_num << std::endl;
            }
        }else{
            std::cout << "loadRoutes: missing columns on row " << row_num << std::endl;
        }

        row_num++;
    }
}