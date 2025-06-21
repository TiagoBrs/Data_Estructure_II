#include "RB_Tree.h"
#include <stdio.h>

int main(){
	RB_Tree* T = RB_Create();

	int V[] = {41, 38, 31, 12, 19, 8};

	for(int i=0; i<6; i++){
		RB_Insert(T, V[i]);
	}

	in_Order(T);
	putchar('\n');
	pre_Order(T);

	putchar('\n');

	RB_Delete(T, 12);

	in_Order(T);
	putchar('\n');
	pre_Order(T);

	return 0;
}