#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP
#include <iostream>
#include <fstream>
#include <string>

typedef std::pair<int, int> item;

class Knapsack {
    public:
        Knapsack(item** items, int size, int capacity);
        void execute();
    private:
        int visited;
        int leafVisits;
        int size;
        int capacity;
        item* items;
};
#endif
