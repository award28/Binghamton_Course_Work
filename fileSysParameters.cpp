#include <deque>

#include "replacements.hpp"
Fifo::Fifo(int arr[]) {
    for(int i = 0; i < numAccesses; i++)
        this->accessed[i]  = arr[i];
}

std::string Fifo::execute(int cache) {
    std::deque<int> table;
    int hit = 0;
    double hitp;

    for(int i = 0; i < numAccesses; i++) {
        if(std::find(table.begin(), table.end(), this->accessed[i]) == table.end()) {
            if((int) table.size() < cache)
                table.push_front(this->accessed[i]);
            else {
                table.pop_back();
                table.push_front(this->accessed[i]);
            }
        }
        else 
            hit++;
    }

    hitp = (hit/(double)numAccesses) * 100;
    return std::to_string(hitp);
}
