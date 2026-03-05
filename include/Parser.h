#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Airport.h"
#include "Algorithm.h"


void loadAirports(std::string filename, std::unordered_map<int, Airport>& airports, std::unordered_map<std::string, int>& nametoID);

void loadRoutes(std::string filename, std::unordered_map<int, Airport>& airports);


#endif