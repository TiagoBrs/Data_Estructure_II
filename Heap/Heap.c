#include <stdlib.h>
#include <stdio.h>
#include "Heap.h"
#include <math.h>

struct _hp{
	unsigned int length;
	unsigned int heapsize;
	int* Arr;
};

Heap* Create_Heap(int v[], int len){
	Heap* heap = malloc(sizeof(Heap));
	if(heap){
		heap->Arr = malloc(sizeof(int)*len);
		heap->length = heap->heapsize = len;
	}
	for(int i=0; i<len; i++){
		heap->Arr[i] = v[i];
	}
	return heap;
}


void Print_Heap(Heap* heap){

	for(int i=0; i <heap->heapsize; i++){
		printf("%d - ", heap->Arr[i]);
	}
	putchar('\n');
}

void Max_Heapify(Heap* heap, int i){
	int l = 2*i + 1;
	int r = 2*i + 2;
	int largest;

	if(l < heap->heapsize && heap->Arr[l] > heap->Arr[i]){
		largest = l;
	}else{
		largest = i;
	}

	if(r < heap->heapsize && heap->Arr[r] > heap->Arr[largest]){
		largest = r;
	}

	if(largest != i){
		int temp = heap->Arr[i];
		heap->Arr[i] = heap->Arr[largest];
		heap->Arr[largest] = temp;

		Max_Heapify(heap, largest);
	}
}

void Build_Max_Heap(Heap* heap){
	for(int i=(floor(heap->heapsize/2)-1); i>=0; i--){
		Max_Heapify(heap, i);
	}
}

void Heap_Sort(Heap* H){
	Build_Max_Heap(H);

	for(int i=H->length-1; i>0; i--){
		int temp = H->Arr[0];
		H->Arr[0] = H->Arr[i];
		H->Arr[i] = temp;

		H->heapsize--;
		Max_Heapify(H, 0);
	}

	H->heapsize = H->length;
}