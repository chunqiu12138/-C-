#include<iostream>

using namespace std;

class SortableList {
	public:
		SortableList(int mSize) {
			maxSize = mSize;
			l = new int[maxSize];
			n = 0; //����������Ԫ�ظ���
		}
		~SortableList() {
			delete[]l;
		}
		void Input();
		void Output();
		void QuickSort();

	private:
		void Swap(int i, int j); //�����±�Ϊ i �� j ������Ԫ��
		void QuickSort(int left, int right);
		int Partition(int left, int right);
		int* l;
		int maxSize;
		int n;
};

void SortableList::Input() {
 	cout << "���������Ԫ�ظ���: " ;
	int size = 0;
	cin >> size;
	this->n = size;
	cout << endl;
	cout << "�������������: ";
	for (int i = 0; i < this->n; ++i)
		cin >> l[i];
	cout << endl;
}

void SortableList::Output() {
	cout << "��ǰ����Ϊ: ";
	for (int i = 0; i < this->n; ++i)
		cout << l[i] << " ";
	cout << endl;
}

void SortableList::Swap(int i, int j)
{
	int c = l[i];
	l[i] = l[j];
	l[j] = c;
}

int SortableList::Partition(int left, int right)
{
	int i = left, j = right + 1;
	do {
		do i++; while (l[i] < l[left]);
		do j--; while (l[j] > l[left]);
		if (i < j) Swap(i, j);
	} while (i < j);
	Swap(left, j);
	return j;
}

void SortableList::QuickSort(){
	QuickSort(0, n - 1);
}

void SortableList::QuickSort(int left, int right){
	if (left < right){
		int j = Partition(left, right);
		QuickSort(left, j - 1);
		QuickSort(j + 1, right);
	}
}

int main() {
	SortableList t1(100);
	t1.Input();
	t1.QuickSort();
	t1.Output();
}