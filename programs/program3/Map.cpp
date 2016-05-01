#include <iostream>
#include <fstream>
#include <cmath>
#include "Map.hpp"
using std::string;
using std::cout;
using std::endl;

Map::Map(string filename) {
    std::ifstream fin;
    string name = "";
    int x, y;
    City *west, *east, *north, *south;

    fin.open(filename);

    while(fin >> name >> x >> y) cities.push_back(new City(name, x, y));

    for(auto it:cities) {
        west = new City("", -1, -1);
        east = new City("", -1, -1);
        north = new City("", -1, -1);
        south = new City("", -1, -1);
        for(auto add:cities) {
            if(it->getName() != add->getName()) {
                if(it->getYCoor() == add->getYCoor()) {
                    if(it->getXCoor() - add->getXCoor() < 0) {
                        if(west->getXCoor() == -1) west = add;
                        else if(it->getXCoor() - west->getXCoor() < it->getXCoor() - add->getXCoor()) west = add;
                    }
                    if(it->getXCoor() - add->getXCoor() > 0) {
                        if(east->getXCoor() == -1) east = add;
                        else if(east->getXCoor() - it->getXCoor() < add->getXCoor() - it->getXCoor()) east = add;
                    }
                }
                if(it->getXCoor() == add->getXCoor()) {
                    if(it->getYCoor() - add->getYCoor() < 0) {
                        if(west->getYCoor() == -1) north = add;
                        else if(it->getYCoor() - west->getYCoor() > it->getYCoor() - add->getYCoor()) north = add;
                    }
                    if(it->getYCoor() - add->getYCoor() > 0) {
                        if(east->getYCoor() == -1) south = add;
                        else if(east->getYCoor() - it->getYCoor() > add->getYCoor() - it->getYCoor()) south = add;
                    }
                }
            }
        }
        if(west->getXCoor() != -1) it->setAdjacent(west);
        if(east->getXCoor() != -1) it->setAdjacent(east);
        if(north->getXCoor() != -1) it->setAdjacent(north);
        if(south->getXCoor() != -1) it->setAdjacent(south);
    }
}

City* Map::findByName(string cityName) {
    for(auto it:cities) if(cityName == it->getName()) return it;
    return NULL;
}
