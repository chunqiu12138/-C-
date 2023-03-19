//习题7-10-用备忘录算法求LCS
//备忘录方法是动态规划法的一个变种，它采用分治法思想，自顶向下直接递 归 求最优解。
//但与分治法不同的是，备忘录方法为每个已经计算的子问题建立备忘录，即保存子问题的计
//算结果以备需要时引用，从而避免子问题的重复求解。
//试改写当前程序的int LCS::LCSLength()函数，用备忘录方法来求解最长公共子序列。
//提示：备忘录方法采用的是递归求解方式，因此需要用一个公有成员函数int LCSLength()
//来调用私有递归成员函数int LCSLength(int i,int j); 共同实现。
#include<iostream>

using namespace std;

class LCS
{
public:
    LCS(int nx, int ny, char* a, char* b);
    ~LCS();
    int LCSLength();                 //求c和s数组，返回LCS的长度
    int LCSLength_Memo();            //备忘录算法求c和s数组，返回LCS长度，非递归函数
    void CLCS();                     //构造LCS，非递归

private:
    int LCSLength_Memo(int i, int j); //备忘录算法求c和s数组，返回LCS长度，递归函数
    void CLCS(int i, int j);         //构造LCS，递归
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

//求c和s数组，返回LCS的长度
int LCS::LCSLength()
{
    for (int i = 0; i <= m; i++) c[i][0] = 0; //初始化行标或列标为0的元素
    for (int j = 1; j <= n; j++) c[0][j] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (x[i] == y[j]) //由c[i-1][j-1]得到c[i][j]
            {
                c[i][j] = c[i - 1][j - 1] + 1; s[i][j] = 1;
            }
            else
                if (c[i - 1][j] >= c[i][j - 1]) //由c[i-1][j]得到c[i][j]
                {
                    c[i][j] = c[i - 1][j]; s[i][j] = 2;
                }
                else //由c[i][j-1]得到c[i][j]
                {
                    c[i][j] = c[i][j - 1]; s[i][j] = 3;
                }
    return c[m][n]; //返回最优解值
}

void LCS::CLCS()                     //构造LCS，非递归
{
    CLCS(m, n);
}

void LCS::CLCS(int i, int j)          //构造LCS，递归
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

//备忘录算法求c和s数组，返回LCS长度
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
    cout << "1. 不用备忘录算法求LCS的长度:" << endl;
    len1 = LL.LCSLength();                      //长度为4
    cout << "   LCS的长度=" << len1 << endl << endl;
    
    cout << "2. 用备忘录算法求LCS的长度:" << endl;
    len2 = LL.LCSLength_Memo();                 //长度为4
    cout << "   LCS的长度=" << len2 << endl << endl;
    cout << "3. LCS=\"";                         //LCS="bcba"
    LL.CLCS();
    cout << "\"" << endl;
    
}

