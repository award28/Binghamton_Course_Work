#include <iostream>
#include "BSTree.hpp"

using std::cout;
using std::cin;
using std::endl;

int main() {
    BSTree *tree1 = new BSTree();
    cout << "Tree is empty: " << tree1->empty() << endl;
    cout << "Inserting 5: " << tree1->insert(5) << endl;
    cout << "Inserting 10: " << tree1->insert(10) << endl;
    cout << "Inserting 8: " << tree1->insert(8) << endl;
    cout << "Inserting 7: " << tree1->insert(7) << endl;
    cout << "Inserting 9: " << tree1->insert(9) << endl;
    cout << "Inserting 11: " << tree1->insert(11) << endl;
    cout << "Find 5: " << tree1->find(5) << endl;
    cout << "Find 1: " << tree1->find(12) << endl;
    cout << "Find 12: " << tree1->find(12) << endl;

}
