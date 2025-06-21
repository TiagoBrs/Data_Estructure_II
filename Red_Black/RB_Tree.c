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

// Type RB_Tree_Delete

Node* treeMin(Node* node, RB_Tree* T);
void left_rotation(RB_Tree* tree, Node* X);
void right_rotation(RB_Tree* tree, Node* X);
void Insert_fixup(RB_Tree* T, Node* Z);
void aux_inorder(Node*, RB_Tree*);
void aux_preorder(Node*, RB_Tree*);
Node* Search(Node* node, int key, RB_Tree* T);
void RB_Delete_FIXUP(RB_Tree* T, Node* x);
void RB_Transplant(RB_Tree* T, Node* u, Node* v);

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

void RB_Delete(RB_Tree* T, int key){
	Node* z = Search(T->root, key, T);

	Node* y = z;
	Node* x = NULL;
	char y_original_color = z->color;

	if(z->left == T->nil){
		x = y->right;
		RB_Transplant(T, z, z->right);
	}
	else{
		if(z->right == T->nil){
			x = y->left;
			RB_Transplant(T, z, z->left);
		}
		else{
			Node* y = treeMin(z->right, T);
			x = y->right;
			y_original_color = y->color;
			
			if(y->parent == z){
				x->parent = y;
			}
			else{
				RB_Transplant(T, y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			RB_Transplant(T, z, y);
			y->left = z->left;
			y->left->parent = y;	
			
			y->color = z->color;
			//Seta a subárvore à esquerda
			
		}
	}
	if(y_original_color == 'B'){
			RB_Delete_FIXUP(T, x);
		}
	free(z);
}

void RB_Delete_FIXUP(RB_Tree* T, Node* x){
	while(x != T->nil && x->color == 'B'){
		if(x == x->parent->left){ // Verifica se x é o filho da esquerda
			Node* w = x->parent->right;

			//Case 1
			if(w->color == 'R'){
				w->color = 'B';
				w->parent->color = 'R';
				left_rotation(T, x->parent);
				w = x->parent->right;
			} 
			//Case 2
			if(w->left->color == 'B' && w->right->color == 'B'){
				w->color = 'R';
				x = x->parent;
			}
			else{
				//Case 3
				if(w->left->color == 'R' && w->right->color == 'B'){
					w->color = 'R';
					w->left->color = 'B';
					right_rotation(T, w);
					w = x->parent->right;
				}
				//Case 4

				w->color = x->parent->color;
				w->parent->color = 'B';
				w->right->color = 'B';
				left_rotation(T, x->parent);
				x = T->root;
			}
		}
		else{
			//Same with left and right exchanged
			Node* w = x->parent->left;

			//Case 1
			if(w->color == 'R'){
				w->color = 'B';
				w->parent->color = 'R';
				right_rotation(T, x->parent);
				w = x->parent->left;
			} 
			//Case 2
			if(w->right->color == 'B' && w->left->color == 'B'){
				w->color = 'R';
				x = x->parent;
			}
			else{
				//Case 3
				if(w->right->color == 'R' && w->left->color == 'B'){
					w->color = 'R';
					w->right->color = 'B';
					left_rotation(T, w);
					w = x->parent->left;
				}
				//Case 4

				w->color = x->parent->color;
				w->parent->color = 'B';
				w->left->color = 'B';
				right_rotation(T, x->parent);
				x = T->root;
			}
		}
	}
	x->color = 'B';
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

Node* treeMin(Node* node, RB_Tree* T){
	while(node->left != T->nil){
		node = node->left;
	}
	return node;
}

Node* Search(Node* node, int key, RB_Tree* T){
	if(node == T->nil) return T->nil;

	if(node->info == key) return node;

	if(key < node->info)
		return Search(node->left, key, T);
	return Search(node->right, key, T);
}

void RB_Transplant(RB_Tree* T, Node* u, Node* v){
	if(u->parent == T->nil){
		T->root = v;
	}
	else{
		if(u == u->parent->left){
			u->parent->left = v;
		}
		else{
			u->parent->right = v;
		}
	}
	v->parent = u->parent;
	
}
