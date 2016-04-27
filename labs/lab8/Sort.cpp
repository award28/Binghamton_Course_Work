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

int *Sort::sortOptimized(int *o, int size) {
    return quicksort(o, o[0], o[size - 1]);
}

int *Sort::heapsort(int *a, int size) {
    int temp;
    //Build max heap
    for(int i = (size-2)/2; i >= 0; i--) siftdown(a, i, size);

    for(int i = size - 1; i >= 0; i--) {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        siftdown(a, 0, i);
    }
    return a;
}

void Sort::siftdown(int *a, int pos, int size) {
    if((pos < 0) || (pos >= size)) return;
    while(!isLeaf(pos, size)) {
        int j = (2*pos) + 1;
        if(j+1 < size && a[j] < a[j+1]) j++;
        if(a[pos] > a[j]) return;
        
        a[pos] ^= a[j];
        a[j] ^= a[pos];
        a[pos] ^= a[j];
        pos = j;
    }
}

bool Sort::isLeaf(int pos, int size) {
    if((2*pos) + 1 >= size && (2*pos) + 2 >= size) return true;
    return false;
}

int *Sort::mergesort(int *a, int size) {
}

int *Sort::quicksort(int *array, int high, int low) {
}
