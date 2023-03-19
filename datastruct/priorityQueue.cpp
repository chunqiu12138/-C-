#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

typedef struct priorityQueue {
	ElementType* eleements;
	int	n;	//堆元素个数
	int Capacity;	//堆最大容量
}PriorityQueue;

void CreatPQ(PriorityQueue *PQ,int mSize) {	//建立一个空优先权队列
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
		else    //若p指向元素不小于其双亲节点，则调整完毕
			break;
	}
}

void AdjustDown(ElementType heap[], int current, int border) {	//当前位置current，边界下标border
	int p = current;
	int minChild;
	ElementType temp;
	while (2 * p + 1 <= border) {	//p为非叶节点
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] > heap[2 * p + 2]))	//右孩子存在且比左孩子较小
			minChild = 2 * p + 2;
		else
			minChild = 2 * p + 1;
		if (heap[p] <= heap[minChild])
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

void Append(PriorityQueue* PQ, ElementType x) {	//新增一个元素
	if (IsFull(PQ))
		return;
	PQ->eleements[PQ->n] = x;
	PQ->n++;
	AdjustUp(PQ->eleements, PQ->n - 1);
}

void Serve(PriorityQueue* PQ,ElementType *x){		//获取优先权最高元素，返回并从队列中删除
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