#include <iostream>
#include "BSTree.hpp"

using std::cout;
using std::cin;
using std::endl;

bool BSTree::insert(int val) {
    if(empty()) {
        this->root = new BSTree::Node::Node(val);
        return true;
    }
    else {
        return insert(val, this->root);
    }
}

bool BSTree::insert(int val, BSTree::Node *current) {
    bool retVal = false;
    if(val > current->data && current->right == NULL) {
        current->right = new BSTree::Node::Node(val);
        retVal = true;
    }
    else if(val > current->data) retVal = insert(val, current->right);
    else if(val < current->data && current->left == NULL) {
        current->left = new BSTree::Node::Node(val);
        retVal = true;
    }
    else if(val < current->data) retVal = insert(val, current->left);
    if(current != NULL) cout << current->data << endl; 
    return retVal;
}

bool BSTree::find(int val) {
    if(empty()) return false;
    return find(val, this->root);
}

bool BSTree::find(int val, BSTree::Node *current) {
    bool retVal = false;

    if(current == NULL) retVal = false; 
    else if(val == current->right->data) retVal = true;
    else if(val == current->left->data) retVal = true;
    else if(val > current->data) retVal = find(val, current->right);
    else if(val < current->data) retVal = find(val, current->left);
    if(current != NULL) cout << current->data << endl; 
    return retVal;
}

