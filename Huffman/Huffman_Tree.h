#ifndef HTREE
#define HTREE 

typedef struct _tree HuffmanTree;

typedef struct no{
	int freq;
	unsigned char symbol;
	struct no* left;
	struct no* right;
}HuffNode;


HuffmanTree* Create_Tree();
HuffNode* Create_Node(unsigned char, int);

void Print_In_Order(HuffNode*);
void Print_Pre_Order(HuffNode*);
void Print_Pos_Order(HuffNode*);
int height(HuffNode*);




#endif