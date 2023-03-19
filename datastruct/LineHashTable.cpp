#include<stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define NotPresent -1
#define NeverUsed -99	//元素为空标记

typedef int ElementType;

typedef struct hashTable {
	int M;	//散列表长度
	int num;	//	当前散列表储存元素个数
	bool* empty;	//empty标记数组
	ElementType* elements;	//元素数组
}HashTable;


void CreatHT(HashTable* ht, int size) {
	int i;
	ht->M = size;
	ht->num =0;
	ht->empty = (bool*)malloc(sizeof(bool) * size);
	ht->elements = (ElementType*)malloc(sizeof(ElementType) * size);
	for ( i = 0; i < size; i++){
		ht->empty[i] = TRUE;
		ht->elements[i] = NeverUsed;
	}
}

//销毁散列表
void DestroytHT(HashTable* ht) {
	free(ht->empty);
	free(ht->elements);
}

//清空散列表
void ClearHT(HashTable *ht) {
	int i;
	ht->num = 0;
	for ( i = 0; i < ht->M; i++){
		ht->empty[i] = TRUE;
		ht->elements[i] = NeverUsed;
	}
}

//判断散列表是否已满，若已满返回TRUE，否则返回FALSE
bool IsFull(HashTable *ht) {
	if (ht->num == ht->M)
		return TRUE;
	else
		return FALSE;
}

//判断散列表是否已空，若已空返回TRUE，否则返回FALSE
bool IsEmpty(HashTable* ht) {
	if (ht->num == 0)
		return TRUE;
	else
		return FALSE;
}

/*
//基于除留余数法的散列函数
int Hash(int M, int Key) {
	return Key % M;
}
*/
int Hash(int M, int Key) {
	return Key % 11;
}

//在散列表ht中查找关键值为key的函数
int Search(HashTable *ht,int key) {
	int anchor, pos;
	anchor = pos = Hash(ht->M,key);		//计算key的基地址
	do {
		if (ht->empty[pos])		//判断探查过程是否达到空位置，若是，返回NotPresent
			return NotPresent;
		if (ht->elements[pos] == key)	//若存在与key相等的关键字，返回所在位置
			return pos;
		pos = (pos + 1) % ht->M;
	} while (pos != anchor);	//若pos==anchor时，表明已完整搜索整个散列表
	return NotPresent;		//遍历结束，但未找到key
}

//在散列表中插入关键字值为key的元素
bool Insert(HashTable *ht,int key) {
	int i, anchor;
	if (IsFull(ht))
		return FALSE;
	if (Search(ht, key) != NotPresent)	//若待插入元素已存在，插入失败
		return FALSE;
	i = anchor = Hash(ht->M, key);		//计算key的基地址
	do{
		if (ht->elements[i]==NeverUsed) {
			ht->elements[i] = key;
			ht->empty[i] = FALSE;
			ht->num++;
			return TRUE;
		}
		i = (i + 1) % ht->M;
	} while (i != anchor);
	return FALSE;
}

bool Delete (HashTable * ht, int key){
	if (IsEmpty(ht))
		return FALSE;
	int pos = Search(ht, key);
	if (pos == NotPresent)
		return FALSE;
	else{
		ht->elements[pos] = NeverUsed;
		ht->num--;
		return TRUE;
	}
}

void Output(HashTable* ht) {
	int i;
	for (i = 0;i<ht->M;i++)
		printf("%5d", ht->elements[i]);
	printf("\n");
	for (i = 0; i < ht->M; i++)
		printf("%5d", ht->empty[i]);
	printf("\n");
}

int main() {
	HashTable* T = (HashTable*)malloc(sizeof(HashTable));
	CreatHT(T,13);
	Insert(T, 47);
	Insert(T, 7);
	Insert(T, 29);
	Insert(T, 11);
	Insert(T, 9);
	Insert(T, 84);
	Insert(T, 54);
	Insert(T, 20);
	Insert(T, 30);
	Output(T);
}


