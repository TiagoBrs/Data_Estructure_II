#ifndef BTREE
#define BTREE 

typedef struct _tree BinaryTree;

BinaryTree* Create_Btree();

int Insert_Btree(BinaryTree*, int);

void pre_Order(BinaryTree*);
void in_Order(BinaryTree*);

void Tree_Delete(BinaryTree*, int);


#endif