#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "BSTree.hpp"
using namespace std;

int main(){

  cout << "Test #1: Create an empty tree" << endl;
	BSTree tree;
	assert(tree.empty());
	cout << "\tPASS" << endl;

  cout << "Test #2: Insert values into the Tree" << endl;
	int array[] = {500, 300, 700, 200, 400, 600, 800, 550, 650, 900, 530, 580, 670, 560, 595, 590, 585, 593};
	for(int i = 0; i < 19; i++){
		tree.insert(array[i]);
    assert(!tree.empty());
	}
	cout << "\tPASS" << endl;

    cout << "Test #3: Delete a node" << endl;
    cout << "Delete 600: " << tree.remove(600) << endl;
    cout << "Find 600: " << tree.find(600) << endl;
    cout << "Find 593: " << tree.find(593) << endl;
    cout << "\tPASS" << endl;
	return 0;
}
