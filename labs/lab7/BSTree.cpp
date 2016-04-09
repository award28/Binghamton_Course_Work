#include <iostream>
#include "BSTree.hpp"
#include <vector>

using std::vector;

BSTree::~BSTree() {

}

BSTree::BSTree(const BSTree::BSTree &old_tree) {

}

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

void BSTree::sortedArray(vector<int> &list) {
    inOrder(this->root, list);
}

bool BSTree::remove(int num) {
    if(!find(num)) return false;
    
   
    BSTree::Node *current = this->root;
    while(current->data != num) {
        if(num > current->data) current = current->right;
        else if(num < current->data) current = current->left;    
    }
    promotion(current);
    return true;
}

BSTree::Node *BSTree::findMax(BSTree::Node *n) {
    if(n->right == NULL) return n;
    else return findMax(n->right);
}	

void BSTree::promotion(BSTree::Node *n) {
    BSTree::Node *temp = findMax(n->left);
	n->data = temp->data;
	if(temp->left == NULL) removeLeaf(temp);
	else shortCircuit(temp);
}
void BSTree::shortCircuit(BSTree::Node *temp) {
	temp->parent->right = temp->left;
	removeLeaf(temp);
}
void BSTree::removeLeaf(BSTree::Node *temp) {
	temp = NULL;
}

void BSTree::inOrder(BSTree::Node *n, vector<int> &list) {
    if(n != NULL) {
        inOrder(n->left, list);
        list.push_back(n->data);
        inOrder(n->right, list);
    }
}
