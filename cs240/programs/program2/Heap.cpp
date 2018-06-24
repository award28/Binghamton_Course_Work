#include <iostream>
#include <fstream>
#include "Heap.hpp"

using std::string;
using std::vector;
using std::ifstream;

Heap::Heap(string fileName) {
    ifstream fin;
    string name;
    int budget;
    Player *p;
    bool inserted;

    fin.open(fileName);
    if(!fin.fail()) {
        while(std::getline(fin, name)) {
            fin >> budget;
            if(budget) {
                p = new Player(name, budget);
                if(this->players.empty()) this->players.push_back(*p);
                else {
                    inserted = false;

                    for(auto it = this->players.begin(); it != this->players.end() && !inserted; ++it) {
                        if(it->getBudget() < budget) {
                            this->players.insert(it, *p);
                            inserted = true;
                        }
                    }
                    if(!inserted) this->players.push_back(*p);
                }
            }
            fin.ignore(256, '\n');
        }
    }
    fin.close();
}

Heap::Heap(const Heap& copy) {
    for(auto it = copy.players.begin(); it != copy.players.end(); ++it) {
        this->players.insert(this->players.end(), *it);
    }
}

void Heap::addPlayer(Player newPlayer) {
bool inserted = false;

    for(auto it = this->players.begin(); it != this->players.end() && !inserted; ++it) {
        if(it->getBudget() < newPlayer.getBudget()) {
            this->players.insert(it, newPlayer);
            inserted = true;
        }
    }
    if(!inserted) this->players.push_back(newPlayer);
}

Player Heap::getPlayer() {
    if(!empty()) {
        Player retVal = this->players.front();
        this->players.erase(this->players.begin());
        return retVal;
    }
    else { 
        Player retVal("", 0);
        return retVal;
    }
}

vector<Player> Heap::getArray() {
    return this->players;
}

bool Heap::empty() {
    return this->players.empty();
}

unsigned int Heap::size() {
    return this->players.size();
}
