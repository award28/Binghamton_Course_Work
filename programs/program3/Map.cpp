#include <iostream>
#include <fstream>
#include "Map.hpp"
using std::string;

Map::Map(string filename) {
    std::ifstream fin;
    string name;
    int x, y;

    fin.open(filename);

    while(!fin.eof()) {
        fin >> name >> x >> y;
        cities.push_back(new City(name, x, y));
    }

}

City* Map::findByName(string cityName) {
    for(auto it:cities) if(cityName == it->getName()) return it;
    return NULL;
}
