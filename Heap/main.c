#include "Heap.h"
#include <stdio.h>


int main(){


	int v[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

	Heap* H = Create_Heap(v, sizeof(v)/sizeof(int));

	Print_Heap(H);
	Build_Max_Heap(H);

	Print_Heap(H);

	Heap_Sort(H);

	Print_Heap(H);
	return 0;
}