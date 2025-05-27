#include "RB_Tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int info;
	char color; //R or B
	struct no* left;
	struct no* right;
	struct no* parent;
}Node;


struct _tree{
	Node* root;
	Node* nil;
}

void left_rotation(AVLTree* tree, Node* X);
void right_rotation(AVLTree* tree, Node* X);

Node* Node_Create(int info){
	Node* new = malloc(sizeof(Node));

	if(!new) return NULL;
	new->color = 'R';
	new->info = info;
	new->left = new->right = new->parent = NULL; 
	//Pointer initialization to nil is delegated to the insert function

	return new;

}

RB_Tree* RB_Create(){
	RB_Tree* rb = malloc(sizeof(RB_Tree));
	Node* nil = malloc(sizeof(Node));

	if(!rb || !nil) return NULL;
		
	nil->color = 'B';
	nil->left = nil->right = nil->parent = NULL;
	nil->info = 0;

	rb->root = nil;
	rb->nil = nil;

	return rb;
}



void left_rotation(AVLTree* tree, Node* X){
	Node* Y = X->right;
	
	X->right = Y->left;

	if(Y->left != tree->nil){
		Y->left->parent = X;
	}

	Y->parent = X->parent;

	if(X->parent != tree->nil){
		//O pai de x deve apontar para Y
		if(X == X->parent->left){
			X->parent->left = Y;
		}
		else{
			X->parent->right = Y;
		}
	}
	else{
		tree->root = Y;
	}
	Y->left = X;
	X->parent = Y;
}