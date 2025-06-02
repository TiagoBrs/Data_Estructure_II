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
};

// Type RB_Tree

void left_rotation(RB_Tree* tree, Node* X);
void right_rotation(RB_Tree* tree, Node* X);
void Insert_fixup(RB_Tree* T, Node* Z);
void aux_inorder(Node*, RB_Tree*);
void aux_preorder(Node*, RB_Tree*);

Node* Node_Create(int info){
	Node* new_node = malloc(sizeof(Node));

	if(!new_node) return NULL;
	new_node->color = 'R';
	new_node->info = info;
	new_node->left = new_node->right = new_node->parent = NULL; 
	//Pointer initialization to nil is delegated to the insert function

	return new_node;

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


int RB_Insert(RB_Tree* tree, int key){
	if(!tree) return 0;
	Node* prev = tree->nil;
	Node* current = tree->root;

	while(current != tree->nil){
		prev = current;

		if(key > current->info){
			current = current->right;
		}
		else{
			current = current->left;
		}
	}
	Node* new_node = Node_Create(key);
	new_node->left = new_node->right = tree->nil; //Set to nil
	new_node->parent = prev;

	if(prev == tree->nil){
		tree->root = new_node;
	}
	else{
		if(key < prev->info){
			prev->left = new_node;
		}
		else{
			prev->right = new_node;
		}
	}

	new_node->color = 'R';
	Insert_fixup(tree, new_node);

	return 1;
}


void Insert_fixup(RB_Tree* T, Node* Z){
	while(Z->parent->color == 'R'){

		if(Z->parent == Z->parent->parent->left){
			Node* Y = Z->parent->parent->right;

			if(Y->color == 'R'){
				Y->color = 'B';
				Z->parent->color = 'B';
				Z->parent->parent->color = 'R';

				Z = Z->parent->parent;
			}
			else{
				if(Z == Z->parent->right){
					Z = Z->parent;
					left_rotation(T, Z);
				}
				Z->parent->color = 'B';
				Z->parent->parent->color = 'R';

				right_rotation(T, Z->parent->parent);
			}
		}
		else{
			Node* Y = Z->parent->parent->left;

			if(Y->color == 'R'){
				Y->color = 'B';
				Z->parent->color = 'B';
				Z->parent->parent->color = 'R';

				Z = Z->parent->parent;
			}
			else{
				if(Z == Z->parent->left){
					Z = Z->parent;
					right_rotation(T, Z);
				}
				Z->parent->color = 'B';
				Z->parent->parent->color = 'R';

				left_rotation(T, Z->parent->parent);
			}
		}
	}
	T->root->color = 'B';
}





void left_rotation(RB_Tree* tree, Node* X){
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
void right_rotation(RB_Tree* tree, Node* X){
	Node* Y = X->left;

	X->left = Y->right;

	if(Y->right != tree->nil){
		Y->right->parent = X;
	}

	Y->parent = X->parent;

	if(X->parent != tree->nil){
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
}


void in_Order(RB_Tree* tree){
	aux_inorder(tree->root, tree);
}


void aux_inorder(Node* node, RB_Tree* tree){
	if(node == tree->nil) return;

	aux_inorder(node->left, tree);
	printf("[%d] ", node->info);
	aux_inorder(node->right, tree);
}

void pre_Order(RB_Tree* tree){
	aux_preorder(tree->root, tree);
}


void aux_preorder(Node* node, RB_Tree* tree){
	if(node == tree->nil) return;

	printf("[%d] ", node->info);
	aux_preorder(node->left, tree);
	aux_preorder(node->right, tree);
}