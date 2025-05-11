#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct _tree AVLTree;

AVLTree* Create_AVLtree();

int AVL_Insert(AVLTree*, int);

void Pre_Order(AVLTree*);
void In_Order(AVLTree*);

void AVL_Delete(AVLTree*, int);

#endif