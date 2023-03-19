#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2   //����
#define Underflow 3  //����
#define NotPresent 4 //������
#define Duplicats 5  //�ظ�

typedef int Status;
typedef int ElemType; //�������������

//definition of sequential representation
typedef struct seqList
{
	int n;
	int maxLength;
	ElemType* element;
} SeqList;

//initialization
Status Init(SeqList* h, int mSize)
{
	h->maxLength = mSize;
	h->n = 0;
	h->element = (ElemType*)malloc(sizeof(ElemType)*mSize); //��̬����һά����ռ�
	if (!h->element) //�ж�ָ���Ƿ�Ϊ��
		return ERROR;
	return OK;
}

//check
Status Find(SeqList h, int i, ElemType *x)
{
	if (i<0 || i>h.n - 1)
		return ERROR;
	*x = h.element[i]; //ȡ��element[i]��ֵͨ������x����
	return OK;
}


//insert
Status Insert(SeqList* h, int i, ElemType x)
{
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	if (h->n == h->maxLength) //�жϴ���ռ��Ƿ�����
		return ERROR;
	for (j = h->n - 1; j > i; j--)
		h->element[j + 1] = h->element[j];
	h->element[i + 1] = x;
	h->n = h->n + 1;
	return OK;
}

//delete
Status Delete(SeqList* h, int i)
{
	int j;
	if (i<-1 || i>h->n - 1)
		return ERROR;
	if (!h->n ) //˳����Ƿ�Ϊ��
		return ERROR;
	for (j = i+1; j < h->n; j++)
		h->element[j - 1] = h->element[j];
	h->n--;
	return OK;
}

//output
Status Output(SeqList *h)
{
	int i;
	if (h->n == 0)
		return ERROR;
	for (i = 0; i <= h->n - 1; i++)
		printf("%d", h->element[i]);
	printf("\n");
	return OK;
}

//destroy �ͷų�ʼ�������ж�̬���������Ԫ�ش���ռ䣬��ֹ�ڴ�й©
void Destroy(SeqList* h)
{
	h->n = 0;
	h->maxLength = 0;
	free(h->element);
}

//���ڲ��Ե�������
void main()
{
	int i;
	SeqList list;
	Init(&list, 10);
	for (i = 0; i < 10; i++)
		Insert(&list, i - 1, i);
	Output(&list);
	Delete(&list, 5);
	Insert(&list, -1, 9);
	Output(&list);
	Destroy(&list);
}