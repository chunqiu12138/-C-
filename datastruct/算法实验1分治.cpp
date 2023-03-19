//ϰ��7-10-�ñ���¼�㷨��LCS
//����¼�����Ƕ�̬�滮����һ�����֣������÷��η�˼�룬�Զ�����ֱ�ӵ� �� �����Ž⡣
//������η���ͬ���ǣ�����¼����Ϊÿ���Ѿ�����������⽨������¼��������������ļ�
//�����Ա���Ҫʱ���ã��Ӷ�������������ظ���⡣
//�Ը�д��ǰ�����int LCS::LCSLength()�������ñ���¼�������������������С�
//��ʾ������¼�������õ��ǵݹ���ⷽʽ�������Ҫ��һ�����г�Ա����int LCSLength()
//������˽�еݹ��Ա����int LCSLength(int i,int j); ��ͬʵ�֡�
#include<iostream>

using namespace std;

class LCS
{
public:
    LCS(int nx, int ny, char* a, char* b);
    ~LCS();
    int LCSLength();                 //��c��s���飬����LCS�ĳ���
    int LCSLength_Memo();            //����¼�㷨��c��s���飬����LCS���ȣ��ǵݹ麯��
    void CLCS();                     //����LCS���ǵݹ�

private:
    int LCSLength_Memo(int i, int j); //����¼�㷨��c��s���飬����LCS���ȣ��ݹ麯��
    void CLCS(int i, int j);         //����LCS���ݹ�
    int** c, ** s, m, n;
    char* x, * y;
};

LCS::LCS(int nx, int ny, char* a, char* b)
{
    m = nx;    n = ny;
    x = a;     y = b;
    c = new int* [m + 1];   s = new int* [m + 1];
    for (int i = 0; i <= m; i++)
    {
        c[i] = new int[n + 1];
        s[i] = new int[n + 1];
    }
}

LCS::~LCS()
{
    for (int i = 0; i <= m; i++)
    {
        delete[]c[i];   delete[]s[i];
    }
    delete[]c;   delete[]s;
}

//��c��s���飬����LCS�ĳ���
int LCS::LCSLength()
{
    for (int i = 0; i <= m; i++) c[i][0] = 0; //��ʼ���б���б�Ϊ0��Ԫ��
    for (int j = 1; j <= n; j++) c[0][j] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (x[i] == y[j]) //��c[i-1][j-1]�õ�c[i][j]
            {
                c[i][j] = c[i - 1][j - 1] + 1; s[i][j] = 1;
            }
            else
                if (c[i - 1][j] >= c[i][j - 1]) //��c[i-1][j]�õ�c[i][j]
                {
                    c[i][j] = c[i - 1][j]; s[i][j] = 2;
                }
                else //��c[i][j-1]�õ�c[i][j]
                {
                    c[i][j] = c[i][j - 1]; s[i][j] = 3;
                }
    return c[m][n]; //�������Ž�ֵ
}

void LCS::CLCS()                     //����LCS���ǵݹ�
{
    CLCS(m, n);
}

void LCS::CLCS(int i, int j)          //����LCS���ݹ�
{
    if(i == 0 || j == 0) return;
    if (x[i] == y[j])
    {
        CLCS(i - 1, j - 1);
        cout << x[i];
    }
    else
        if (c[i - 1][j] >= c[i][j - 1]) CLCS(i - 1, j);
        else CLCS(i, j - 1);
}                                     //O(m+n)

//����¼�㷨��c��s���飬����LCS����
int LCS::LCSLength_Memo()
{
    return LCSLength_Memo(m, n);
}

int LCS::LCSLength_Memo(int i, int j)
{
    if (i == 0 || j == 0) return 0;
    if (c[i][j] != 0) return c[i][j];
    else
        if (x[i] == y[j])
        {
            c[i][j] = LCSLength_Memo(i - 1, j - 1) + 1; s[i][j] = 1;
        }
        else
            if (LCSLength_Memo(i - 1, j) >= LCSLength_Memo(i, j - 1))
            {
                c[i][j] = LCSLength_Memo(i - 1, j); c[i][j] = 2;
            }
            else
            {
                c[i][j] = LCSLength_Memo(i, j - 1); s[i][j] = 3;
            }
    return c[i][j];
}

void main()
{
    int nx = 7, ny = 6, len1, len2;
    char* x = (char*)"0abcbdab", * y = (char*)"0bdcaba";

    LCS LL(nx, ny, x, y);
    cout << "x[]=\"0abcbdab\"; y[]=\"0bdcaba\"" << endl << endl;
    cout << "1. ���ñ���¼�㷨��LCS�ĳ���:" << endl;
    len1 = LL.LCSLength();                      //����Ϊ4
    cout << "   LCS�ĳ���=" << len1 << endl << endl;
    
    cout << "2. �ñ���¼�㷨��LCS�ĳ���:" << endl;
    len2 = LL.LCSLength_Memo();                 //����Ϊ4
    cout << "   LCS�ĳ���=" << len2 << endl << endl;
    cout << "3. LCS=\"";                         //LCS="bcba"
    LL.CLCS();
    cout << "\"" << endl;
    
}

