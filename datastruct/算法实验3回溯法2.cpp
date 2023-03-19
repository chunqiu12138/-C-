//Backtrack(int i)�㷨��ʱ�临�Ӷ���O(n*2^n)

#include <iostream>
#include <iomanip>
using namespace std;

template<class T>
class Loading
{
public:
	Loading(T* W, int num, T C1, T C2, T& total);
	~Loading()
	{
		delete[]x; delete[]bestx; delete[]w;
	}
	void Backtrack();
	void Show();
private:
	void Backtrack(int i);  //�ҵ���ӽ���һ���ִ�����c1�����װ�ط�����
							//��������ֵbestw�����Ž�����bestx��
	int n;      //��װ����Ŀ 
	int* x;     //��ǰ�� 
	int* bestx; //��ǰ���Ž�
	T* w;       //��װ����������
	T c1;       //��һ�Ҵ�������
	T c2;       //�ڶ��Ҵ�������
	T cw;       //��ǰ��һ�Ҵ���������
	T bestw;    //��ǰ��һ�Ҵ�������������
	T r;        //ʣ�༯װ������ 
};

//���캯��
template<class T>
Loading<T>::Loading(T* W, int num, T C1, T C2, T& total)
{
	int i;

	n = num;   c1 = C1;   c2 = C2;   bestw = 0;	   cw = 0;
	x = new T[n + 1];  			bestx = new T[n + 1]; 			w = new T[n + 1];
	r = 0;
	for (i = 1; i <= n; i++)
	{
		w[i] = W[i];
		r += w[i];       //��ʼ��r 
	}
	total = r;          //��ʼ��total 
}

template<class T>
void Loading<T>::Backtrack(int i)
{
	if (i > n) //�ж��Ƿ�ﵽҶ�ӽڵ�
	{
		if (cw > bestw)
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];
				bestw = cw;
			}
		}
		return;
	}
	//�������� 
	r = r - w[i];
	if (cw + w[i] <= c1) //�жϸü�װ�䵽�׷Ų���
	{//���������� 
		x[i] = 1;
		cw = cw + w[i];
		Backtrack(i + 1);
		//���ڵ�i�������������ʱҪ����i�ڵ�
		cw = cw - w[i];
	}
	if (cw + r > bestw) //�ж��Ȳ��Ÿü�װ����Ƿ��п��н�
	{//���������� 
		x[i] = 0;
		Backtrack(i + 1);
	}
	r = r + w[i];//���ڵ�i�������������ʱҪ����i�ڵ�
}  //����bestx���ܱ�����O(2^n)�Σ������һ��bestw��ʱ����O(n)����˸��㷨��ʱ�临�Ӷ���O(n*2^n)

template<class T>
void Loading<T>::Backtrack()
{
	Backtrack(1);
}

template<class T>
void Loading<T>::Show()
{
	int totalW = 0;
	int c1W = 0;     //��һ�Ҵ�������
	int i;

	for (i = 1; i <= n; i++)
	{
		if (bestx[i] == 1) c1W += w[i];
		totalW += w[i];
	}
	if (totalW - c1W > c2)
	{
		cout << "  û�к����װ�ط���!" << endl;
		return;
	}

	cout << "  ���Ž�(��һ�Ҵ�)��(";
	for (i = 1; i < n; i++) cout << bestx[i] << ",";
	cout << bestx[i] << ")" << endl;
	cout << "  ���Ž�(�ڶ��Ҵ�)��(";
	for (i = 1; i < n; i++) cout << !bestx[i] << ",";
	cout << !bestx[i] << ")" << endl;

	cout << "  װ�ط�������: " << endl;
	cout << "  ��һ�Ҵ�װ��:" << endl;
	for (i = 1; i <= n; i++)
		if (bestx[i] == 1) cout << "    ��װ��" << i << ": " << setw(2) << w[i] << endl;
	cout << "     ������: " << c1W;
	if (c1 - c1W == 0) cout << "��װ����" << endl;
	else cout << "��ʣ��������" << c1 - c1W << "��" << endl;

	cout << "  �ڶ��Ҵ�װ��:" << endl;
	for (i = 1; i <= n; i++)
		if (!bestx[i] == 1) cout << "    ��װ��" << i << ": " << setw(2) << w[i] << endl;
	cout << "     ������: " << totalW - c1W;
	if (c2 - (totalW - c1W) == 0) cout << "��װ����" << endl;
	else cout << "��ʣ��������" << c2 - (totalW - c1W) << "��" << endl;

}

void main()
{
	int C1, C2, n, Total;

	cout << "������Դʵ��3�ľ���(1)��" << endl;
	C1 = C2 = 50; n = 3;
	int w1[] = { 0,10,40,40 };
	cout << "     i= 0  1  2  3" << endl;
	cout << "  w1[]={0,10,40,40}; C1=C2=50; n=3" << endl;
	Loading<int> L1(w1, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "\n  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L1.Backtrack();
		L1.Show();         //��1: 1(10)��2(40)   �����أ�50
	}                     //��2: 3(40)          �����أ�40
	cout << endl;

	cout << "������Դʵ��3�ľ���(2)��" << endl;
	C1 = C2 = 50; n = 3;
	int w2[] = { 0,20,40,40 };
	cout << "  w2[]={0,20,40,40}; C1=C2=50; n=3" << endl;
	Loading<int> L2(w2, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L2.Backtrack();
		L2.Show();         //û�к����װ�ط���!
	}
	cout << endl;

	cout << "������Դʵ��3�Ĳ�������(1)��" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w3[] = { 0,22,35,24,19,04 };
	cout << "  w3[]={0,22,35,24,19,04}; C1=60; C2=40; n=5" << endl;
	Loading<int> L3(w3, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L3.Backtrack();
		L3.Show();         //û�к����װ�ط���!
	}
	cout << endl;

	cout << "������Դʵ��3�Ĳ�������(2)��" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w4[] = { 0,22,35,24,15,04 };
	cout << "  w4[]={0,22,35,24,15,04}; C1=60; C2=40; n=5" << endl;
	Loading<int> L4(w4, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L4.Backtrack();
		L4.Show();         //û�к����װ�ط���!
	}
	cout << endl;

	cout << "������Դʵ��3�Ĳ�������(3)��" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w5[] = { 0,22,35,24,15,03 };
	cout << "     i= 0  1  2  3  4  5" << endl;
	cout << "  w5[]={0,22,35,24,15,03}; C1=60; C2=40; n=5" << endl;
	Loading<int> L5(w5, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L5.Backtrack();
		L5.Show();         //��1: 1(22)��2(35)��5(03)   �����أ�60
	}                     //��2: 3(24)��4(15)          �����أ�39
	cout << endl;

	cout << "������Դʵ��3�Ĳ�������(3-1)��" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w6[] = { 0,21,35,23,15,03 };
	cout << "     i= 0  1  2  3  4  5" << endl;
	cout << "  w6[]={0,21,35,23,15,03}; C1=60; C2=40; n=5" << endl;
	Loading<int> L6(w6, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L6.Backtrack();
		L6.Show();         //��1: 1(21)��2(35)��5(03)   �����أ�59
	}                     //��2: 3(23)��4(15)          �����أ�38
	cout << endl;

	cout << "������Դʵ��3�Ĳ�������(4)��" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w7[] = { 0,22,35,24,18,01 };
	cout << "     i= 0  1  2  3  4  5" << endl;
	cout << "  w7[]={0,22,35,24,18,01}; C1=60; C2=40; n=5" << endl;
	Loading<int> L7(w7, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  ��װ��������(" << Total << ")�������Ҵ���װ����(" << C1 + C2 << ")��" << endl;
	else
	{
		L7.Backtrack();
		L7.Show();         //��1: 2(35)��3(24)��5(01)   �����أ�60
	}                      //��2: 1(22)��4(18)          �����أ�40
	cout << endl;

}