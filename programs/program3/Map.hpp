#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <vector>
#include "City.hpp"

class Map {
    private:
        std::vector<City*> cities;
    public:
        Map(std::string filename);
        City* findByName(std::string cityName);
};
#endif
