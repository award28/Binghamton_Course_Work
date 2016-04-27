#include "Sort.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
    int size;
    Sort sorts;

    cout << "Enter first array size here: ";
    cin >> size;
    
    int a[size], *sorted;

    for(int i = 0; i < size; i++) {
        cout << "Enter element #" << i+1 << ": ";
        cin >> a[i];
    }
    
    cout << "\nSorting this array using heapsort:" << endl;
    sorted = sorts.sortB(a, size);
    
    for(int i = 0; i < size; i++) cout << sorted[i] << " ";
    cout << endl;

    return 0;
}
