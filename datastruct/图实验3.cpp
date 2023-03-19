#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define Overflow 2    //��ʾ����
#define Underflow 3   //��ʾ����
#define NotPresent 4  //��ʾԪ�ز�����
#define Duplicate 5   //��ʾ���ظ�Ԫ��
typedef int ElemType;
typedef int Status;

//�ڽӾ���Ľṹ�嶨��
typedef struct {
    ElemType** a;     //�ڽӾ���
    int n;            //ͼ�ĵ�ǰ������
    int e;            //ͼ�ĵ�ǰ����
    ElemType noEdge;  //��������ޱ�ʱ��ֵ
}mGraph;


//�ڽӾ���ĳ�ʼ��
Status Init(mGraph* mg, int nSize, ElemType noEdgeValue) {
    int i, j;
    mg->n = nSize;               //��ʼ��������
    mg->e = 0;                   //��ʼ��ʱû�б�
    mg->noEdge = noEdgeValue;    //��ʼ��û�б�ʱ��ȡֵ
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*));  //���ɳ���Ϊn��һάָ������
    if (!mg->a) return ERROR;
    for (i = 0; i < mg->n; i++) {   //��̬���ɶ�ά����
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType));
        for (j = 0; j < mg->n; j++) {
            mg->a[i][j] = mg->noEdge;  //��ʼ��ʱȨ�ض���Ϊ-1
        }
        mg->a[i][i] = 0;        //�Ի�·����Ϊ0
    }
    return OK;
}


//�ڽӾ���ĳ���(�ĳ���int�ͣ��з���ֵ),���ͷ�һά����,���ͷ�ָ������
int Destory(mGraph* mg) {
    int i;
    for (i = 0; i < mg->n; i++) {
        free(mg->a[i]);  //�ͷ�n��һά����Ĵ洢�ռ�
    }
    free(mg->a);         //�ͷ�һά����Ĵ洢�ռ�
    return 1;
}


//�ڽӾ���ıߵ�����
Status Exist(mGraph* mg, int u, int v) {
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge) return ERROR;
    return OK;
}


//�ڽӾ���ıߵĲ���
Status Insert(mGraph* mg, int u, int v, ElemType w) {
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v) return ERROR;
    if (mg->a[u][v] != mg->noEdge) return Duplicate;  //����������Ѵ���,�򷵻س�����Ϣ
    mg->a[u][v] = w;                                 //�����±�
    mg->e++;                                        //����һ����
    return OK;
}


//�ڽӾ���ıߵ�ɾ��
Status Remove(mGraph* mg, int u, int v) {
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v) return ERROR;
    if (mg->a[u][v] == mg->noEdge) return NotPresent;  //����ɾ���߲�����,�򷵻س�����Ϣ
    mg->a[u][v] = mg->noEdge;                         //ɾ����
    mg->e--;
    return OK;
}



int main() {
    mGraph* lg = NULL;
    Init(lg, 8);
    InsertEdge(lg, 3, 6, 5);
    InsertEdge(lg, 3, 1, 4);
    InsertEdge(lg, 1, 4, 1);
    InsertEdge(lg, 1, 2, 2);
    InsertEdge(lg, 2, 4, 3);
    InsertEdge(lg, 2, 5, 10);
    InsertEdge(lg, 4, 3, 2);
    InsertEdge(lg, 4, 5, 7);
    InsertEdge(lg, 4, 6, 8);
    InsertEdge(lg, 4, 7, 4);
    InsertEdge(lg, 5, 7, 6);
    InsertEdge(lg, 7, 6, 1);
}