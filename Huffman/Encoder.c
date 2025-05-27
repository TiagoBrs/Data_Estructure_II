#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Heap.h"
#include "Huffman_Tree.h"


void Count_Frequency(unsigned char* string, int freq[256]);
void Set_Heap(Heap* H, unsigned char* string, int freq[256]);
int Count_Frequency_Unique(int freq[256]);
HuffNode* Huffman(unsigned char* C);


int main(){

	char C[] = "aaaabbc";

	HuffNode* root = Huffman(C);

	printf("In order:\n");
	Print_In_Order(root);
	printf("\nPós_Ordem:\n");
	Print_Pos_Order(root);
	printf("\nPreOrder\n");
	Print_Pre_Order(root);
		
	
	putchar('\n');
	return 0;	
}

HuffNode* Huffman(unsigned char* C){
	Heap* Q = Create_Heap(strlen(C)); 
	int freq[256];

	///Algoritmo HUFFMAN///
	Set_Heap(Q, C, freq);
	int n = Count_Frequency_Unique(freq);

	HuffNode* z=NULL;
	for(int i=0; i<n-1; i++){
		HuffNode* z = Create_Node('\0', 0);

		z->left = Extract_Min(Q);
		z->right = Extract_Min(Q);

		z->freq = z->left->freq + z->right->freq;
		Min_Heap_Insert(Q, z);
	}
	return z;
}



int Count_Frequency_Unique(int freq[256]){
	int count = 0;
	for(int i = 0; i < 256; i++) {
    	if(freq[i] != 0){
    		count++;
    	}
	}
	return count;
}


void Count_Frequency(unsigned char* string, int freq[256]) {
    for(int i = 0; i < 256; i++)
        freq[i] = 0;

    for(int i = 0; string[i] != '\0'; i++) {
        freq[string[i]]++;
    }
}

void Set_Heap(Heap* H, unsigned char* string, int freq[256]){
	int C = strlen(string);

	Count_Frequency(string, freq);

	for(int i=0; i<256; i++){
		if(freq[i] != 0){
			HuffNode* node = Create_Node(i, freq[i]);
			Min_Heap_Insert(H, node);
		}
	}
}
