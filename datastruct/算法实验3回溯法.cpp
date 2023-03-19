#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

//�ж������ʺ��Ƿ���ͬһ�л���ͬһб����
bool Place(int k, int i, int* x)
{
    for (int j = 0; j < k; j++)
        if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
            return false;
    return true;
}

//�ݹ麯�������n�ʺ����⣩
void NQueens(int k, int n, int* x,bool& flag)
{
    for (int i = 0; i < n; i++)  //��ʽԼ���ĵ�һ�ֹ۵㣬x[k] = 0,1,������,n-1
    {
        if (Place(k, i, x))  //Լ������
        {
            x[k] = i;
            if (k == n - 1)
            {
                for (i = 0; i < n; i++)
                    cout << x[i] << " ";  //���һ�����н�
                flag = true;
            }
            else
            {
                NQueens(k + 1, n, x,flag);  //������Ƚ�����һ��
            }
        }
        if (flag)
        {
            return;
        }
    }
}

void NQueens(int n, int* x)
{
    bool flag = false;
    NQueens(0, n, x,flag);
}

int main()
{
    int queens[8];  //8�ʺ�
    for (int i = 0; i < 8; i++)
        queens[i] = -1;
    NQueens(8, queens);
    return 0;
}
