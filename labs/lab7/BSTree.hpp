#ifndef BSTREE_HPP
#define BSTREE_HPP
#include <iostream>
#include <vector>

class BSTree {
    private:
        class Node {
            public:
               Node(int data) { this->data = data; this->parent = NULL; this->left = NULL; this->right = NULL; }
               int data;
               Node *parent;
               Node *left;
               Node *right;
        };
        Node *root;
    public:
        BSTree(){ this->root = NULL; }
        ~BSTree();
        BSTree(const BSTree &old_tree);
        bool empty(){ bool retVal; (this->root) ? retVal = false: retVal = true; return retVal; }
        bool insert(int val);
        bool insert(int val, Node *current);
        bool find(int val);
        bool find(int val, Node *current); 
        void sortedArray(std::vector<int> &list);
        bool remove(int num);
        Node *findMax(Node *n);
        void promotion(Node *n);
        void shortCircuit(Node *temp);
        void removeLeaf(Node *temp);
};
#endif
