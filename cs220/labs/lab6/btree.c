#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct tnode * tree;

struct tnode {
   tree left;
   tree right;
   int value;
};

tree makeNode(int value);
void freeTree(tree t);

void insertVal(tree t, int value);
void prLNR(tree t);
void prRNL(tree t);
void printTree(tree t, char * prefix);

int main(int argc, char **argv) {
   int i;

   if (argc<2) {
		printf("You must specify at least one argument to %s\n",argv[0]);
		return 1;
	}
	tree root=makeNode(atoi(argv[1]));
   for(i=2; i<argc; i++) {
      int val=atoi(argv[i]);
      insertVal(root,val);
   }
   printf("In LNR order: ");
   prLNR(root);
   printf("\nIn RNL order: ");
   prRNL(root);
   printf("\nGraphic Representation...\n");
   printTree(root,"");
   freeTree(root);
   return 0;
}

tree makeNode(int value) {
   tree t = malloc(sizeof(struct tnode));
   t->value=value;
   t->left=NULL;
   t->right=NULL;
   return t;
}

void freeTree(tree t) {
   assert(t);
   if (t->left) freeTree(t->left);
   if (t->right) freeTree(t->right);
   free(t);
}

void insertVal(tree t, int value) {
	assert(t);

	if (t->value >= value && t->left != NULL) insertVal(t->left, value);
    else if(t->value >= value && t->left == NULL) t->left = makeNode(value);
    else if (t->value < value && t->right != NULL) insertVal(t->right, value);
    else if(t->value < value && t->right == NULL) t->right = makeNode(value);
}

void prLNR(tree t) {
	assert(t);
   /* Write code to:
   	- prLNR the left sub-tree,
   	- print the value of the node,
   	- prLNR the right sub-tree
   */
    if(t->left) prLNR(t->left);
    printf("%d ", t->value);
    if(t->right) prRNL(t->right);
    return;
}


void prRNL(tree t) {
	assert(t);
   /* Write code to:
   	- prRNL the right sub-tree,
   	- print the value of the node,
   	- prRNL the left sub-tree
   */
    if(t->right) prLNR(t->right);
    printf("%d ", t->value);
    if(t->left) prRNL(t->left);
}

void printTree(tree t, char * prefix) {
	assert(t);
	/* Write code to print a tree graphically */
}

