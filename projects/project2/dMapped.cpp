#include "cache.hpp"

DMapped::DMapped(const std::vector<memInstruction>& trace) {
    this->trace = trace;
}

void DMapped::execute(unsigned int size) {
    this->numHits = 0;
    this->numMisses = 0;
    this->size = size;
    this->capacity = size / 32;
    this->cache.resize(capacity);
    std::fill(this->cache.begin(), this->cache.begin() + capacity, -1);

    unsigned int tag;

    for (auto trace : this->trace) {
        tag = trace.second >> 5;
        unsigned int &entry = this->cache.at(tag % this->capacity);         
        if(tag == entry)
            numHits++;
        else {
            numMisses++;
            entry = tag;
        }
    }
}
