#ifndef CITY_HPP
#define CITY_HPP
#include <iostream>
#include <list>

class City {
    private:
        std::string cityName;
        int x;
        int y;
        std::list<City*> adjacent;
    public:
        City(std::string cityName, int xCoor, int yCoor);
        std::string getName();
        int getXCoor();
        int getYCoor();
        std::list<City*> getAdjacent();
        void setAdjacent(City* adj);
        bool operator<(City &c);
};
#endif
