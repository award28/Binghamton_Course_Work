#include <iostream>
#include "BSTree.hpp"

bool BSTree::insert(int val) {
    if(empty()) {
        this->root = new BSTree::Node::Node(val);
        return true;
    }

    return insert(val, this->root);
}

bool BSTree::insert(int val, BSTree::Node *current) {
    bool retVal = false;

    if(val > current->data && current->right == NULL) {
        current->right = new BSTree::Node::Node(val);
        current->right->parent = current;
        retVal = true;
    }
    else if(val > current->data) retVal = insert(val, current->right);
    else if(val < current->data && current->left == NULL) {
        current->left = new BSTree::Node::Node(val);
        current->left->parent = current;
        retVal = true;
    }
    else if(val < current->data) retVal = insert(val, current->left);
    return retVal;
}

bool BSTree::find(int val) {
    if(empty()) return false;
    else if(this->root->data == val) return true;
    return find(val, this->root);
}

bool BSTree::find(int val, BSTree::Node *current) {
    bool retVal = false;

    if(current == NULL) return false; 
    
    if(val > current->data) retVal = find(val, current->right);
    else if(val < current->data) retVal = find(val, current->left);
    else if(val == current->data) retVal = true;
    return retVal;
}

