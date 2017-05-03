#include "cache.hpp"

FullyHot::FullyHot(const std::vector<instruction>& traces) {
    this->traces = traces;
    this->cache.resize((16 * 1024)/32);

    std::fill(this->cache.begin(), this->cache.end() + ((16 * 1024) / 32), std::make_pair(false, 0));

    for(unsigned long long i = 0; i < this->cache.size(); i++)
        replace(0);
}

void FullyHot::execute() {

    for(auto trace : this->traces) {
        if(inCache(trace.second/32))
            this->hits++;
        this->total++;
    }
}

bool FullyHot::inCache(unsigned long long tag) {
    for (unsigned long long i = 0; i < this->cache.size(); i++) {
        if (this->cache.at(i).second == tag) {
            access(i);
            return true;
        }
    }
    replace(tag);
    return false;
}

void FullyHot::access(unsigned long long loc) {
    unsigned long long begin = 0;
    unsigned long long end = this->cache.size() - 1;
    unsigned long long cur = (begin + end) / 2;

    while(begin + 1 != end) {
        if(cur < loc) {
            begin = cur;
            this->cache.at(cur).first = true;
        } 
        else {
            end = cur;
            this->cache.at(cur).first = false;
        }
        cur = (begin + end) / 2;
    }

    if(cur < loc)
        this->cache.at(cur).first = true;
    else
        this->cache.at(cur).first = false;
}

unsigned long long FullyHot::findSwap() {
    unsigned long long begin = 0;
    unsigned long long end = this->cache.size() - 1;
    unsigned long long cur = (begin + end) / 2;

    while(cur != begin && cur != end) {
        if (this->cache.at(cur).first)
            end = cur;
        else 
            begin = cur;

        cur = (begin + end) / 2;
    }

    if (this->cache.at(cur).first)
        return cur;
    else
        return cur + 1;
}

void FullyHot::replace(unsigned long long tag) {
    unsigned long long pos = findSwap();
    this->cache.at(pos).second = tag;
    access(pos);
}
