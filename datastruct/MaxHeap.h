#ifndef MAXHEAP_H
#define MAXHEAP_H

typedef int ElementType;

typedef struct maxHeap{
	ElementType* eleements;
	int	n;	//¶ÑÔªËØ¸öÊý
}MaxHeap;

void AdjustDown(ElementType heap[], int current, int border);

#endif

