#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include "City.hpp"

class Map {
    private:
        std::vector<City*> cities;
    public:
        Map(std::string filename);
        City* findByName(std::string cityName);
        std::vector<City *> shortestPath(City * start, City * dest);
        unsigned int pathDistance(City * start, City * dest);
};
#endif
