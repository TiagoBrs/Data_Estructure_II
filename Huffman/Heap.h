#include "Huffman_Tree.h"

#ifndef HEAP
#define HEAP 

typedef struct _hp Heap;

Heap* Create_Heap(int);

void Min_Heapify(Heap*, int);
void Build_Min_Heap(Heap*);
void Min_Heap_Insert(Heap*, HuffNode*);

int Heap_Size(Heap*);
HuffNode* Extract_Min(Heap* H);


void Print_Heap(Heap*);

#endif