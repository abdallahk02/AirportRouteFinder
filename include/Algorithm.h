#ifndef ALGORITHM_H
#define ALGORITHM_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "Airport.h"

// Returns distance in kilometers
double calculateHaversine(double lat1, double lon1, double lat2, double lon2);

std::vector<std::string> minStops(int srcID, int desID, std::unordered_map<int, Airport> airports);

std::vector<std::string> minDist(int srcID, int desID, std::unordered_map<int, Airport> airports);

#endif
