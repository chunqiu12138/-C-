#include"MaxHeap.h"

void AdjustDown(ElementType heap[], int current, int border) {	//��ǰλ��current���߽��±�border
	int p = current;
	int maxChild;
	ElementType temp;
	while (2 * p + 1 <= border) {	//pΪ��Ҷ�ڵ�
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] < heap[2 * p + 2]))	//�Һ��Ӵ����ұ����ӽϴ�
			maxChild = 2 * p + 2;
		else
			maxChild = 2 * p + 1;
		if (heap[p] >= heap[maxChild])
			break;
		else{
			temp = heap[p];
			heap[p] = heap[maxChild];
			heap[maxChild] = temp;
			p = maxChild;	//�������ִ�����Ԫ��λ��
		}
	}
}