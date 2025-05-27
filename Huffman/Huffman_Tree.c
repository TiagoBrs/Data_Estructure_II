#include "Huffman_Tree.h"
#include <stdio.h>
#include <stdlib.h>

struct _tree{
	HuffNode* root;
};

HuffmanTree* Create_Tree(){
	HuffmanTree* htree = malloc(sizeof(HuffmanTree));

	if(htree){
		htree->root = NULL;
		return htree;
	}
	return NULL;
}

HuffNode* Create_Node(unsigned char symbol, int freq){
	HuffNode* new_node = malloc(sizeof(HuffNode));
	if(new_node){
		new_node->freq = freq;
		new_node->symbol = symbol;
		new_node->left = new_node->right = NULL;
	}
	return new_node;
}

void Print_In_Order(HuffNode* node){
	if(node == NULL) return;

	Print_In_Order(node->left);
	printf("[%c, %d]--->", node->symbol, node->freq);
	Print_In_Order(node->right);
}

void Print_Pos_Order(HuffNode* node){
	if(node == NULL) return;
	
	Print_Pos_Order(node->left);
	Print_Pos_Order(node->right);
	printf("[%c, %d]--->", node->symbol, node->freq);
}


void Print_Pre_Order(HuffNode* node){
	if(node == NULL) return;

	printf("[%c, %d]--->", node->symbol, node->freq);
	Print_Pre_Order(node->left);
	Print_Pre_Order(node->right);
}

int height(HuffNode* node){
	if(node == NULL) return -1;

	int l = height(node->left);
	int r = height(node->right);

	if(l > r){
		return l + 1;
	}
	return r + 1;
}

