#include <iostream>
#include "BSTree.hpp"
#include <vector>

using std::vector;

BSTree::~BSTree() {
    postOrder(this->root);
}

BSTree::BSTree(const BSTree::BSTree &old_tree) {
    this->root = new BSTree::Node::Node(old_tree.root->data);
    preOrder(this->root, old_tree.root);
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
    if(this->root != NULL) inOrder(this->root, list);
}

bool BSTree::remove(int num) {
    if(!find(num)) return false;

    BSTree::Node *current = this->root;

    while(current->data != num) {
        if(num > current->data) current = current->right;
        else if(num < current->data) current = current->left;    
    }
    if(current->left == NULL && current->right == NULL) removeLeaf(current);
    else if(current->left == NULL || current->right == NULL) shortCircuit(current);
    else promotion(current);
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
    if (temp->left == NULL) {
        if(temp->parent->left == temp) temp->parent->left = temp->right;
        else temp->parent->right = temp->right;
    }
    if (temp->right == NULL) {
        if(temp->parent->left == temp) temp->parent->left = temp->left;
        else temp->parent->right = temp->left;
    }
    removeLeaf(temp);
}
void BSTree::removeLeaf(BSTree::Node *temp) {
    if(temp->parent->right == temp) temp->parent->right = NULL;
    if(temp->parent->left == temp) temp->parent->left = NULL;
    if(temp->parent == this->root) {
        if(this->root->right == temp) this->root->right = NULL;
        if(this->root->left == temp) this->root->left = NULL;
    }
    delete temp;
}
void BSTree::inOrder(BSTree::Node *n, vector<int> &list) {
    if(n != NULL) {
        inOrder(n->left, list);
        list.push_back(n->data);
        inOrder(n->right, list);
    }
}
void BSTree::postOrder(BSTree::Node *n) {
    if(n != NULL) {
        postOrder(n->left);
        postOrder(n->right);
        if(n->data != this->root->data) {
            if(n->parent->left != NULL) 
                if(n->data == n->parent->left->data) n->parent->left = NULL;
            if(n->parent->right != NULL)
                if(n->data == n->parent->right->data) n->parent->right = NULL;
        }
        delete n;
    }
}

void BSTree::preOrder(Node *newT, Node *oldT) {
    if(oldT != NULL) {
        insert(oldT->data, newT);
        preOrder(newT, oldT->left);
        preOrder(newT, oldT->right);
    }
}
