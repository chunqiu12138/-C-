//头文件以及结构体定义
#include<stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct hfmTNode {
	ElementType element; //结点的数据域
	int w; //结点的权值
	struct hfmTNode* lChild; //结点的左孩子指针
	struct hfmTNode* rChild; //结点的右孩子指针
}HFMTNode;

typedef struct binary {
	HFMTNode* root;
}BinaryTree;

/*-----------------------以下为优先权队列有关操作---------------------------------*/
typedef struct priorityQueue {
	BinaryTree* nodeelem;
	int	n;	//堆元素个数
	int Capacity;	//堆最大容量
}PriorityQueue;

void CreatPQ(PriorityQueue* PQ, int mSize) {	//建立一个空优先权队列
	PQ->n = 0;
	PQ->Capacity = mSize;
	PQ->nodeelem = (BinaryTree*)malloc(mSize * sizeof(BinaryTree));
}

void Destroy(PriorityQueue* PQ) {
	free(PQ->nodeelem);
	PQ->Capacity = 0;
	PQ->n = 0;
}

void AdjustUp(BinaryTree heap[], int current) {
	int p = current;
	BinaryTree temp;
	while (p > 0)
	{
		if (heap[p].root->w < heap[(p - 1) / 2].root->w) {
			temp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = temp;
			p = (p - 1) / 2;
		}
		else    //若p指向元素不小于其双亲节点，则调整完毕
			break;
	}
}

void AdjustDown(BinaryTree heap[], int current, int border) {	//当前位置current，边界下标border
	int p = current;
	int minChild;
	BinaryTree temp;
	while (2 * p + 1 <= border) {	//p为非叶节点
		if ((2 * p + 2 <= border) && (heap[2 * p + 1].root->w > heap[2 * p + 2].root->w))	//右孩子存在且比左孩子较小
			minChild = 2 * p + 2;
		else
			minChild = 2 * p + 1;
		if (heap[p].root->w <= heap[minChild].root->w)
			break;
		else {
			temp = heap[p];
			heap[p] = heap[minChild];
			heap[minChild] = temp;
			p = minChild;	//设置下轮待考察元素位置
		}
	}
}

bool IsEmpty(PriorityQueue* PQ) {
	if (PQ->n == 0)
		return 1;
	else
		return 0;
}

bool IsFull(PriorityQueue* PQ) {
	if (PQ->n == PQ->Capacity)
		return 1;
	else
		return 0;
}

int Size(priorityQueue* PQ) {	//获取优先权队列元素总数
	return PQ->n;
}

void Append(PriorityQueue* PQ, BinaryTree* x) {	//新增一个元素
	if (IsFull(PQ))
		return;
	PQ->nodeelem[PQ->n] = *x;
	PQ->n++;
	AdjustUp(PQ->nodeelem, PQ->n - 1);
}

void Serve(PriorityQueue* PQ, BinaryTree* x) {		//获取优先权最高元素，返回并从队列中删除
	if (IsEmpty(PQ))
		return;
	*x = PQ->nodeelem[0];
	PQ->n--;
	PQ->nodeelem[0] = PQ->nodeelem[PQ->n];
	AdjustDown(PQ->nodeelem, 0, PQ->n - 1);
}
/*-----------------------以上为优先权队列有关操作---------------------------------*/

void MakeTree(BinaryTree* bt, ElementType e, BinaryTree* left, BinaryTree* right){
	HFMTNode* p = (HFMTNode*)malloc(sizeof(HFMTNode));
	bt->root = p;
	p->w = e;
	if (left)
		p->lChild = left->root;
	else
		p->lChild = NULL;
	if(right)
		p->rChild = right->root;
	else
		p->rChild = NULL;
}

void PreOrderTree(HFMTNode* t) {	
	if (!t)
		return;
	printf("%d  ", t->w);
	PreOrderTree(t->lChild);
	PreOrderTree(t->rChild);
}

//哈夫曼树的创建
BinaryTree CreatHFMTree(int w[],int m) {
	PriorityQueue* PQ=(PriorityQueue*)malloc(sizeof(PriorityQueue));	//定义优先权队列PQ,用于二叉树根节点指针
	BinaryTree* x = (BinaryTree*)malloc(sizeof(BinaryTree));			//x,y,z为二叉树变量
	BinaryTree* y = (BinaryTree*)malloc(sizeof(BinaryTree));
	BinaryTree* z = (BinaryTree*)malloc(sizeof(BinaryTree));	
	CreatPQ(PQ,m);						//初始化优先权队列PQ，设优先权值存在根节点数据域
	for (int i = 0; i < m; i++) {			
		MakeTree(x,w[i],NULL,NULL);		//创建仅包含根节点的二叉树，w[i]为根的权值
		Append(PQ,x);				//将新创建的二叉树插入优先权队列
	}
	while (PQ->n>1) {
		Serve(PQ, x);
		Serve(PQ, y);
		//合并x和y，作为新二叉树z的左右子树，z的优先权值等于x和y的优先权值之和
		if (x->root->w< y->root->w)	//设置左子树根节点值小于右子树
			MakeTree(z,x->root->w+y->root->w,x,y);
		else
			MakeTree(z, x->root->w + y->root->w, y, x);
		Append(PQ,z);	//将合并生成的新二叉树z插入优先权队列
	}
	Serve(PQ, x);	//获取优先权队列中唯一的二叉树，存入x，该二叉树即为哈夫曼树
	return *x;
}

//哈夫曼编码
BinaryTree HFMCode(char c[],int w[], int m){
	PriorityQueue* PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));	//定义优先权队列PQ,用于二叉树根节点指针
	BinaryTree* x = (BinaryTree*)malloc(sizeof(BinaryTree));			//x,y,z为二叉树变量
	BinaryTree* y = (BinaryTree*)malloc(sizeof(BinaryTree));
	BinaryTree* z = (BinaryTree*)malloc(sizeof(BinaryTree));
	CreatPQ(PQ, m);						//初始化优先权队列PQ，设优先权值存在根节点数据域
	for (int i = 0; i < m; i++) {
		MakeTree(x, w[i], NULL, NULL);		//创建仅包含根节点的二叉树，w[i]为根的权值
		x->root->element = c[i];
		Append(PQ, x);				//将新创建的二叉树插入优先权队列
	}
	while (PQ->n > 1) {
		Serve(PQ, x);
		Serve(PQ, y);
		//合并x和y，作为新二叉树z的左右子树，z的优先权值等于x和y的优先权值之和
		if (x->root->w < y->root->w)	//设置左子树根节点值小于右子树
			MakeTree(z, x->root->w + y->root->w, x, y);
		else
			MakeTree(z, x->root->w + y->root->w, y, x);
		Append(PQ, z);	//将合并生成的新二叉树z插入优先权队列
	}
	Serve(PQ, x);	//获取优先权队列中唯一的二叉树，存入x，该二叉树即为哈夫曼树
	return *x;
}


//哈夫曼解码
void HFMDcode(BinaryTree t){
	HFMTNode *p = t.root;
	char s[20];
	printf("请输入哈夫曼编码(01字符串):");
	gets_s(s);
	for (int i = 0; i < 20; i++) {		//遍历输入的01串
		if (p->lChild == NULL) {
			printf("解码结果:%c\n", p->element);
			break;
		}
		if ('0' == s[i])
			p = p->lChild;
		else
			p = p->rChild;
	}
}

//用于测试的主函数
int main() {
	printf("创建 *教材图5.33* 的哈夫曼树\n");
	printf("权值集={9,11,13,3,5,12}");
	int w[6] = { 9,11,13,3,5,12 };
	BinaryTree t;
	t=CreatHFMTree(w,6);
	getchar();
	printf("\n--创建完成--\n");
	getchar();
	printf("先序遍历创建的哈夫曼树:\n");
	PreOrderTree(t.root);
	getchar();
	printf("\n\n将 *教材图5.34* 的列子进行哈夫曼编码\n");
	printf("字符集S={ 'A','B','C','D' }\n");
	printf("权值集w={  6 , 4 , 2 , 3 }");
	int w1[6] = { 6,4,2,3 };
	char s[6] = { 'A','B','C','D' };
	BinaryTree t1;
	t1 = HFMCode(s,w1,4);
	getchar();
	printf("\n--编码完成--\n");
	getchar();
	printf("输入哈夫曼编码(A:0 B:10 C:110 D:111)可以进行解码\n");
	HFMDcode(t1);
	return 0;
}