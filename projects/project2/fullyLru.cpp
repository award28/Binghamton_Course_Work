#include "cache.hpp"

FullyLRU::FullyLRU(const std::vector<instruction>& traces) {
    this->traces = traces;
}
void FullyLRU::execute() {
    for (auto trace : this->traces) {
        if (cache->inCache(trace.second/32, true)) 
            this->hits++;
        this->total++;
    }
}
