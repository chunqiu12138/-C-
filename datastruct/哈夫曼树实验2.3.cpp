//ͷ�ļ��Լ��ṹ�嶨��
#include<stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct hfmTNode {
	ElementType element; //����������
	int w; //����Ȩֵ
	struct hfmTNode* lChild; //��������ָ��
	struct hfmTNode* rChild; //�����Һ���ָ��
}HFMTNode;

typedef struct binary {
	HFMTNode* root;
}BinaryTree;

/*-----------------------����Ϊ����Ȩ�����йز���---------------------------------*/
typedef struct priorityQueue {
	BinaryTree* nodeelem;
	int	n;	//��Ԫ�ظ���
	int Capacity;	//���������
}PriorityQueue;

void CreatPQ(PriorityQueue* PQ, int mSize) {	//����һ��������Ȩ����
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
		else    //��pָ��Ԫ�ز�С����˫�׽ڵ㣬��������
			break;
	}
}

void AdjustDown(BinaryTree heap[], int current, int border) {	//��ǰλ��current���߽��±�border
	int p = current;
	int minChild;
	BinaryTree temp;
	while (2 * p + 1 <= border) {	//pΪ��Ҷ�ڵ�
		if ((2 * p + 2 <= border) && (heap[2 * p + 1].root->w > heap[2 * p + 2].root->w))	//�Һ��Ӵ����ұ����ӽ�С
			minChild = 2 * p + 2;
		else
			minChild = 2 * p + 1;
		if (heap[p].root->w <= heap[minChild].root->w)
			break;
		else {
			temp = heap[p];
			heap[p] = heap[minChild];
			heap[minChild] = temp;
			p = minChild;	//�������ִ�����Ԫ��λ��
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

int Size(priorityQueue* PQ) {	//��ȡ����Ȩ����Ԫ������
	return PQ->n;
}

void Append(PriorityQueue* PQ, BinaryTree* x) {	//����һ��Ԫ��
	if (IsFull(PQ))
		return;
	PQ->nodeelem[PQ->n] = *x;
	PQ->n++;
	AdjustUp(PQ->nodeelem, PQ->n - 1);
}

void Serve(PriorityQueue* PQ, BinaryTree* x) {		//��ȡ����Ȩ���Ԫ�أ����ز��Ӷ�����ɾ��
	if (IsEmpty(PQ))
		return;
	*x = PQ->nodeelem[0];
	PQ->n--;
	PQ->nodeelem[0] = PQ->nodeelem[PQ->n];
	AdjustDown(PQ->nodeelem, 0, PQ->n - 1);
}
/*-----------------------����Ϊ����Ȩ�����йز���---------------------------------*/

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

//���������Ĵ���
BinaryTree CreatHFMTree(int w[],int m) {
	PriorityQueue* PQ=(PriorityQueue*)malloc(sizeof(PriorityQueue));	//��������Ȩ����PQ,���ڶ��������ڵ�ָ��
	BinaryTree* x = (BinaryTree*)malloc(sizeof(BinaryTree));			//x,y,zΪ����������
	BinaryTree* y = (BinaryTree*)malloc(sizeof(BinaryTree));
	BinaryTree* z = (BinaryTree*)malloc(sizeof(BinaryTree));	
	CreatPQ(PQ,m);						//��ʼ������Ȩ����PQ��������Ȩֵ���ڸ��ڵ�������
	for (int i = 0; i < m; i++) {			
		MakeTree(x,w[i],NULL,NULL);		//�������������ڵ�Ķ�������w[i]Ϊ����Ȩֵ
		Append(PQ,x);				//���´����Ķ�������������Ȩ����
	}
	while (PQ->n>1) {
		Serve(PQ, x);
		Serve(PQ, y);
		//�ϲ�x��y����Ϊ�¶�����z������������z������Ȩֵ����x��y������Ȩֵ֮��
		if (x->root->w< y->root->w)	//�������������ڵ�ֵС��������
			MakeTree(z,x->root->w+y->root->w,x,y);
		else
			MakeTree(z, x->root->w + y->root->w, y, x);
		Append(PQ,z);	//���ϲ����ɵ��¶�����z��������Ȩ����
	}
	Serve(PQ, x);	//��ȡ����Ȩ������Ψһ�Ķ�����������x���ö�������Ϊ��������
	return *x;
}

//����������
BinaryTree HFMCode(char c[],int w[], int m){
	PriorityQueue* PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));	//��������Ȩ����PQ,���ڶ��������ڵ�ָ��
	BinaryTree* x = (BinaryTree*)malloc(sizeof(BinaryTree));			//x,y,zΪ����������
	BinaryTree* y = (BinaryTree*)malloc(sizeof(BinaryTree));
	BinaryTree* z = (BinaryTree*)malloc(sizeof(BinaryTree));
	CreatPQ(PQ, m);						//��ʼ������Ȩ����PQ��������Ȩֵ���ڸ��ڵ�������
	for (int i = 0; i < m; i++) {
		MakeTree(x, w[i], NULL, NULL);		//�������������ڵ�Ķ�������w[i]Ϊ����Ȩֵ
		x->root->element = c[i];
		Append(PQ, x);				//���´����Ķ�������������Ȩ����
	}
	while (PQ->n > 1) {
		Serve(PQ, x);
		Serve(PQ, y);
		//�ϲ�x��y����Ϊ�¶�����z������������z������Ȩֵ����x��y������Ȩֵ֮��
		if (x->root->w < y->root->w)	//�������������ڵ�ֵС��������
			MakeTree(z, x->root->w + y->root->w, x, y);
		else
			MakeTree(z, x->root->w + y->root->w, y, x);
		Append(PQ, z);	//���ϲ����ɵ��¶�����z��������Ȩ����
	}
	Serve(PQ, x);	//��ȡ����Ȩ������Ψһ�Ķ�����������x���ö�������Ϊ��������
	return *x;
}


//����������
void HFMDcode(BinaryTree t){
	HFMTNode *p = t.root;
	char s[20];
	printf("���������������(01�ַ���):");
	gets_s(s);
	for (int i = 0; i < 20; i++) {		//���������01��
		if (p->lChild == NULL) {
			printf("������:%c\n", p->element);
			break;
		}
		if ('0' == s[i])
			p = p->lChild;
		else
			p = p->rChild;
	}
}

//���ڲ��Ե�������
int main() {
	printf("���� *�̲�ͼ5.33* �Ĺ�������\n");
	printf("Ȩֵ��={9,11,13,3,5,12}");
	int w[6] = { 9,11,13,3,5,12 };
	BinaryTree t;
	t=CreatHFMTree(w,6);
	getchar();
	printf("\n--�������--\n");
	getchar();
	printf("������������Ĺ�������:\n");
	PreOrderTree(t.root);
	getchar();
	printf("\n\n�� *�̲�ͼ5.34* �����ӽ��й���������\n");
	printf("�ַ���S={ 'A','B','C','D' }\n");
	printf("Ȩֵ��w={  6 , 4 , 2 , 3 }");
	int w1[6] = { 6,4,2,3 };
	char s[6] = { 'A','B','C','D' };
	BinaryTree t1;
	t1 = HFMCode(s,w1,4);
	getchar();
	printf("\n--�������--\n");
	getchar();
	printf("�������������(A:0 B:10 C:110 D:111)���Խ��н���\n");
	HFMDcode(t1);
	return 0;
}