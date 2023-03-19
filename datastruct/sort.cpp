#include<iostream>
#include"MaxHeap.h"

using namespace std;

typedef int ElemType;

void Swap(ElemType *a,ElemType *b){
	ElemType tem=*a;
	*a = *b;
	*b = tem;
}

void BubbleSort(ElemType A[],int N){
	int i, p;
	for (p = N - 1; p >= 0;p--){
		bool flag= 0;
		for (i = 0; i < p; i++){	//һ��ð��
			if (A[i] > A[i + 1]){
				Swap(&A[i],&A[i+1]);
				flag = 1;
			}
		}
		if(!flag)	break;
	}
}

void InsertSort(ElemType A[],int N){
	int i, p;
	for (p = 1; p < N;p++) {
		ElemType insertItem = A[p];
		for (i = p; i > 0 && A[i - 1] > insertItem; i--)
			A[i] = A[i - 1];	//�Ƴ���λ
		A[i] = insertItem;
	}
}

void ShellSort(ElemType A[],int N){
	int D, i, p;
	for (D = N / 2; D > 0;D/=2){	//ϣ����������
		for (p = D; p < N; p++) {	//��������
			ElemType insertItem = A[p];
			for (i = p; i >= D && A[i - D] > insertItem; i-=D)
				A[i] = A[i - D];	//�Ƴ���λ
			A[i] = insertItem;
		}
	}
}

void HeapSort(ElementType A[],int N){
	int i;
	for (i = (N - 2) / 2; i >= 0; i--)	//�����һ�����ڵ㿪ʼ�����������Ϊ����
		AdjustDown(A, i, N - 1);
	for (i = N - 1; i > 0; i--){	//iָ��ǰ�ѵ�Ԫ��
		Swap(&A[0],&A[i]);
		AdjustDown(A, 0, i - 1);
	}
}

void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{ /* �������A[L]~A[R-1]��A[R]~A[RightEnd]�鲢��һ���������� */
	int LeftEnd, NumElements, Tmp;
	LeftEnd = R - 1; /* ����յ�λ�� */
	Tmp = L;         /* �������е���ʼλ�� */
	NumElements = RightEnd - L + 1;
	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++]; /* �����Ԫ�ظ��Ƶ�TmpA */
		else
			TmpA[Tmp++] = A[R++]; /* ���ұ�Ԫ�ظ��Ƶ�TmpA */
	}
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++]; /* ֱ�Ӹ������ʣ�µ� */
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++]; /* ֱ�Ӹ����ұ�ʣ�µ� */
}

void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{ /* �����鲢������������ */
	int i, j;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);
	if (i + length < N) /*�鲢���2������*/
		Merge(A, TmpA, i, i + length, N - 1);
	else /* ���ֻʣ1������*/
		for (j = i; j < N; j++) TmpA[j] = A[j];
}

void MergeSort(ElemType A[], int N) {
	int length = 1;
	ElemType* TmpA = (ElemType*)malloc(N * sizeof(ElemType));
	if (TmpA != NULL) {
		while (length < N) {
			Merge_pass(A, TmpA, N, length);
			length *= 2;
			Merge_pass(TmpA, A, N, length);
			length *= 2;
		}
		free(TmpA);
	}
	else printf("�ռ䲻��");
}

void Quick_Sort(ElementType A[],int L,int R){
	int i = L, j = R ;
	if(L<R){
		int pivot=A[j];
		i = L - 1;
		while(1){
			while (A[++i] < pivot);
			while (A[--j] > pivot);
			if (i < j)
				Swap(&A[i], &A[j]);
			else break;
		}
		Swap(&A[i], &A[R]);
		Quick_Sort(A, L, i - 1);
		Quick_Sort(A, i + 1, R);
	}
}

void QuickSort(ElemType A[],int N) {
	Quick_Sort(A,0,N-1);
}

int getMax(ElemType A[], int n){
	int max = A[0];
	for (int i = 0; i < n; i++){
		if (A[i] > max){
			max = A[i];
		}
	}
	return max;
}

void countsort(ElemType A[],int N,int exp) {
	ElemType* output = (ElemType*)malloc(N * sizeof(ElemType));
	int buckets[10] = { 0 };
	int i;
	for (i = 0; i < N;i++) {
		buckets[A[i] / exp % 10]++;
	}
	for (i = 1; i < 10;i++) {
		buckets[i] += buckets[i - 1];
	}
	for (i = N - 1; i >= 0;i--){
		output[buckets[(A[i] / exp )% 10] - 1] = A[i];
		buckets[A[i] / exp % 10]--;
	}
	for (i = 0; i < N; i++) {
		A[i] = output[i];
	}
}

void RadixSort(ElemType A[],int N) {
	int exp;
	int max = getMax(A, N);
	for (exp = 1; max / exp > 0; exp *= 10) {
		countsort(A, N, exp);
	}
}

int main(){
	/*
	ElemType A[8] = { 5,9,8,0,99,13,14,15 };
	BubbleSort(A, 8);
	for(int i=0;i<8;i++)
		cout << A[i]<<" ";
	cout << "A" <<endl;

	ElemType B[8] = { 5,9,8,0,99,13,14,15 };
	InsertSort(B,8);
	for (int i = 0; i < 8; i++)
		cout <<B[i] << " ";
	cout << "B" << endl;

	ElemType C[8] = { 5,9,8,0,99,13,14,15 };
	ShellSort(C, 8);
	for (int i = 0; i < 8; i++)
		cout << C[i] << " ";
	cout << "C" << endl;
	
	ElemType D[8] = { 5,9,8,0,99,13,14,15 };
	HeapSort(D, 8);
	for (int i = 0; i < 8; i++)
		cout << D[i] << " ";
	cout << "D" << endl;

	ElemType E[8] = { 5,9,8,0,99,13,14,15 };
	MergeSort(E, 8);
	for (int i = 0; i < 8; i++)
		cout << E[i] << " ";
	cout <<"E" << endl;
	*/

	ElemType F[8] = { 2,5,4,3,1 };
	QuickSort(F, 5);
	for (int i = 0; i < 5; i++)
		cout << F[i] << " ";
	cout << "F" << endl;

	/*
	ElemType G[8] = {5,9,8,0,99,13,14,15};
	RadixSort(G, 8);
	for (int i = 0; i < 8; i++)
		cout << G[i] << " ";
	cout << "G" << endl;
	*/
}


