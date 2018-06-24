/*
 Classword 13: Insertion
 Write a single recursive method, insert, that inserts a value into your tree.
 Trace out your tree with the following values inserted in this order: 5, 8, 3, 6, 4, 2, 9, 1, 7
 What happens on the first insert when the tree is empty?
 What does your function need to do?
    How does this affect performance?
    How can you alter the method to avoid this problem?
*/

#include <iostream>

void insert(int num);

using namespace std;

int main () {


    int curNum;
    cout << "Enter the numbers to insert to your tree (Enter 1000 to stop): ";
    
    cin >> curNum;
    while(curNum != 1000) {
        insert(curNum);
        cin >> curNum;
    }
}

void insert(int num) {
    if(
