#include "Sort.hpp"
#include <iostream>

using std::cout;
using std::endl;

int *Sort::sortA(int *a, int size) {
    return heapsort(a, size);
}

int *Sort::sortB(int *b, int size) {
    return mergesort(b, 0, size -1, size);
}

int *Sort::sortOptimized(int *a, int size) {
    quicksort(a, 0, size - 1);
    return a;
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

int *Sort::mergesort(int *a, int low, int high, int size) {
    int mid;
    
    if (low < high) {
        mid = (low + high)/2;
        mergesort(a, low, mid, size);
        mergesort(a, mid+1, high, size);
        merge(a, low, mid, high, size);
    }

    return a;
}

void Sort::merge(int *a, int low, int mid, int high, int size) {
    int i, j, k;
    int newA[size];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (a[i] < a[j]) {
            newA[k] = a[i];
            k++;
            i++;
        }
        else {
            newA[k] = a[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        newA[k] = a[i];
        k++;
        i++;
    }
    while (j <= high) {
        newA[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        a[i] = newA[i];
    }
}

void Sort::quicksort(int *a, int left, int right) {
    int temp;
    int i = left;
    int j = right;
    int pivot = a[median(a, left, right)];

    while(i <= j) {
        while(a[i] < pivot) i++;
        while(a[j] > pivot) j--;
        if(i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if(left < j) quicksort(a, left, j);
    if(i < right) quicksort(a, i, right);
}

int Sort::median(int *a, int left, int right) {
    int temp;
    int mid = (left + right)/2;
    
    if(a[right] < a[left]) {
        temp = a[left];
        a[left] = a[right];
        a[right] = temp;
    }
    if(a[mid] < a[left]) {
        temp = a[mid];
        a[mid] = a[left];
        a[left] = temp;
    }
    if(a[right] < a[mid]) {
        temp = a[right];
        a[right] = a[mid];
        a[mid] = temp;
    }

    return mid;
}
