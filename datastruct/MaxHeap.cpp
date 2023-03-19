#include"MaxHeap.h"

void AdjustDown(ElementType heap[], int current, int border) {	//当前位置current，边界下标border
	int p = current;
	int maxChild;
	ElementType temp;
	while (2 * p + 1 <= border) {	//p为非叶节点
		if ((2 * p + 2 <= border) && (heap[2 * p + 1] < heap[2 * p + 2]))	//右孩子存在且比左孩子较大
			maxChild = 2 * p + 2;
		else
			maxChild = 2 * p + 1;
		if (heap[p] >= heap[maxChild])
			break;
		else{
			temp = heap[p];
			heap[p] = heap[maxChild];
			heap[maxChild] = temp;
			p = maxChild;	//设置下轮待考察元素位置
		}
	}
}