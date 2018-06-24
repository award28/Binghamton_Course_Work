#include "cache.hpp"

SA::SA(const std::vector<instruction>& traces, bool prefetch, bool write, bool onMiss) {
    this->traces = traces;
    this->prefetch = prefetch;
    this->write = write;
    this->onMiss = onMiss;
}

void SA::execute(unsigned long long assoc) {
    this->hits = 0;
    this->total = 0;
    this->assoc = assoc;
    this->capacityPer = ceil((size / 32) / assoc);
    this->sets.reserve(this->capacityPer);

    for(unsigned long long i = 0; i < this->capacityPer; i++)
        this->sets.push_back(Set(assoc));

    unsigned long long addr;

    for(auto trace : this->traces) {
        addr = trace.second/32;

        if(check(addr, trace.first, true))
            this->hits++;
        this->total++;
    }
}

bool SA::check(unsigned long long addr, bool store, bool head) {
    unsigned long long tag, set;
    bool res;

    unsigned int mask = 0;

    for(int i = log2(this->capacityPer); i <= 27; i++)
        mask |= 1 << i;

    tag = (addr & mask);
    set = (addr % this->capacityPer);

    //std::cout << set << " " << tag << std::endl;

    if(!set)
        set = this->capacityPer - 1;
    else
        set--;

    if(store && this->write) 
        res = this->sets.at(set).inCache(tag, true, this->total);
    else
        res = this->sets.at(set).inCache(tag, true, this->total);

    if(head) {
        if(res) {
            if(this->prefetch && !this->onMiss) 
                check(addr, false, false);
        }
        else if(this->prefetch)
            check(addr, false, false);
    }

    return res;
}
