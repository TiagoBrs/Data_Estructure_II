#include "BinaryTree.h"
#include <stdio.h>

int main(){
	BinaryTree* tree = Create_Btree();

	Insert_Btree(tree, 15);
	Insert_Btree(tree, 16);
	Insert_Btree(tree, 21);
	Insert_Btree(tree, 10);
	
	in_Order(tree);

	//Tree_Delete(tree, 16);
	Tree_Delete(tree, 15);
	Tree_Delete(tree, 10);
	//Tree_Delete(tree, 21);
	
	printf("\n");
	
	in_Order(tree);


	return 0;

}
