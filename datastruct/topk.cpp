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
	int Select(int k);

private:
	void Swap(int i, int j); //�����±�Ϊ i �� j ������Ԫ��
	void InsertSort(int left,int right);	//��������
	int Partition(int left, int right);
	int Select(int k, int left, int right, int r);
	int* l;
	int maxSize;
	int n;
	int k;
};

void SortableList::Input() {
	cout << "�������ѡ��Ԫ�ظ���: ";
	int j = 0;
	cin >> j;
	n = j;
	cout << endl;
	cout << "�������ѡ��������: ";
	for (int i = 0; i < n; ++i) {
		cin >> l[i];
	}
	cout << endl;
	cout << "������ѡ���kС��ֵ: ";
	cin >> j;
	k = j ;
}

void SortableList::Output() {
	int j = Select(k);
	cout << "��ǰ���е�kС����Ϊ: ";
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
			l[i] = l[i - 1];	//�Ƴ���λ
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
{ //ÿ������r��Ԫ�أ�Ѱ�ҵ�kСԪ�� 
	int n = right - left + 1;
	if (n <= r) //�������㹻С��ʹ��ֱ�Ӳ������� 
	{
		InsertSort(left, right);
		return left + k - 1; //ȡ���еĵ�kСԪ�أ����±�Ϊleft+k-1 
	}
	for (int i = 1; i <= n / r; i++)
	{
		InsertSort(left + (i - 1) * r, left + i * r - 1);
		//����ȡ�й�����ÿ����м�ֵ 
		Swap(left + i - 1, left + (i - 1) * r + (int)ceil((double)r / 2) - 1);
		//��ÿ����м�ֵ�������ӱ�ǰ�����д�� 
	}
	int j = Select((int)ceil((double)n / r / 2), left, left + (n / r) - 1, r);
	//������м�ֵ�����±�Ϊj 
	Swap(left, j); //�����м�ֵΪ��ŦԪ��������left�� 
	j = Partition(left, right); //�Ա��ӱ����зֻ����� 
	if (k == j - left + 1) return j; //���ص�kСԪ���±� 
	else if (k < j - left + 1)
		return Select(k, left, j - 1, r);//�����ӱ����kСԪ�� 
	else
		return Select(k - (j - left + 1), j + 1, right, r);
	//�����ӱ����k-(j-left+1)СԪ�� 
}

int main() {
	SortableList t1(100);
	t1.Input();
	t1.Output();
}