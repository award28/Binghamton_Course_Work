#ifndef BSTREE_HPP
#define BSTREE_HPP
#include <iostream>

class BSTree {
    private:
        class Node {
            public:
               friend class BSTree;
               Node(int data) { this->data = data; this->left = NULL; this->right = NULL; }
               int data;
               Node *left;
               Node *right;
        };
        Node *root;
    public:
        friend class Node;
        BSTree(){ this->root = NULL; }
        bool empty(){ bool retVal; (this->root) ? retVal = false: retVal = true; return retVal; }
        bool insert(int val);
        bool insert(int val, Node *current);
        bool find(int val);
        bool find(int val, Node *current); 
};
#endif
