#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"
#include <math.h>
#include "Huffman_Tree.h"
#include <limits.h>

struct _hp{
	int heapsize;
	int length;
	HuffNode** Arr;
};


Heap* Create_Heap(int len){
	Heap* heap = malloc(sizeof(Heap));
	if(heap){
		heap->heapsize = 0;
		heap->length = len;
		heap->Arr = malloc(sizeof(HuffNode*) * len);
	}
	return heap;
}


void Print_Heap(Heap* heap){

	for(int i=0; i < heap->heapsize; i++){
		printf("%c ---> %d\n", heap->Arr[i]->symbol, heap->Arr[i]->freq);
	}
	putchar('\n');
}

void Min_Heapify(Heap* heap, int i){
	int l = 2*i + 1;
	int r = 2*i + 2;
	int min;

	if(l < heap->heapsize && heap->Arr[l]->freq < heap->Arr[i]->freq){
		min = l;
	}else{
		min = i;
	}

	if(r < heap->heapsize && heap->Arr[r]->freq < heap->Arr[min]->freq){
		min = r;
	}

	if(min != i){
		HuffNode* temp = heap->Arr[i];
		heap->Arr[i] = heap->Arr[min];
		heap->Arr[min] = temp;

		Min_Heapify(heap, min);
	}
}

void Build_Min_Heap(Heap* heap){
	for(int i=(floor(heap->heapsize/2)-1); i>=0; i--){
		Min_Heapify(heap, i);
	}
}

int Parent(int i){
	return (i-1)/2;
}


int Heap_Size(Heap* H){
	return H->heapsize;
}


//Funções de fila de prioridade(Cormen pg 143)

HuffNode* Heap_Min(Heap* H){
	return H->Arr[0];
}

HuffNode* Extract_Min(Heap* H){
	if(H->heapsize < 1){
		return NULL; //Underflow
	}
	HuffNode* min = Heap_Min(H);

	H->Arr[0] = H->Arr[H->heapsize-1];
	H->heapsize--;
	Min_Heapify(H, 0);

	H->Arr[H->heapsize] = NULL;

	return min;
}

void Heap_Increase(Heap* H, HuffNode* node, int i){
	if(node->freq > H->Arr[i]->freq){
		puts("Nova chave maior que a chave atual");
		return;
	}
	H->Arr[i] = node;

	while(i > 0 && H->Arr[Parent(i)]->freq > H->Arr[i]->freq){
		//Trocar Arr[1] com parent(i)
		HuffNode* Temp = H->Arr[i];
		H->Arr[i] = H->Arr[Parent(i)];
		H->Arr[Parent(i)] = Temp;

		i=Parent(i);
	}
}


void Min_Heap_Insert(Heap* H, HuffNode* node){
	HuffNode* Dummy = Create_Node('\0', INT_MAX);
	H->Arr[H->heapsize] = Dummy;
	H->heapsize++;

	Heap_Increase(H, node, H->heapsize-1);
}
