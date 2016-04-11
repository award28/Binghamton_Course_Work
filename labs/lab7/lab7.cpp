#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include "BSTree.hpp"
using namespace std;

void printList(vector<int> &list){
	for(unsigned int i = 0; i < list.size(); i++)
		cerr << " [" << list[i] << "] ";
	cerr << endl;
}

int main(){
	srand(time(NULL));
  	cerr << "\n\tTEST #0: Passes all tests from Lab 6" << endl;
	BSTree tree;
	assert(tree.empty());
	int array[] = {5,3,10,4,8,2,1,7,9,6,12,11,13};
	for(unsigned int i = 0; i < sizeof(array)/sizeof(int); i++){
		tree.insert(array[i]);
    	assert(!tree.empty());
	}
	//retest inserting duplicate values
	for(int i = 0; i < 8; i++){
		assert(!tree.insert(array[i]));
	}
	for(int i = 1; i <= 14; i++){
		if(i != 14){
			assert(tree.find(i));
		}else
			assert(!tree.find(i));
	}
	BSTree tree3;
	assert(!tree3.find(1));
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #1: Cannot remove node that is not in the tree" << endl;
	assert(!tree.remove(25));
	vector<int> test1;
	tree.sortedArray(test1);
	printList(test1);
	assert(test1.size() == 13);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #2: Remove a leaf node" << endl;
	assert(tree.remove(1));
	vector<int> test2;
    tree.sortedArray(test2);
	printList(test2);
	assert(test2.size() == 12);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #3: Remove single branch using the Short Circuit algorithm" << endl;
	assert(tree.remove(7));
    vector<int> test3;
    tree.sortedArray(test3);
	printList(test3);
	assert(test3.size() == 11);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "Test #4: Remove two branch node promoting a leaf node" << endl;
	assert(tree.remove(10));
	vector<int> test4;
	tree.sortedArray(test4);
	printList(test4);
	assert(test4.size() == 10);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #5: Remove two branch node promoting a 1 branch node using Short Circuit" << endl;
	assert(tree.remove(11));
	vector<int> test5;
	tree.sortedArray(test5);
	printList(test5);
	assert(test5.size() == 9);
	cerr << "\n\t========================PASS========================\n" << endl;

	

	cerr << "\n\tTEST #6: Remove root with two branches" << endl;
	assert(tree.remove(5));
	vector<int> test6;
	tree.sortedArray(test6);
	printList(test6);
	assert(test6.size() == 8);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #7: Remove root with one branch" << endl;
	assert(tree.remove(3));
	assert(tree.remove(4));
	assert(tree.remove(2));
	assert(tree.remove(6));
	vector<int> test7;
	tree.sortedArray(test7);
	printList(test7);
	assert(test7.size() == 4);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #8: Remove root as leaf" << endl;
	assert(tree.remove(9));
    assert(tree.remove(8));
	assert(tree.remove(13));
	assert(tree.remove(12));
	vector<int> test8;
    for(int i = 1; i < 14; i++) if(tree.find(i) == 1) cout << i << " ";
    cout << endl;
    tree.sortedArray(test8);
	printList(test8);
	assert(test8.size() == 0);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #9: Deep copy for a tree of 100 random values" << endl;
	for(int i = 0; i < 100; i++){
		int value = rand() % 1000;
		tree.insert(value);
	}

	BSTree * copyTree = new BSTree(tree);
	vector<int> test9, test9Copy;
	tree.sortedArray(test9);
	copyTree->sortedArray(test9Copy);
	assert(test9Copy == test9);
	cerr << "\n\t========================PASS========================\n" << endl;

	cerr << "\n\tTEST #10: Test deletion and Destructor" << endl;
	for(int i = 0; i < 1000; i++){
		tree.remove(i);
	}
	assert(tree.empty());
	delete copyTree;
	cerr << "\n\t========================PASS========================\n" << endl;

	return 0;
}
