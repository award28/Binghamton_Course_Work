#include "Sort.hpp"
#include <iostream>

using std::cout;
using std::endl;

int *Sort::sortA(int *a, int size) {
    return heapsort(a, size);
}

int *Sort::sortB(int *b, int size) {
    return mergesort(b, size);
}

int *Sort::optimizedSort(int *o, int size) {
    return quicksort(o, o[0], o[size - 1]);
}

int *Sort::heapsort(int *a, int size) {
}

int *Sort::mergesort(int *a, int size) {
}

int *Sort::quicksort(int *array, int high, int low) {
}

