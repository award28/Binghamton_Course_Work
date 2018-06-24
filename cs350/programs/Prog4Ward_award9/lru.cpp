#include <list>

#include "replacements.hpp"

Lru::Lru(int arr[]) {
    for(int i = 0; i < numAccesses; i++)
        this->accessed[i]  = arr[i];
}

std::string Lru::execute(int cache) {
    std::list<int> table;
    
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
        else {
            table.remove(this->accessed[i]);
            table.push_front(this->accessed[i]);
            hit++;
        }
    }

    hitp = (hit/(double)numAccesses) * 100;
    return std::to_string(hitp);
}
