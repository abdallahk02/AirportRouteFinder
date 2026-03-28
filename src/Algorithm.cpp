#include "Algorithm.h"
#include <queue>
#include <iostream>
#include <algorithm>

double calculateHaversine(double lat1, double lon1, double lat2, double lon2) {
    // Earth's radius in kilometers
    const double R = 6371.0; 

    // Convert degrees to radians
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double rLat1 = lat1 * M_PI / 180.0;
    double rLat2 = lat2 * M_PI / 180.0;

    // Haversine formula
    double a = std::pow(std::sin(dLat / 2), 2) +
               std::cos(rLat1) * std::cos(rLat2) *
               std::pow(std::sin(dLon / 2), 2);
    
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c;
}

std::vector<std::string> minStops(int srcID, int desID, std::unordered_map<int, Airport> airports){
    std::vector<std::string> stops;

    std::unordered_map<int, int> parents;   // map to track path and visited
    parents[srcID] = -1;

    std::queue<int> q;  
    q.push(srcID);
    bool pathFound = false;
    
    while(!q.empty() && !pathFound){
        int s = q.size();
        for(int i = 0; i < s; i++){
            if(pathFound){
                break;
            }
            
            int currID = q.front();
            q.pop();
            std::vector<std::pair<int, double>> routes = airports[currID].routes;

            for(size_t j = 0; j < routes.size(); j++){
                std::pair<int, double> p = routes[j];   
                                
                if(parents.find(p.first) != parents.end()){     // airport already checked
                    continue; 
                }
        
                parents[p.first] = airports[currID].id;    

                if(p.first == desID){   // destination found
                    pathFound = true;
                    break;
                }else{
                    q.push(p.first);  // search further
                }
            }
        }
    }

    if(parents.find(desID) == parents.end()){
        return {"404"};
    } 

    int stopID = desID;
    
    while(stopID != srcID){
        Airport stop = airports[stopID];
        std::string stopCode = stop.code;
        stops.push_back(stopCode);
        stopID = parents[stopID];
        if(stopID == srcID){
            std::string srcCode = airports[srcID].code;
            stops.push_back(srcCode);
        }
    }
    std::reverse(stops.begin(), stops.end());

    return stops;
}

std::vector<std::string> minDist(int srcID, int desID, std::unordered_map<int, Airport> airports){
    std::vector<std::string> stops;

    // Priority calculation (g+h) - distance from start + remaining distance estimate
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> fScores; 
    // Map aiport n to g(n) - distance from start
    std::unordered_map<int, double> gScores;
    // Starting heuristic 
    int h_start = calculateHaversine(airports[srcID].latitude, airports[srcID].longitude, airports[desID].latitude, airports[desID].longitude);
    // Path reconstruction
    std::unordered_map<int, int> previous;
    std::unordered_set<int> visited;

    bool pathFound = false;

    fScores.push({h_start, srcID});
    gScores[srcID] = 0;

    while(!fScores.empty()){
        std::pair<int, int> p = fScores.top();
        Airport current = airports[p.second];
        fScores.pop();

        if(visited.find(current.id) != visited.end()){
            continue;
        }else{
            visited.insert(current.id);
        }

        if(current.id == desID){
            // Found end of path
            pathFound = true;
            break;
        }

        std::vector<std::pair<int, double>> neighbors = airports[current.id].routes;
        for(size_t i = 0; i < neighbors.size(); i++){
            Airport n = airports[neighbors[i].first];
            double n_g = gScores[current.id] + neighbors[i].second;
            if(gScores.find(n.id) == gScores.end() || gScores[n.id] > n_g){ // Found new or shorter path to n
                gScores[n.id] = n_g;
                double n_h = calculateHaversine(airports[desID].latitude, airports[desID].longitude, n.latitude, n.longitude);
                double n_f = n_g+n_h;
                fScores.push({n_f,n.id});
                previous[n.id] = current.id;
            }
        }


    }

    if(!pathFound) return {"404"};

    int stopID = desID;

    while(stopID != srcID){
        stops.push_back(airports[stopID].code);
        stopID = previous[stopID];
    }
    stops.push_back(airports[srcID].code);
    std::reverse(stops.begin(), stops.end());

    return stops;
}
