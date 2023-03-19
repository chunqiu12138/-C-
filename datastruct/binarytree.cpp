#include <stdlib.h>
#include <stdio.h>

typedef char ElemType;

typedef struct btnode {
	ElemType element;
	struct btnode* left;
	struct btnode* right;
}BTNode, ElemTypeQ;

typedef struct binary {
	BTNode* root;
}BinaryTree;

typedef struct queue {
	int front;
	int ferar;
	int maxsize;
	ElemTypeQ* element;
}Queue;

void create(Queue* Q, int mSize) {
	Q->maxsize = mSize;
	Q->element = (ElemTypeQ*)malloc(sizeof(ElemTypeQ) * mSize);
	Q->front = Q->ferar = 0;
}

bool IsEmpty(Queue* Q) {
	return Q->front == Q->ferar;
}

bool IsFull(Queue* Q) {
	return (Q->ferar + 1) % Q->maxsize == Q->front;
}

bool Front(Queue* Q, ElemTypeQ** x) {  //��ȡ��ͷԪ��
	if (IsEmpty(Q))
		return false;
	*x =&(Q->element[(Q->front + 1) % Q->maxsize]);
	return true;
}

bool EnQueue(Queue* Q, ElemTypeQ x) {	//�ڶ�β����Ԫ��
	if (IsFull(Q))
		return false;
	Q->ferar = (Q->ferar + 1) % Q->maxsize;
	Q->element[Q->ferar] = x;
	return true;
}

bool DeQueue(Queue* Q) {	//ɾ����ͷԪ��
	if (IsEmpty(Q))
		return false;
	Q->front = (Q->front + 1) % Q->maxsize;
	return true;
}

void Destroy(Queue* Q) {
	Q->maxsize = 0;
	free(Q->element);
	Q->front = Q->front = -1;
}

void Creat(BinaryTree* bt) {	//����һ�ÿյĶ�����
	bt->root = NULL;
}

BTNode* NweNode(ElemType x, BTNode* l, BTNode* r) {
	BTNode* p = (BTNode*)malloc(sizeof(BTNode));
	p->element = x;
	p->left = l;
	p->right = r;
	return p;
}

bool Root(BinaryTree *bt,ElemType *x) {		//���ڵ�ֵ����x
	if (bt->root) {
		x = &bt->root->element;
		return true;
	}
	else
		return false;
}

void MakeTree(BinaryTree* bt, ElemType e,BinaryTree *left,BinaryTree* right) {	//	����һ�ö�����bt,left��rightΪ����������
	if (bt->root || left == right)
		return;
	bt->root = NweNode(e,left->root,right->root);
	left->root = right->root = NULL;
}

void PreOrderTree(BTNode *t){	//�������������
	if (!t)
		return;
	printf("%c",t->element);
	PreOrderTree(t->left);
	PreOrderTree(t->right);
}

void  MidOrderTree(BTNode* t) {	//�������������
	if (!t)
		return;
	MidOrderTree(t->left);
	printf("%c", t->element);
	MidOrderTree(t->right);
}

void LateOrderTree(BTNode* t) {		//�������������
	if (!t)
		return;
	LateOrderTree(t->left);
	LateOrderTree(t->right);
	printf("%c", t->element);
}

#define QUEUESIZE 100
void LevelOrderTree(BinaryTree* Tree) {		//�������
	if (!Tree->root)
		return;
	Queue Q;	BTNode *t=Tree->root;
	create(&Q, QUEUESIZE);
	EnQueue(&Q, *Tree->root);
	while (!IsEmpty(&Q)) {
		Front(&Q, &t);
		DeQueue(&Q);
		printf("%c", t->element);
		if (t->left) EnQueue(&Q, *t->left);
		if (t->right)EnQueue(&Q, *t->right);
	}
	Destroy(&Q);
}

int Check_Account(BTNode *t){
	if (!t)
		return 0;
	else
		return Check_Account(t->left) + Check_Account(t->right)+1;
}

int CheckHigh(BTNode* t) {	//��ѯ�������߶�
	int lh, rh,maxh;
	if (t) {
		lh = CheckHigh(t->left);
		rh = CheckHigh(t->right);
		maxh=(lh > rh)? lh : rh;
		return (maxh + 1);
	}
	else return 0;
}

void TreeClear(BTNode *t){
	if (!t)
		return;
	TreeClear(t->left);
	TreeClear(t->right);
	free(t);
}

int main() {
	BinaryTree a, b, x, y, z;
	Creat(&a);
	Creat(&b); 
	Creat(&x);
	Creat(&y);
	Creat(&z);
	MakeTree(&y, 'E', &a, &b);
	MakeTree(&z, 'F', &a, &b);
	MakeTree(&x, 'C', &y, &z);
	MakeTree(&y, 'D', &a, &b);
	MakeTree(&z, 'B', &y, &x);
	PreOrderTree(z.root);
	printf("\n");
	MidOrderTree(z.root);
	printf("\n");
	LateOrderTree(z.root);
	printf("\n");
	LevelOrderTree(&z);
	printf("\n");	
	printf("%d",CheckHigh(z.root));
	printf("\n");
	printf("%d", Check_Account(z.root));
	TreeClear(z.root);
}