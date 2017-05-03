#include "cache.hpp"

#define MAX_UINT 4294967295

Set::Set(unsigned long long size) {
    this->size = size;
    this->blocks.resize(size);
    this->counter = 0;

    std::fill(this->blocks.begin(), this->blocks.end() + size, std::make_pair(0, MAX_UINT));
}

bool Set::inCache(unsigned long long tag, bool replace) {
    bool found = false;

    for(auto block : this->blocks) {
        if(tag == block.second) {
            found = true;
            this->counter++;
            block.first = this->counter;
        }
    }

    if(replace)
        replaceBlock(tag);

    return found;
}

void Set::replaceBlock(unsigned long long tag) {
    std::pair<unsigned long long, unsigned long long> lru = std::make_pair(MAX_UINT, 0);

    for(auto block : this->blocks)
        if(block.first < lru.first)
            lru = block;

    unsigned long long pos = std::find(this->blocks.begin(), this->blocks.end(), lru) - this->blocks.begin();

    this->counter++;
    this->blocks.at(pos) = std::make_pair(this->counter, tag);
}
