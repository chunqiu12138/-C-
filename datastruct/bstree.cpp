#include<stdio.h>
#include <stdlib.h>

typedef int EelemType;

typedef int KeyType;

typedef struct entry {
	KeyType	Key;
	EelemType Data;
}Entry;

typedef struct bstnode {
	Entry element;
	struct bstnode *Lchild, *Rchild;
}*Bintree;

Bintree RecSearchBST(Bintree T,KeyType k) {
	while (T){
		if (k > T->element.Key)
			T = T->Rchild;
		else if (k < T->element.Key)
			T = T->Lchild;
		else
			return T;
	}
	return NULL;
}

/*
bool InsertBST(Bintree T,Entry e) {
	Bintree p=NULL;
	while (T) {
		Bintree p = T;
		if(e.Key<T->element.Key)
			T = T->Rchild;
		else if (e.Key > T->element.Key)
			T = T->Lchild;
		else
{
			printf("duplicate");
			return 0;
		}
	}
	T = (Bintree)malloc(sizeof(*Bintree));
	T->element = e;
	T->Lchild = NULL;
	T->Rchild = NULL;
	if (!p)
		return true;
	else if (p->element.Key > T->element.Key)
		p->Lchild = T;
	else if (p->element.Key < T->element.Key)
		p->Rchild = T;
	return true;
}
*/

Bintree InsertBST(Bintree T, Entry e) {
	if (!T) {
		T = (Bintree)malloc(sizeof(*T));
		T->element = e;
		T->Lchild = NULL;
		T->Rchild = NULL;
		return T;
	}
	if (e.Key > T->element.Key)
		T->Rchild = InsertBST(T,e);
	else if (e.Key < T->element.Key)
		T->Lchild = InsertBST(T, e);
}

Bintree DeletBstnode(Bintree T,entry e){
	Bintree tmp;
	if (!T)
		printf("not found");
	else if (e.Key < T->element.Key)
		T->Lchild = DeletBstnode(T, e);
	else if (e.Key > T->element.Key)
		T->Lchild = DeletBstnode(T, e);
	else if (T->Lchild && T->Rchild)		//�ҵ�Ҫɾ���Ľڵ㣬�Ҹýڵ���������������
	{
		Bintree tmp = FindMin(T->Rchild);
		T->element = tmp->element;
		T->Rchild = DeletBstnode(T->Rchild, T->element);
		//ɾ������������С�ڵ�
	}
	else {		//ɾ���ڵ�ֻ��һ�������ӽڵ�
		tmp = T;
		if (!T->Rchild)
			T = T->Rchild;
		else if (!T->Lchild)
			T = T->Lchild;
		free(tmp);
	}
	return T;
}