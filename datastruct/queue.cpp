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

bool Front(Queue* Q, ElemTypeQ *x) {  //��ȡ��ͷԪ��
	if (IsEmpty(Q))
			return false;
	*x = Q->element[(Q->front+1)%Q->maxsize];
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