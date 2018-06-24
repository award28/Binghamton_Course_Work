#include "replacements.hpp"

Opt::Opt(int arr[]) {
    for(int i = 0; i < numAccesses; i++)
        this->accessed[i]  = arr[i];
}

std::string Opt::execute(int cache) {
    int table[cache];
    int numFuture[100];
    
    int hit = 0;
    int lowInd = 0;
    int freeSpots = cache;
    double hitp;
    bool found;

    std::fill_n(table, cache, 0);
    std::fill_n(numFuture, 100, 0);

    for(int i = 0; i < numAccesses; i++)
        numFuture[this->accessed[i] - 1]++;

    for(int i = 0; i < numAccesses; i++) {
        found = false;
        lowInd = 0;

        numFuture[this->accessed[i] - 1]--;
        
        for(int j = 0; j < cache && !found; j++)
            found = (this->accessed[i] == table[j]);

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
            else {
                for(int j = 0; j < cache; j++) {
                    if(numFuture[table[lowInd] - 1] >= numFuture[table[j] - 1])
                        lowInd = j;
                }
                table[lowInd] = this->accessed[i];
            }
        }
        else 
            hit++;
    }

    hitp = (hit/(double)numAccesses) * 100;
    return std::to_string(hitp);
}
