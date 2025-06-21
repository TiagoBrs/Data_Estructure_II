#ifndef RBTREE
#define RBTREE 

typedef struct _tree RB_Tree;

RB_Tree* RB_Create();

int RB_Insert(RB_Tree*, int);

void pre_Order(RB_Tree*);
void in_Order(RB_Tree*);

void RB_Delete(RB_Tree*, int);



#endif