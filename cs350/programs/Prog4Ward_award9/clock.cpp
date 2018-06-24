#include <vector>

#include "replacements.hpp"

typedef std::pair<int, bool> node;

Clock::Clock(int arr[]) {
    for(int i = 0; i < numAccesses; i++)
        this->accessed[i]  = arr[i];
}

std::string Clock::execute(int cache) {
    std::vector<node> table;
    
    int hit = 0;
    int hand = 0;
    double hitp;
    bool found;

    for(int i = 0; i < numAccesses; i++) {
        found = false;

        for(int j = 0; j < (int) table.size() && !found; j++) {
            if(table[j].first == this->accessed[i]) {
                found = true;
                table[j].second = true;
                hand = j;
            }
        }

        if(!found) {
            if((int) table.size() < cache) {
                table.push_back(std::make_pair(this->accessed[i], true));
                hand = table.size() - 1;
            }
            else {
                while(table[hand % cache].second) {
                    table[hand % cache].second = false;
                    hand++;
                }
                table[hand % cache].second = true;
                table[hand % cache].first = this->accessed[i];
                hand++;
            }
        }
        else {
            hit++;
        }
    }

    hitp = (hit/(double)numAccesses) * 100;
    return std::to_string(hitp);
}
