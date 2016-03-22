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
	int array[] = {5,3,8,2,1,7,9,6};
	for(int i = 0; i < 8; i++){
		tree.insert(array[i]);
    assert(!tree.empty());
	}
	cout << "\tPASS" << endl;

  cout << "Test #3: Cannot insert duplicate values into the Tree" << endl;
	for(int i = 0; i < 8; i++){
		assert(!tree.insert(array[i]));
	}
	cout << "\tPASS" << endl;


  cout << "Test #4: Insert 1000 Values into the Tree" << endl;
	BSTree tree2;
	for(int i = 0; i < 1000; i++){
		int value = rand() % 10000; 
		tree2.insert(value);
	}
  cout << "\tPASS" << endl;

  cout << "Test #5: Find values in the tree" << endl;
	for(int i = 1; i <= 9; i++){
		if(i != 4)
			assert(tree.find(i));
		else
			assert(!tree.find(i));
	}
	cout << "\tPASS" << endl;

  cout << "Test #6: Find doesn't segfault on empty tree" << endl;
	BSTree tree3;
	assert(!tree3.find(1));
	cout << "\tPASS" << endl;

	return 0;
}
