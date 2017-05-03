#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

typedef std::pair<bool, unsigned long long> instruction;

class Direct {
    public:
        Direct(const std::vector<instruction>& traces);
        void execute(unsigned long long size);
        unsigned long long hits;
        unsigned long long total;

    private:
        std::vector<unsigned long long> cache;
        std::vector<instruction> traces;
        unsigned long long size;
        unsigned long long capacity;
};

class Set {
    public:
        Set(unsigned long long size);
        bool inCache(unsigned long long tag, bool replace);
        unsigned long long counter;
    private:
        std::vector<std::pair<unsigned long long, unsigned long long> > blocks;
        unsigned long long size;
        void replaceBlock(unsigned long long tag);
};

class SA {
    public:
        SA(const std::vector<instruction>& traces, bool prefetch, bool write, bool onMiss);
        void execute(unsigned long long size);
        unsigned long long hits;
        unsigned long long total;

    private:
        bool check(unsigned long long addr, bool store, bool head);
        std::vector<instruction> traces;
        std::vector<Set*> sets;
        unsigned long long size = 16 * 1024;
        unsigned long long capacityPer;
        unsigned long long assoc;
        bool prefetch;
        bool write;
        bool onMiss;
};

class FullyLRU {
    public:
        FullyLRU(const std::vector<instruction>& traces);
        void execute();
        unsigned long long hits;
        unsigned long long total;

    private:
        std::vector<instruction> traces;
        Set *cache = new Set((16 * 1024)/ 32);
};

class FullyHot {
    public:
        FullyHot(const std::vector<instruction>& traces);
        void execute();
        unsigned long long hits;
        unsigned long long total;

    private:
        typedef std::pair<bool, unsigned long long> hot;
        std::vector<instruction> traces;
        bool inCache(unsigned long long);
        void access(unsigned long long);
        unsigned long long findSwap();
        void replace(unsigned long long);
        std::vector<hot> cache;
};
#endif
