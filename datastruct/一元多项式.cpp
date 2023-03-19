//头函数及结构体定义
#include<stdio.h>
#include<stdlib.h>

typedef struct pNode{
    int coef;
    int exp;
    struct pNode* link;
} pNode;

typedef struct{
    struct pNode* head;
} polynominal;

//一元多项式的创建
void Create(polynominal* p) {
    pNode* pn, * pre, * q;
    p->head = (pNode*)malloc(sizeof(pNode));
    p->head->exp = -1;
    p->head->link = p->head;        
    for (;;) {
        pn = (pNode*)malloc(sizeof(pNode));
        printf("coef:\n");
        scanf_s("%d", &pn->coef);
        printf("exp:\n");
        scanf_s("%d", &pn->exp);
        if (pn->exp < 0) break;
        pre = p->head;
        q = p->head->link;
        while (q && q->exp > pn->exp) {
            pre = q;
            q = q->link;
        }
        pn->link = q;
        pre->link = pn;
    }
}

//一元多项式的输出
void Output(polynominal* p){
    pNode* q = p->head->link;  //q指向p的第一个结点
    while(q->exp!=-1){      //当q指向p的头结点时结束循环
        printf("%dX^%d",q->coef,q->exp);
        if(q->link->exp != -1&&q->link->coef>0) printf("+");    //输出加号
        q = q->link;
    }
}

//一元多项式的相加
void Add(polynominal* px, polynominal* qx) {
    pNode *q, *q1 = qx->head, *p, *temp;    //q1指表头结点
    p = px->head->link;                       //p指向多项式px的第一个结点
    q = q1->link;                            //q1是q的前驱
    while (p->exp >= 0) {
        while (p->exp < q->exp) {               //跳过q->exp大的项
            q1 = q;
            q = q->link;
        }
        if (p->exp == q->exp) {                 //当指数相等时,系数相加
            q->coef = q->coef + p->coef;
            if (q->coef == 0) {                 //若相加后系数为0
                q1->link = q->link;           //删除q
                free(q);                      //释放q的空间
                q = q1->link;                 //重置q指针
                p = p->link;
            }
            else {                             //若相加后系数不为0
                q1 = q;                       //q1后移
                q = q->link;
                p = p->link;                  //p也后移
            }
        }
        else {                                 //p->exp > q->exp的情况
            temp = (pNode*)malloc(sizeof(pNode));     //以p的系数和指数生成新结点
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link;
            p = p->link;
        }
    }
}

//一元多项式的撤销
void Destroy(polynominal* p) {
    pNode* q = p->head->link,*m;
    while (q->exp!=-1){
        m = q->link;
        free(q);
        q= m;
    }
    free(p->head);
}

//一元多项式乘法(相乘结果保存在qx)
void Multiply(polynominal* px, polynominal* qx) {
    pNode* p, * q, *m, *pre, *last;
    polynominal *pn1, *pn2=NULL;
    pn1= (polynominal*)malloc(sizeof(polynominal));     //生成多项式pn1用于储存最终相乘结果
    pn1->head = (pNode*)malloc(sizeof(pNode));
    pn1->head->exp = -1;
    pn1->head->link = pn1->head;
    p = px->head->link;        //p指向px的第一个节点
    while(p->exp!=-1){          //遍历px的每个节点
        pn2 = (polynominal*)malloc(sizeof(polynominal));     //生成多项式pn2用于储存每一趟相乘结果
        pn2->head = (pNode*)malloc(sizeof(pNode));
        pn2->head->exp = -1;
        pn2->head->link = pn2->head;
        q = qx->head->link;    //q指向qx的一个节点
        while(q->exp != -1){    //遍历qx的每个节点
            m=(pNode*)malloc(sizeof(pNode));     //储存当前p和p指向的节点的相乘结果
            m->coef = p->coef * q->coef;
            m->exp = p->exp + q->exp;
            pre = pn2->head;   //n指向pn2的头结点
            last = pn2->head->link;
            while (last && last->exp > m->exp) {    //寻找m所在的位置
                pre = last;
                last = last->link;
            }
            if (m->exp==last->exp){          //m的指数项在pn2中已存在
                if (m->coef == -last->coef) {       //m和last的系数和为零
                    pre->link = last->link;
                    free(m);
                    free(last);
                }
                else {              //将last的系数加上m的系数
                    last->coef += m->coef;
                    free(m);
                }
            }
            else{                  //将m节点加入多项式pn2
                pre->link = m;
                m->link = last;
            }
            q = q->link;    //将p指针指向下一个节点
        }
        Add(pn2,pn1);       //保存一趟循环的结果
        p = p->link;        //将q指针指向下一个节点
    }
    *qx=*pn1;
}

//用于测试的主函数
int main() {
    polynominal* p = (polynominal*)malloc(sizeof(polynominal));
    polynominal* q = (polynominal*)malloc(sizeof(polynominal));
    int choose=1;
    printf("请输入第一个多项式:\n");
    Create(p);
    Output(p);
    printf("\n\n请输入第二个多项式:\n");
    Create(q);
    Output(q);
    printf("\n\n请选择下一步(0:add  1:mutiply  other:exit):\n");
    scanf_s("%d", &choose);
    switch (choose) {                                   //选择加法还是乘法功能
        case 0:
            printf("相加的结果是:\n");
            Add(p, q);
            Output(q);
            break;
        case 1:
            printf("相乘的结果是:\n");
            Multiply(p, q);
            Output(q);
            break;
        default:
            break;
    }
    Destroy(p);                     //释放内存
    Destroy(q);
    return 0;
}