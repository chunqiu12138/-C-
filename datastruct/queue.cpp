#include "queue.h"
#include <stdlib.h>

void create(Queue* Q, int mSize) {
	Q->maxsize = mSize;
	Q->element = (ElemTypeQ*)malloc(sizeof(ElemTypeQ) * mSize);
	Q->front = Q->ferar = 0;
}

bool IsEmpty(Queue* Q) {
	return Q->front == Q->ferar;
}

bool IsFull(Queue* Q) {
	return (Q->ferar+1)%Q->maxsize==Q->front;
}

bool Front(Queue* Q, ElemTypeQ *x) {  //获取队头元素
	if (IsEmpty(Q))
			return false;
	*x = Q->element[(Q->front+1)%Q->maxsize];
	return true;
}

bool EnQueue(Queue* Q, ElemTypeQ x) {	//在队尾插入元素
	if (IsFull(Q))
		return false;
	Q->ferar = (Q->ferar + 1) % Q->maxsize;
	Q->element[Q->ferar] = x;
	return true;
}

bool DeQueue(Queue* Q) {	//删除队头元素
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