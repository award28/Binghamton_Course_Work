#include "cache.hpp"

Direct::Direct(const std::vector<instruction>& traces) {
    this->traces = traces;
}

void Direct::execute(unsigned long long size) {
    this->hits = 0;
    this->total = 0;
    this->size = size;
    this->capacity = size / 32;
    this->cache.resize(capacity);
    std::fill(this->cache.begin(), this->cache.begin() + capacity, -1);

    unsigned long long tag;

    for (auto trace : this->traces) {
        tag = trace.second >> 5;
        unsigned long long &entry = this->cache.at(tag % this->capacity);         
        if(tag == entry)
            this->hits++;
        else 
            entry = tag;

        this->total++;
    }
}
