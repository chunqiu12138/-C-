#ifndef QUEUE_H
#define QUEUE_H

typedef int ElemTypeQ;

typedef struct queue {
	int front;
	int ferar;
	int maxsize;
	ElemTypeQ* element;
}Queue;

void create(Queue* Q, int mSize);
bool IsEmpty(Queue* Q);
bool IsFull(Queue* Q);
bool Front(Queue* Q, ElemTypeQ* x);
bool EnQueue(Queue* Q, ElemTypeQ x);
bool DeQueue(Queue* Q);
void Destroy(Queue* Q);


#endif
