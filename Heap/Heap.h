#ifndef HEAP
#define HEAP 

typedef struct _hp Heap;

Heap* Create_Heap(int v[], int);

void Max_Heapify(Heap*, int);
void Build_Max_Heap(Heap*);
void Heap_Sort(Heap*);

void Print_Heap(Heap*);

#endif