#include <iostream>
#include "State.hpp" 

using std::string;

State::State(int id, string info) {
    this->id = id;
    this->info = info;
}

int State::getId() { return this->id; }

string State::getInfo() { return this->info; }
