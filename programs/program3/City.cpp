#include <iostream>
#include <cmath>
#include "City.hpp"

using std::cout;
using std::string;
using std::endl;
using std::cin;

City::City(string cityName, int xCoor, int yCoor) {
    this->cityName = cityName;
    this->x = xCoor;
    this->y = yCoor;
}

string City::getName() { return this->cityName; }
int City::getXCoor() { return this->x; }
int City::getYCoor() { return this->y; }

