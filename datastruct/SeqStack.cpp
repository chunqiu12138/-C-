#include<stdlib.h>

typedef int ElemType;

//defination of stack struct
typedef struct stack {
	int top;
	int maxSize;
	ElemType* element;
}Stack;

//creat a stack
void Create(Stack* s, int mSize)
{
	s->maxSize = mSize;
	s->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
	s->top = -1;
}

//destroy
void Destroy(Stack *s) {
	s->maxSize = -1;
	free(s->element);
	s->top = -1;
}

//clear
void Clear(Stack* s) {
	s->top = -1;
}

bool IsFULL(Stack *s) {
	return s->top == s->maxSize - 1;
}

bool IsEmpty(Stack *s) {
	return s->top == -1;
}

bool Top(Stack* s, ElemType* x) {
	if (IsEmpty(s))	//¿ÕÕ»´¦Àí
		return 0;
	*x = s->element[s->top];
	return 1;
}

bool push(Stack *s,ElemType x) {
	if (IsFULL(s))
		return 0;
	s->top++;
	s->element[s->top] = x;
	return 1;
}

bool pop(Stack* s)
{
	if (IsEmpty)
		return false;
	s->top--;
	return true;
}

