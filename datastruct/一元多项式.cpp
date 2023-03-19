//ͷ�������ṹ�嶨��
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

//һԪ����ʽ�Ĵ���
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

//һԪ����ʽ�����
void Output(polynominal* p){
    pNode* q = p->head->link;  //qָ��p�ĵ�һ�����
    while(q->exp!=-1){      //��qָ��p��ͷ���ʱ����ѭ��
        printf("%dX^%d",q->coef,q->exp);
        if(q->link->exp != -1&&q->link->coef>0) printf("+");    //����Ӻ�
        q = q->link;
    }
}

//һԪ����ʽ�����
void Add(polynominal* px, polynominal* qx) {
    pNode *q, *q1 = qx->head, *p, *temp;    //q1ָ��ͷ���
    p = px->head->link;                       //pָ�����ʽpx�ĵ�һ�����
    q = q1->link;                            //q1��q��ǰ��
    while (p->exp >= 0) {
        while (p->exp < q->exp) {               //����q->exp�����
            q1 = q;
            q = q->link;
        }
        if (p->exp == q->exp) {                 //��ָ�����ʱ,ϵ�����
            q->coef = q->coef + p->coef;
            if (q->coef == 0) {                 //����Ӻ�ϵ��Ϊ0
                q1->link = q->link;           //ɾ��q
                free(q);                      //�ͷ�q�Ŀռ�
                q = q1->link;                 //����qָ��
                p = p->link;
            }
            else {                             //����Ӻ�ϵ����Ϊ0
                q1 = q;                       //q1����
                q = q->link;
                p = p->link;                  //pҲ����
            }
        }
        else {                                 //p->exp > q->exp�����
            temp = (pNode*)malloc(sizeof(pNode));     //��p��ϵ����ָ�������½��
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link;
            p = p->link;
        }
    }
}

//һԪ����ʽ�ĳ���
void Destroy(polynominal* p) {
    pNode* q = p->head->link,*m;
    while (q->exp!=-1){
        m = q->link;
        free(q);
        q= m;
    }
    free(p->head);
}

//һԪ����ʽ�˷�(��˽��������qx)
void Multiply(polynominal* px, polynominal* qx) {
    pNode* p, * q, *m, *pre, *last;
    polynominal *pn1, *pn2=NULL;
    pn1= (polynominal*)malloc(sizeof(polynominal));     //���ɶ���ʽpn1���ڴ���������˽��
    pn1->head = (pNode*)malloc(sizeof(pNode));
    pn1->head->exp = -1;
    pn1->head->link = pn1->head;
    p = px->head->link;        //pָ��px�ĵ�һ���ڵ�
    while(p->exp!=-1){          //����px��ÿ���ڵ�
        pn2 = (polynominal*)malloc(sizeof(polynominal));     //���ɶ���ʽpn2���ڴ���ÿһ����˽��
        pn2->head = (pNode*)malloc(sizeof(pNode));
        pn2->head->exp = -1;
        pn2->head->link = pn2->head;
        q = qx->head->link;    //qָ��qx��һ���ڵ�
        while(q->exp != -1){    //����qx��ÿ���ڵ�
            m=(pNode*)malloc(sizeof(pNode));     //���浱ǰp��pָ��Ľڵ����˽��
            m->coef = p->coef * q->coef;
            m->exp = p->exp + q->exp;
            pre = pn2->head;   //nָ��pn2��ͷ���
            last = pn2->head->link;
            while (last && last->exp > m->exp) {    //Ѱ��m���ڵ�λ��
                pre = last;
                last = last->link;
            }
            if (m->exp==last->exp){          //m��ָ������pn2���Ѵ���
                if (m->coef == -last->coef) {       //m��last��ϵ����Ϊ��
                    pre->link = last->link;
                    free(m);
                    free(last);
                }
                else {              //��last��ϵ������m��ϵ��
                    last->coef += m->coef;
                    free(m);
                }
            }
            else{                  //��m�ڵ�������ʽpn2
                pre->link = m;
                m->link = last;
            }
            q = q->link;    //��pָ��ָ����һ���ڵ�
        }
        Add(pn2,pn1);       //����һ��ѭ���Ľ��
        p = p->link;        //��qָ��ָ����һ���ڵ�
    }
    *qx=*pn1;
}

//���ڲ��Ե�������
int main() {
    polynominal* p = (polynominal*)malloc(sizeof(polynominal));
    polynominal* q = (polynominal*)malloc(sizeof(polynominal));
    int choose=1;
    printf("�������һ������ʽ:\n");
    Create(p);
    Output(p);
    printf("\n\n������ڶ�������ʽ:\n");
    Create(q);
    Output(q);
    printf("\n\n��ѡ����һ��(0:add  1:mutiply  other:exit):\n");
    scanf_s("%d", &choose);
    switch (choose) {                                   //ѡ��ӷ����ǳ˷�����
        case 0:
            printf("��ӵĽ����:\n");
            Add(p, q);
            Output(q);
            break;
        case 1:
            printf("��˵Ľ����:\n");
            Multiply(p, q);
            Output(q);
            break;
        default:
            break;
    }
    Destroy(p);                     //�ͷ��ڴ�
    Destroy(q);
    return 0;
}