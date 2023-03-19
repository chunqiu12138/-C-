#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct priorityQueue {
	ElementType* eleements;
	int	n;	//��Ԫ�ظ���
	int Capacity;	//���������
}PriorityQueue;

void CreatPQ(PriorityQueue *PQ,int mSize) {	//����һ��������Ȩ����
	PQ->n = 0;
	PQ->Capacity = mSize;
	PQ->eleements = (ElementType*)malloc(mSize * sizeof(ElementType));
}

void Destroy(PriorityQueue *PQ){
	free(PQ->eleements);
	PQ->Capacity = 0;
	PQ->n = 0;
}

void AdjustUp(ElementType heap[], int current) {
	int p = current;
	ElementType temp;
	while (p>0)
	{
		if (heap[p] < heap[(p - 1) / 2]) {
			temp = heap[p];
			heap[p] = heap[(p - 1) / 2];
			heap[(p - 1) / 2] = temp;
			p = (p - 1) / 2;
		}
		else    //��pָ��Ԫ�ز�С����˫�׽ڵ㣬��������
			break;
	}
}

void AdjustDown(ElementType heap[], int current, int border) {	//��ǰλ��current���߽��±�border
	int p = current;
	int minChild;
	ElementType temp;
	while (2 * p + 1 <= border) {	//pΪ��Ҷ�ڵ�
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] > heap[2 * p + 2]))	//�Һ��Ӵ����ұ����ӽ�С
			minChild = 2 * p + 2;
		else
			minChild = 2 * p + 1;
		if (heap[p] <= heap[minChild])
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

void Append(PriorityQueue* PQ, ElementType x) {	//����һ��Ԫ��
	if (IsFull(PQ))
		return;
	PQ->eleements[PQ->n] = x;
	PQ->n++;
	AdjustUp(PQ->eleements, PQ->n - 1);
}

void Serve(PriorityQueue* PQ,ElementType *x){		//��ȡ����Ȩ���Ԫ�أ����ز��Ӷ�����ɾ��
	if (IsEmpty(PQ))
		return;
	*x = PQ->eleements[0];
	PQ->n--;
	PQ->eleements[0] = PQ->eleements[PQ->n];
	AdjustDown(PQ->eleements, 0, PQ->n - 1);
}

int main() {
	PriorityQueue *p=(PriorityQueue*)malloc(sizeof(PriorityQueue));
	ElementType m;
	ElementType *x=&m;
	CreatPQ(p,10);
	Append(p, 71);
	Append(p, 74);
	Append(p, 2);
	Append(p, 72);
	Append(p, 54);
	Append(p, 93);
	Append(p, 52);
	Append(p, 28);
	for (int i = 0; i < p->n; i++)
	{
		printf("%d ",p->eleements[i]);
	}
	Serve(p, x);
	Serve(p, x);
	printf("\n");
	for (int i = 0; i < p->n; i++)
	{
		printf("%d ", p->eleements[i]);
	}
}