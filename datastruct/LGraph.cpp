#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"queue.h"
#define MAX_VEXNUM 30//����������
#define INTMAX 1000

int visited[MAX_VEXNUM];

typedef int ElemType;
/*�߽ڵ�Ķ���*/
typedef struct eNode {
    int adjVex;         //�ڽӵ��±�
    ElemType Weight;  //��Ȩ�� 
    struct eNode* next;    //ָ����һ���ڽӵ��ָ�� 
}ENode;

/*ͼ�Ķ���*/
typedef struct lGraph {
    int n;  //ͼ��ǰ������
    int e;  //ͼ��ǰ����
    ENode** a;  //ָ��һάָ������
}LGraph;

/*��ʼ���ڽ�ͼ*/
bool CreateGraph(LGraph *lg,int nSize){ 
    int i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));    //��̬���ɳ���Ϊn��һάָ������
    if(!lg->a)
        return 0;
    for(i = 0; i < lg->n; i++)
        lg->a[i] = NULL;    //��ָ���������
    return 1;
}

/*��������ͼ�ߵĲ���*/
bool InsertEdge(LGraph *lg, int u,int v,ElemType w){     //u��vΪ������ͬq�Ҳ������Ľڵ㣬wΪ�ߵ�Ȩ
    if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
        return false;
    ENode* NewNode;
    /*Ϊu�����µ��ڽӵ�*/
    NewNode = (ENode*)malloc(sizeof(ENode));
    NewNode->adjVex = v;
    NewNode->Weight = w;
    NewNode->next = lg->a[u];   //���µ��ڽӵ���뵥�������ǰ��
    lg->a[u] = NewNode;
 
    //Ϊv�����µ��ڽӵ�
    NewNode = (ENode*)malloc(sizeof(ENode));
    NewNode->adjVex = u;
    NewNode->Weight = w;
    NewNode->next = lg->a[v];   //���µ��ڽӵ���뵥�������ǰ��
    lg->a[v] = NewNode;
 
    lg->e++;
    return 1;
}

/*�����������*/
void DFS(LGraph *lg, ElemType v,int visited[]){   //�������v
    ENode* w;
    visited[v] = 1;
    printf("%d ", v);
    for (w = lg->a[v]; w; w = w->next) {
        if (!visited[w->adjVex]) {
            DFS(lg, w->adjVex,visited);
        }
    }
}

/*�����������*/
void BFS(LGraph* lg, ElemType v, int visited[]){
    ENode* w;
    Queue q;
    create(&q, lg->n);
    visited[v] = 1;
    printf("%d ",v);
    EnQueue(&q, v);
    while (!IsEmpty(&q)) {
        Front(&q, &v);
        DeQueue(&q);
        for (w = lg->a[v];w;w=w->next){
            if(!visited[w->adjVex]){
                visited[w->adjVex] = 1;
                printf("%d ", w->adjVex);
                EnQueue(&q, w->adjVex);
            }
        }
    }
}

int FindMin(int dist[],int s[],int n){
    int i,minpos;
    ElemType min;
    min = INTMAX;
    for (i = 1; i <n; i++) {
        if (!s[i] && dist[i] < min) {
            min = dist[i];
            minpos = i;
        }
    }
    if (min < INTMAX) /* ���ҵ���Сdist */
        return minpos; /* ���ض�Ӧ�Ķ����±� */
    else return 0;  /* �������Ķ��㲻���ڣ����ش����� */
}

int FindMin(int dist[],int n) {
    int i, minpos;
    ElemType min;
    min = INTMAX;
    for (i = 1; i < n; i++) {
        if (dist[i] && dist[i] < min) {
            min = dist[i];
            minpos = i;
        }
    }
    if (min < INTMAX) /* ���ҵ���Сdist */
        return minpos; /* ���ض�Ӧ�Ķ����±� */
    else return -1;  /* �������Ķ��㲻���ڣ����ش����� */
}

bool Dijkstra(LGraph *lg, ElemType dist[], int path[], int v){
    int s[8] = {0};
    ENode *w;
    int h;
    /* ��ʼ�����˴�Ĭ�ϲ����ڵı���INTMAX��ʾ */
    for (w = lg->a[v];w;w=w->next){
        dist[w->adjVex] = w->Weight;
        if (dist[w->adjVex] < INTMAX)
            path[w->adjVex] = v;
        else
            path[w->adjVex] = -1;
    }
    /* �Ƚ�������뼯�� */
    dist[v] = 0;
    s[v] = true;

    while (1) {
        /*δ����¼������dist��С��*/
        h = FindMin(dist, s, lg->n);
        if (h == 0) /* ��������h������ */
            break;      /* �㷨���� */
        s[h] = true;
        for (w = lg->a[h]; w; w = w->next) /* ��ͼ�е�ÿ������w */
            /* ��w��h���ڽӵ㲢��δ����¼ */
            if (s[w->adjVex] == false && w->Weight < INTMAX) {
                /* ����¼Vʹ��dist[W]��С */
                if (dist[h] + w->Weight < dist[w->adjVex]) {
                    dist[w->adjVex] = dist[h] + w->Weight;
                    path[w->adjVex] = h; /* ����S��W��·�� */
                }
            }
    } /* while����*/
    return true; /* �㷨ִ����ϣ�������ȷ��� */
}

void Prim(LGraph *lg,int v){
    int dist[8] = { INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX };
    int close[8] = { 0,0,0 ,0 ,0 ,0 ,0 ,0 };
    ENode* w;
    int h,i;
    /* ��ʼ�����˴�Ĭ�ϲ����ڵı���INTMAX��ʾ */
    for (w = lg->a[v]; w; w = w->next) {
        dist[w->adjVex] = w->Weight;
        close[w->adjVex] = v;
    }
    /*��¼���*/
    dist[v] = 0;
    close[v] = -1;

    while (1) {
        /*δ����¼������dist��С��*/
        h = FindMin(dist, lg->n);
        if (h == -1) /* ��������h������ */
            break;      /* �㷨���� */
        /*��¼*/
        dist[h] = 0;
        
        for (w = lg->a[h]; w; w = w->next) /* ��ͼ�е�ÿ������w */
            /* ��w��h���ڽӵ㲢��δ����¼ */
            if (dist[w->adjVex]  && w->Weight < INTMAX) {
                /* ����¼Vʹ��dist[W]��С */
                if ( w->Weight < dist[w->adjVex]) {
                    dist[w->adjVex] =  w->Weight;
                    close[w->adjVex] = h; /* ����S��W��·�� */
                }
            }
    } /* while����*/
    for (int i = 1; i < lg->n; i++)
        printf("%3d ", i);
    printf("\n");
    for (int i = 1; i < lg->n; i++)
        printf("%3d ", close[i]);
}

void Kraskal() {

}

int main() {
    LGraph* lg=(LGraph*)malloc(sizeof(LGraph));
    CreateGraph(lg, 8);
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
    /*Dijkstra
    int dist[8] = { INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX };
    int path[8] = { -1,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 };
    Dijkstra(lg,dist,path,1);
    for (int i = 1; i < 8; i++)
        printf("%d ", dist[i]);
    printf("\n");
    for (int i = 1; i < 8; i++)
        printf("%d ", path[i]);
    */
    Prim(lg,1);
}