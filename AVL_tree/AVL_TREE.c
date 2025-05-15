#include "AVL_TREE.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no{
	int info;
	struct no* left;
	struct no* right;
	struct no* parent;
	int balance;
}Node;

struct _tree{
	Node* root;
};

int Insert(int key, Node* current, bool* h, AVLTree* tree);

Node* Left_Rotation(AVLTree* tree, Node* X);
Node* Right_Rotation(AVLTree* tree, Node* X);

Node* Case_1(Node* pt, bool* h);
Node* Case_2(Node* pt, bool* h);

AVLTree* Create_AVLtree(){
	AVLTree* tree = malloc(sizeof(AVLTree));
	if(tree){
		tree->root = NULL;
	}
	return tree;
}

Node* Create_Node(int info){
	Node* new_node = malloc(sizeof(Node));
	if(new_node){
		new_node->info = info;
		new_node->left = new_node->right = new_node->parent = NULL;
		new_node->balance = 0;
	}
	return new_node;
}


void AVL_Insert(AVLTree* tree, Node** node, int info, bool* h){

}






















Node* Left_Rotation(AVLTree* tree, Node* X){
	Node* Y = X->right;
	
	X->right = Y->left;

	if(Y->left != NULL){
		Y->left->parent = X;
	}

	Y->parent = X->parent;

	if(X->parent != NULL){
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
	return Y;
}

Node* Right_Rotation(AVLTree* tree, Node* X){
	Node* Y = X->left;
	
	X->left = Y->right;

	if(Y->right != NULL){
		Y->right->parent = X;
	}

	Y->parent = X->parent;

	if(X->parent != NULL){
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
	Y->right = X;
	X->parent = Y;
	return Y;
}


void Aux_In_Order(Node* v){
	Aux_In_Order(v->left);
	printf("%d - ", v->info);
	Aux_In_Order(v->right);
}
void In_Order(AVLTree* tree){
	if(tree){
		Aux_In_Order(tree->root);
	}
}