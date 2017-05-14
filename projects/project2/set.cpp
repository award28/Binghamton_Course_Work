#include "cache.hpp"

#define MAX_UINT 184400000000000000

Set::Set(unsigned long long size) {
    this->size = size;
    this->blocks.reserve(size);
    this->counter = 0;

    for(unsigned long long i = 0; i < size; i++)
        this->blocks.push_back(std::make_pair(0, MAX_UINT));
}

bool Set::inCache(unsigned long long tag, bool replace, unsigned long long count) {
    for(auto block : this->blocks) {
        if(tag == block.second) {
            this->counter++;
            count++;
            block.first = count;
            return true;
        }
    }

    if(replace)
        replaceBlock(tag, count);

    return false;
}

void Set::replaceBlock(unsigned long long tag, unsigned long long count) {
    std::pair<unsigned long long, unsigned long long> lru = std::make_pair(MAX_UINT, 0);

    for(auto block : this->blocks)
        if(block.first < lru.first)
            lru = block;

    unsigned long long pos = std::find(this->blocks.begin(), this->blocks.end(), lru) - this->blocks.begin();

    this->counter++;
    count++;
    this->blocks.at(pos) = std::make_pair(count, tag);
}
