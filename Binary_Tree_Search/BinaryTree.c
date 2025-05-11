#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int info;
	struct no* left;
	struct no* right;
	struct no* parent;
}Node;

struct _tree{
	Node* root;
};

//Aux Functions
void auxIn_Order(Node* node);
void auxPre_Order(Node* node);

Node* treeMin(Node* node);


Node* Create_Node(int info);


BinaryTree* Create_Btree(){
	BinaryTree* tree = malloc(sizeof(BinaryTree));
	if(tree){
		tree->root = NULL;
	}
	return tree;
}


void pre_Order(BinaryTree* tree){
	if(tree){
		auxPre_Order(tree->root);
	}
}


void in_Order(BinaryTree* tree){
	if(tree){
		auxIn_Order(tree->root);
	}
}

Node* Search(Node* node, int key){
	if(!node) return NULL;

	if(node->info == key) return node;

	if(key < node->info)
		return Search(node->left, key);
	return Search(node->right, key);
}


int Insert_Btree(BinaryTree* tree, int info){
	if(!tree) return 0;

	Node* new_node = Create_Node(info);
	Node* current = tree->root;
	Node* prev=NULL;

	while(current != NULL){
		prev = current;
		if(info < current->info){
			current = current->left;
		}
		else{
			if(info > current->info){
				current = current->right;
			}
			else{
				free(new_node);
				return 0;
				}	
			}
		}
	new_node->parent = prev;
	if(prev == NULL){
		tree->root = new_node;
	}	
	else{
		if(info > prev->info){
			prev->right = new_node;
		}
		else{
			prev->left = new_node;
		}
	}
	return 1;
}

//Substitui a subárvore enraizada em u pela enraizada em v
void Transplant(BinaryTree* tree, Node* u, Node* v){
	if(u->parent == NULL){
		tree->root = v;
	}
	else{
		if(u == u->parent->left){
			u->parent->left = v;
		}
		else{
			u->parent->right = v;
		}
	}
	if(v != NULL){
		v->parent = u->parent;
	}
}

void Tree_Delete(BinaryTree* tree, int key){
	Node* to_delete = Search(tree->root, key);
	if(!to_delete) return;

	if(to_delete->left == NULL){
		Transplant(tree, to_delete, to_delete->right);
	}
	else{
		if(to_delete->right == NULL){
			Transplant(tree, to_delete, to_delete->left);
		}
		else{
			Node* successor = treeMin(to_delete->right);

			if(successor->parent != successor){
				//Seta a subávore a direita pois, o sucessor não é filho e seus dois ponteiros devem ser atualizados
				Transplant(tree, successor, successor->right);
				successor->right = to_delete->right;
				to_delete->right->parent = successor;
			}

			//Seta a subárvore à esquerda
			Transplant(tree, to_delete, successor);
			successor->left = to_delete->left;
			to_delete->left->parent = successor;
		}
	}
	free(to_delete);
}

//Aux Functions

Node* nodeSucessor(Node* node){
	if(node->right != NULL){
		return treeMin(node->right);
	}
	else{
		Node* suc = node->parent;
		while(node->parent != NULL && suc->info < node->info){
			suc = suc->parent;
		}
		return suc;
	}
}
Node* treeMin(Node* node){
	while(node->left != NULL){
		node = node->left;
	}
	return node;
}


void auxPre_Order(Node* node){
	if(node!=NULL){
		printf("%d -> ", node->info);
		auxPre_Order(node->left);
		auxPre_Order(node->right);
	}
}

void auxIn_Order(Node* node){
	if(node!=NULL){
		auxIn_Order(node->left);
		printf("%d -> ", node->info);
		auxIn_Order(node->right);
	}
}

Node* Create_Node(int info){
	Node* new_node = malloc(sizeof(Node));
	if(new_node){
		new_node->info = info;
		new_node->left = new_node->right = new_node->parent = NULL;
	}
	return new_node;
}
