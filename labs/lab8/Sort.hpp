#ifndef SORT_HPP
#define SORT_HPP
#include <iostream>

class sort {
    private:
        int *heapsort(int *a, int size);
        int *mergesort(int *a, int size);
        int *quicksort(int *array, int high, int low);
    public:
        int *sortA(int *a, int size);
        int *sortB(int *b, int size);
        int *sortOptimized(int *o, int size);
};
#endif
