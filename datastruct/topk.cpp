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
	int Select(int k);

private:
	void Swap(int i, int j); //交换下标为 i 和 j 的数组元素
	void InsertSort(int left,int right);	//插入排序
	int Partition(int left, int right);
	int Select(int k, int left, int right, int r);
	int* l;
	int maxSize;
	int n;
	int k;
};

void SortableList::Input() {
	cout << "请输入待选择元素个数: ";
	int j = 0;
	cin >> j;
	n = j;
	cout << endl;
	cout << "请输入待选择排序列: ";
	for (int i = 0; i < n; ++i) {
		cin >> l[i];
	}
	cout << endl;
	cout << "请输入选择第k小的值: ";
	cin >> j;
	k = j ;
}

void SortableList::Output() {
	int j = Select(k);
	cout << "当前序列第k小的数为: ";
	cout << l[j] ;
	cout << endl;
}

void SortableList::Swap(int i, int j){
	int c = l[i];
	l[i] = l[j];
	l[j] = c;
}

void SortableList::InsertSort(int left, int right) {
	for (int j = left+1; j <= right; j++) {
		int insertItem = l[j];
		int i = j;
		for (; i > 0 && l[i - 1] > insertItem; i--)
			l[i] = l[i - 1];	//移出空位
		l[i] = insertItem;
	}
}

int SortableList::Partition(int left, int right){
	int i = left, j = right + 1;
	do {
		do i++; while (l[i] < l[left]);
		do j--; while (l[j] > l[left]);
		if (i < j) Swap(i, j);
	} while (i < j);
	Swap(left, j);
	return j;
}

int SortableList::Select(int k) {
	return Select(k,0,n-1,5);
}

int SortableList::Select(int k, int left, int right, int r)
{ //每个分组r个元素，寻找第k小元素 
	int n = right - left + 1;
	if (n <= r) //若问题足够小，使用直接插入排序 
	{
		InsertSort(left, right);
		return left + k - 1; //取其中的第k小元素，其下标为left+k-1 
	}
	for (int i = 1; i <= n / r; i++)
	{
		InsertSort(left + (i - 1) * r, left + i * r - 1);
		//二次取中规则求每组的中间值 
		Swap(left + i - 1, left + (i - 1) * r + (int)ceil((double)r / 2) - 1);
		//将每组的中间值交换到子表前部集中存放 
	}
	int j = Select((int)ceil((double)n / r / 2), left, left + (n / r) - 1, r);
	//求二次中间值，其下标为j 
	Swap(left, j); //二次中间值为枢纽元，并换至left处 
	j = Partition(left, right); //对表（子表）进行分划操作 
	if (k == j - left + 1) return j; //返回第k小元素下标 
	else if (k < j - left + 1)
		return Select(k, left, j - 1, r);//在左子表求第k小元素 
	else
		return Select(k - (j - left + 1), j + 1, right, r);
	//在右子表求第k-(j-left+1)小元素 
}

int main() {
	SortableList t1(100);
	t1.Input();
	t1.Output();
}