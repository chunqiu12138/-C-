#include<stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define NotPresent -1
#define NeverUsed -99	//Ԫ��Ϊ�ձ��

typedef int ElementType;

typedef struct hashTable {
	int M;	//ɢ�б���
	int num;	//	��ǰɢ�б���Ԫ�ظ���
	bool* empty;	//empty�������
	ElementType* elements;	//Ԫ������
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

//����ɢ�б�
void DestroytHT(HashTable* ht) {
	free(ht->empty);
	free(ht->elements);
}

//���ɢ�б�
void ClearHT(HashTable *ht) {
	int i;
	ht->num = 0;
	for ( i = 0; i < ht->M; i++){
		ht->empty[i] = TRUE;
		ht->elements[i] = NeverUsed;
	}
}

//�ж�ɢ�б��Ƿ�����������������TRUE�����򷵻�FALSE
bool IsFull(HashTable *ht) {
	if (ht->num == ht->M)
		return TRUE;
	else
		return FALSE;
}

//�ж�ɢ�б��Ƿ��ѿգ����ѿշ���TRUE�����򷵻�FALSE
bool IsEmpty(HashTable* ht) {
	if (ht->num == 0)
		return TRUE;
	else
		return FALSE;
}

/*
//���ڳ�����������ɢ�к���
int Hash(int M, int Key) {
	return Key % M;
}
*/
int Hash(int M, int Key) {
	return Key % 11;
}

//��ɢ�б�ht�в��ҹؼ�ֵΪkey�ĺ���
int Search(HashTable *ht,int key) {
	int anchor, pos;
	anchor = pos = Hash(ht->M,key);		//����key�Ļ���ַ
	do {
		if (ht->empty[pos])		//�ж�̽������Ƿ�ﵽ��λ�ã����ǣ�����NotPresent
			return NotPresent;
		if (ht->elements[pos] == key)	//��������key��ȵĹؼ��֣���������λ��
			return pos;
		pos = (pos + 1) % ht->M;
	} while (pos != anchor);	//��pos==anchorʱ��������������������ɢ�б�
	return NotPresent;		//������������δ�ҵ�key
}

//��ɢ�б��в���ؼ���ֵΪkey��Ԫ��
bool Insert(HashTable *ht,int key) {
	int i, anchor;
	if (IsFull(ht))
		return FALSE;
	if (Search(ht, key) != NotPresent)	//��������Ԫ���Ѵ��ڣ�����ʧ��
		return FALSE;
	i = anchor = Hash(ht->M, key);		//����key�Ļ���ַ
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


