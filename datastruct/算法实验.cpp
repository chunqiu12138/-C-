#include<iostream>

using namespace std;

class SortableList {
	public:
		SortableList(int mSize) {
			maxSize = mSize;
			l = new int[maxSize];
			n = 0; //数组中已有元素个数
		}
		~SortableList() {
			delete[]l;
		}
		void Input();
		void Output();
		void MergeSort();

	private:
		void MergeSort(int left, int right);
		void Merge(int left, int mid, int right);
		int* l;
		int maxSize;
		int n;
};

void SortableList::Input() {
 	cout << "请输入待排元素个数: " ;
	int size = 0;
	cin >> size;
	this->n = size;
	cout << endl;
	cout << "请输入待排序列: ";
	for (int i = 0; i < this->n; ++i)
		cin >> l[i];
	cout << endl;
}

void SortableList::Output(){
	cout << "当前序列为: ";
	for (int i = 0; i < this->n; ++i)
		cout << l[i]<<" ";
	cout << endl;
}

void SortableList::MergeSort(){
	MergeSort(0, n - 1);
}

void SortableList::MergeSort(int left, int right){
	if (left < right){
		int mid = (left + right) / 2;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, mid, right);
	}
}

void SortableList::Merge(int left, int mid, int right){
	int* temp = new int[right - left + 1];
	int i = left, j = mid + 1, k = 0;
	while ((i <= mid) && (j <= right))
		if (l[i] <= l[j]) temp[k++] = l[i++];
		else temp[k++] = l[j++];
	while (i <= mid) temp[k++] = l[i++];
	while (j <= right) temp[k++] = l[j++];
	for (i = 0, k = left; k <= right;) l[k++] = temp[i++];
}

int main() {
	SortableList t1(100);
	t1.Input();
	t1.MergeSort();
	t1.Output();
}