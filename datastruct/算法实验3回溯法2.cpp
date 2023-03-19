//Backtrack(int i)算法的时间复杂度是O(n*2^n)

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
	void Backtrack(int i);  //找到最接近第一艘轮船载重c1的最佳装载方案，
							//最优载重值bestw，最优解数组bestx。
	int n;      //集装箱数目 
	int* x;     //当前解 
	int* bestx; //当前最优解
	T* w;       //集装箱重量数组
	T c1;       //第一艘船的容量
	T c2;       //第二艘船的容量
	T cw;       //当前第一艘船的载重量
	T bestw;    //当前第一艘船的最优载重量
	T r;        //剩余集装箱重量 
};

//构造函数
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
		r += w[i];       //初始化r 
	}
	total = r;          //初始化total 
}

template<class T>
void Loading<T>::Backtrack(int i)
{
	if (i > n) //判断是否达到叶子节点
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
	//搜索子树 
	r = r - w[i];
	if (cw + w[i] <= c1) //判断该集装箱到底放不放
	{//搜索左子树 
		x[i] = 1;
		cw = cw + w[i];
		Backtrack(i + 1);
		//当节点i的子树延伸结束时要返回i节点
		cw = cw - w[i];
	}
	if (cw + r > bestw) //判断先不放该集装箱后是否还有可行解
	{//搜索右子树 
		x[i] = 0;
		Backtrack(i + 1);
	}
	r = r + w[i];//当节点i的子树延伸结束时要返回i节点
}  //由于bestx可能被更新O(2^n)次，计算出一个bestw的时间是O(n)，因此该算法的时间复杂度是O(n*2^n)

template<class T>
void Loading<T>::Backtrack()
{
	Backtrack(1);
}

template<class T>
void Loading<T>::Show()
{
	int totalW = 0;
	int c1W = 0;     //第一艘船总载重
	int i;

	for (i = 1; i <= n; i++)
	{
		if (bestx[i] == 1) c1W += w[i];
		totalW += w[i];
	}
	if (totalW - c1W > c2)
	{
		cout << "  没有合理的装载方案!" << endl;
		return;
	}

	cout << "  最优解(第一艘船)：(";
	for (i = 1; i < n; i++) cout << bestx[i] << ",";
	cout << bestx[i] << ")" << endl;
	cout << "  最优解(第二艘船)：(";
	for (i = 1; i < n; i++) cout << !bestx[i] << ",";
	cout << !bestx[i] << ")" << endl;

	cout << "  装载方案如下: " << endl;
	cout << "  第一艘船装载:" << endl;
	for (i = 1; i <= n; i++)
		if (bestx[i] == 1) cout << "    集装箱" << i << ": " << setw(2) << w[i] << endl;
	cout << "     总载重: " << c1W;
	if (c1 - c1W == 0) cout << "，装满！" << endl;
	else cout << "，剩余载重量" << c1 - c1W << "！" << endl;

	cout << "  第二艘船装载:" << endl;
	for (i = 1; i <= n; i++)
		if (!bestx[i] == 1) cout << "    集装箱" << i << ": " << setw(2) << w[i] << endl;
	cout << "     总载重: " << totalW - c1W;
	if (c2 - (totalW - c1W) == 0) cout << "，装满！" << endl;
	else cout << "，剩余载重量" << c2 - (totalW - c1W) << "！" << endl;

}

void main()
{
	int C1, C2, n, Total;

	cout << "数据来源实验3的举例(1)：" << endl;
	C1 = C2 = 50; n = 3;
	int w1[] = { 0,10,40,40 };
	cout << "     i= 0  1  2  3" << endl;
	cout << "  w1[]={0,10,40,40}; C1=C2=50; n=3" << endl;
	Loading<int> L1(w1, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "\n  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L1.Backtrack();
		L1.Show();         //船1: 1(10)、2(40)   总载重：50
	}                     //船2: 3(40)          总载重：40
	cout << endl;

	cout << "数据来源实验3的举例(2)：" << endl;
	C1 = C2 = 50; n = 3;
	int w2[] = { 0,20,40,40 };
	cout << "  w2[]={0,20,40,40}; C1=C2=50; n=3" << endl;
	Loading<int> L2(w2, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L2.Backtrack();
		L2.Show();         //没有合理的装载方案!
	}
	cout << endl;

	cout << "数据来源实验3的测试用例(1)：" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w3[] = { 0,22,35,24,19,04 };
	cout << "  w3[]={0,22,35,24,19,04}; C1=60; C2=40; n=5" << endl;
	Loading<int> L3(w3, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L3.Backtrack();
		L3.Show();         //没有合理的装载方案!
	}
	cout << endl;

	cout << "数据来源实验3的测试用例(2)：" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w4[] = { 0,22,35,24,15,04 };
	cout << "  w4[]={0,22,35,24,15,04}; C1=60; C2=40; n=5" << endl;
	Loading<int> L4(w4, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L4.Backtrack();
		L4.Show();         //没有合理的装载方案!
	}
	cout << endl;

	cout << "数据来源实验3的测试用例(3)：" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w5[] = { 0,22,35,24,15,03 };
	cout << "     i= 0  1  2  3  4  5" << endl;
	cout << "  w5[]={0,22,35,24,15,03}; C1=60; C2=40; n=5" << endl;
	Loading<int> L5(w5, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L5.Backtrack();
		L5.Show();         //船1: 1(22)、2(35)、5(03)   总载重：60
	}                     //船2: 3(24)、4(15)          总载重：39
	cout << endl;

	cout << "数据来源实验3的测试用例(3-1)：" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w6[] = { 0,21,35,23,15,03 };
	cout << "     i= 0  1  2  3  4  5" << endl;
	cout << "  w6[]={0,21,35,23,15,03}; C1=60; C2=40; n=5" << endl;
	Loading<int> L6(w6, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L6.Backtrack();
		L6.Show();         //船1: 1(21)、2(35)、5(03)   总载重：59
	}                     //船2: 3(23)、4(15)          总载重：38
	cout << endl;

	cout << "数据来源实验3的测试用例(4)：" << endl;
	C1 = 60; C2 = 40; n = 5;
	int w7[] = { 0,22,35,24,18,01 };
	cout << "     i= 0  1  2  3  4  5" << endl;
	cout << "  w7[]={0,22,35,24,18,01}; C1=60; C2=40; n=5" << endl;
	Loading<int> L7(w7, n, C1, C2, Total);
	if (Total > C1 + C2) cout << "  集装箱总重量(" << Total << ")超过两艘船的装载量(" << C1 + C2 << ")！" << endl;
	else
	{
		L7.Backtrack();
		L7.Show();         //船1: 2(35)、3(24)、5(01)   总载重：60
	}                      //船2: 1(22)、4(18)          总载重：40
	cout << endl;

}