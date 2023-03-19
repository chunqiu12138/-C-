#include<stdlib.h>

typedef int ElemType;

//defination of stack struct
typedef struct stack {
	Node* top;
}Stack;

typedef struct node {
	ElemType element;
	struct node* link;
}Node;

void push(Stack* S, ElemType x) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->element = x;
	p->link = NULL;
	p->link = S->top;
	S->top = p;
}

bool pop(Stack *s) {
	if (s->top == NULL)
		return 0;
	Node* p = s->top;
	s->top = p->link;
	free(p);
	return 1;
}