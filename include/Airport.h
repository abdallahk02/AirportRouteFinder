#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
#include <vector>


struct Airport{
    int id;
    std::string name;
    std::string code;
    double latitude;
    double longitude;
    std::unordered_map<int, double> routes;
};

#endif
