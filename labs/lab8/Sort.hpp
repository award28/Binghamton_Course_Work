#ifndef SORT_HPP
#define SORT_HPP
#include <iostream>

class Sort {
    private:
        int *heapsort(int *a, int size);
        void siftdown(int *a, int pos, int size);
        bool isLeaf(int pos, int size);
        int *mergesort(int *a, int low, int high, int size);
        void merge(int *a, int low, int mid, int high, int size);
        int *quicksort(int *array, int high, int low);
    public:
        int *sortA(int *a, int size);
        int *sortB(int *b, int size);
        int *sortOptimized(int *o, int size);
};
#endif
