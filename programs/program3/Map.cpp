#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <list>
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
                        if(east->getXCoor() == -1) east = add;
                        else if(it->getXCoor() - east->getXCoor() < it->getXCoor() - add->getXCoor()) east = add;
                    }
                    if(it->getXCoor() - add->getXCoor() > 0) {
                        if(west->getXCoor() == -1) west = add;
                        else if(west->getXCoor() - it->getXCoor() < add->getXCoor() - it->getXCoor()) west = add;
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

std::vector<City *> Map::shortestPath(City * start, City * dest){
    City* visiting;
    std::vector<City*> visit(cities.size());
    std::list<City *> adj;
    cities.erase(find(cities.begin(), cities.end(), start));
    unsigned int alt;
    visit[0] = start;
    int j = 0;
    
    for(int i = 0; i < visit.size(); i++) {
        if(visit[i] != NULL) {
            adj = visit[i]->getAdjacent();
            for(auto it:adj) {
                if(find(visit.begin(), visit.end(), it) == visit.end()) {
                    j++;
                    visit[j] = it;
                    visit[j]->dist = INT_MAX;
                }
            }
        }
    }
    
    for(auto it:cities) {
        if(find(visit.begin(), visit.end(), it) == visit.end()) {
            j++;
            visit[j] = it;
            visit[j]->dist = INT_MAX;
        }
    }
    
    visit[0]->dist = 0;
    cities.push_back(start);
    while(!visit.empty()) {
        visiting = visit.front();
        visit.erase(visit.begin());
        adj = visiting->getAdjacent();
        for(auto it:adj) {
            alt = visiting->dist + pathDistance(visiting, it);
            if(alt < it->dist) {
                it->dist = alt;
                it->prev = visiting;
            }
        }
    }
    visiting = dest;
    
    if(dest->dist != INT_MAX) {
        while(visit[0] != start) {
            visit.insert(visit.begin(), visiting);
            visiting = visiting->prev;
        }
    }
    else visit.clear();

    for(auto it:visit) cout << it->getName() << endl;
    return visit;
}

unsigned int Map::pathDistance(City * start, City * dest){
    if(start->getXCoor() == dest->getXCoor()) return abs(start->getYCoor() - dest->getYCoor());
    if(start->getYCoor() == dest->getYCoor()) return abs(start->getXCoor() - dest->getXCoor());
    shortestPath(start, dest);
    if(dest->dist == INT_MAX) return -1;
    return dest->dist;
}
