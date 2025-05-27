#ifndef RBTREE
#define RBTREE 

typedef struct _tree RB_Tree;

BinaryTree* Create_Btree();

int Insert_Btree(BinaryTree*, int);

void pre_Order(BinaryTree*);
void in_Order(BinaryTree*);

void Tree_Delete(BinaryTree*, int);


#endif