#ifndef REPLACEMENTS_HPP
#define REPLACEMENTS_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#define numAccesses 10000

class Rand {
    public:
        Rand(int arr[]);
        std::string execute(int cache);
    private:
        int accessed[numAccesses];
};

class Fifo {
    public:
        Fifo(int arr[]);
        std::string execute(int cache);
    private:
        int accessed[numAccesses];
};

class Opt {
    public:
        Opt(int arr[]);
        std::string execute(int cache);
    private:
        int accessed[numAccesses];
};

class Lru {
    public:
        Lru(int arr[]);
        std::string execute(int cache);
    private:
        int accessed[numAccesses];
};

class Clock {
    public:
        Clock(int arr[]);
        std::string execute(int cache);
    private:
        int accessed[numAccesses];
};
#endif
