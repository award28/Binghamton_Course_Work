#include <iostream>
#include <fstream>
#include "Dog.h"

using namespace std;

int Dog::id = 0;

Dog::Dog(String name) {
    id++;
    unique_id = id;
}

void Dog::setBreed(String newBreed) {
    breed = newBreed;
};

String Dog::getBreed() {
    return breed;
}

void Dog::adopted() {
    fstream *myfile = new fstream;
    ifstream
    ofstream
                
    myfile -> open("adopted.log");
    myfile -> open("adopted.log", std::fstream::out | std::fstream::in | std::fstream::app);
    myfile << "Hello" << endl;
}
