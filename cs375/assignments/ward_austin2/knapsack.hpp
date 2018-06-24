#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::pair<int, int> item;

class Knapsack {
    public:
        Knapsack(item** items, int size, int capacity);
        void kwf();
        void execute(int index, int profit, int curWeight);
        void print(const std::string &outfile);
    private:
        bool promising(int i, int weight, int profit);
        int kwfAux(int index, int weight, int profit);
        double bound;
        int visited;
        int maxProfit;
        int leafVisits;
        int size;
        int capacity;
        item* items;
        std::vector<int> numbest;
        std::vector<std::string> include;
};
#endif
