#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2   //上溢
#define Underflow 3  //下溢
#define NotPresent 4 //不存在
#define Duplicats 5  //重复

typedef int Status;
typedef int ElemType; //储存的数据类型

//defination of node
typedef struct node
{
	ElemType elemment;
	struct node* link;
}Node;

//defination of headerList
typedef struct headerList
{
	Node* head;
	int n;
}headerList;

//initiation
Status Init(headerList * h)//构造一个空的单链表
{
	h->head = NULL;
	h->n = 0;
	return OK;
}

//check
Status Find(headerList h, int i, ElemType* x)
{
	Node* p;
	int j;
	if (i<0 || i>h.n - 1)
		return ERROR;
	p = h.head;
	for (j = 0; j < i; j++)//从头结点开始查找ai
		p = p->link;
	*x = p->elemment; //取出element[i]的值通过参数x返回
	return OK;
}

//insert
Status Insert(headerList* h, int i, ElemType x)
{
	Node * p, * q;
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	p = h->head;
	for (j = 0; j < i; j++) 
		p = p->link;        //从头结点开始查找ai
	q = (Node*)malloc(sizeof(Node));  //生成新节点q
	q->elemment = x;
	if (i > -1)
	{
		q->link = p->link;
		p->link = q;
	}
	else
	{
		q->link = h->head;
		h->head = q;
	}
	h->n++;
	return OK;
}

//delete
Status Delete(headerList* h, int i)
{
	int j;
	Node * p, * q;
	if (i<-1 || i>h->n - 1)//是否越界
		return ERROR;
	if (!h->n) //单链表是否为空
		return ERROR;
	q = h->head;
	p = h->head;
	for (j = 0; j < i - 1; j++)//查找ai的前驱
		q = q->link;
	if (i == 0)
		h->head = h->head->link;
	else {
		p = q->link;  //p指向ai
		q->link = p->link;
	}
	free(p);
	h->n--;
	return OK;
}

//output
Status Output(headerList* h)
{
	Node* p;
	if (!h->n )
		return ERROR;
	p = h->head;
	while (p)
	{
		printf("%d ", p->elemment);
		p = p->link;
	}
	return OK;
}

//destroy 
void Destroy(headerList* h)
{
	Node* p;
	while (h->head)
	{
		p = h->head->link;
		free(h->head);
		h->head = p;
	}
}

//用于测试的主函数
void main()
{
	int i;
	int x;
	headerList list;
	Init(&list);
	for (i = 0; i < 9; i++)
		Insert(&list, i - 1, i);
	printf("the linklist is:");
	Output(&list);
	Delete(&list, 0);
	printf("\nthe linklist is:");
	Output(&list);
	Find(list, 5, &x);
	printf("\nthe value is;");
	printf("%d", x);
	Destroy(&list);
}