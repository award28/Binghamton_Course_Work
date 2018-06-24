#include <random>

#include "replacements.hpp"

Rand::Rand(int arr[]) {
    for(int i = 0; i < numAccesses; i++)
        this->accessed[i]  = arr[i];
}

std::string Rand::execute(int cache) {
    int table[cache];
    int hit = 0;
    int random;
    int freeSpots = cache;
    time_t t;
    double hitp;
    bool found = false;

    std::fill_n(table, cache, 0);
    srand((unsigned) time(&t));

    for(int i = 0; i < numAccesses; i++) {
        random = rand() % cache;
        found = false;

        for(int j = 0; j < cache && !found; j++)
            found = (table[j] == this->accessed[i]);

        if(!found) {
            if(freeSpots) {
                for(int j = 0; j < cache && !found; j++) {
                    if(!table[j]) {
                        table[j] = this->accessed[i];
                        found = true;
                    }
                }
                freeSpots--;
            }
            else 
                table[random] = this->accessed[i];
        }
        else 
            hit++;
    }

    hitp = (hit/(double)numAccesses) * 100;
    return std::to_string(hitp);
}
