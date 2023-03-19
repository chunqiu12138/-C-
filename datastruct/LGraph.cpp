#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"queue.h"
#define MAX_VEXNUM 30//顶点最大个数
#define INTMAX 1000

int visited[MAX_VEXNUM];

typedef int ElemType;
/*边节点的定义*/
typedef struct eNode {
    int adjVex;         //邻接点下标
    ElemType Weight;  //边权重 
    struct eNode* next;    //指向下一个邻接点的指针 
}ENode;

/*图的定义*/
typedef struct lGraph {
    int n;  //图当前顶点数
    int e;  //图当前边数
    ENode** a;  //指向一维指针数组
}LGraph;

/*初始化邻接图*/
bool CreateGraph(LGraph *lg,int nSize){ 
    int i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));    //动态生成长度为n的一维指针数组
    if(!lg->a)
        return 0;
    for(i = 0; i < lg->n; i++)
        lg->a[i] = NULL;    //将指针数组空置
    return 1;
}

/*有向（无向）图边的插入*/
bool InsertEdge(LGraph *lg, int u,int v,ElemType w){     //u，v为两个不同q且不相连的节点，w为边的权
    if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
        return false;
    ENode* NewNode;
    /*为u建立新的邻接点*/
    NewNode = (ENode*)malloc(sizeof(ENode));
    NewNode->adjVex = v;
    NewNode->Weight = w;
    NewNode->next = lg->a[u];   //将新的邻接点插入单链表的最前面
    lg->a[u] = NewNode;
 
    //为v建立新的邻接点
    NewNode = (ENode*)malloc(sizeof(ENode));
    NewNode->adjVex = u;
    NewNode->Weight = w;
    NewNode->next = lg->a[v];   //将新的邻接点插入单链表的最前面
    lg->a[v] = NewNode;
 
    lg->e++;
    return 1;
}

/*深度优先搜索*/
void DFS(LGraph *lg, ElemType v,int visited[]){   //搜索起点v
    ENode* w;
    visited[v] = 1;
    printf("%d ", v);
    for (w = lg->a[v]; w; w = w->next) {
        if (!visited[w->adjVex]) {
            DFS(lg, w->adjVex,visited);
        }
    }
}

/*宽度优先搜索*/
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
    if (min < INTMAX) /* 若找到最小dist */
        return minpos; /* 返回对应的顶点下标 */
    else return 0;  /* 若这样的顶点不存在，返回错误标记 */
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
    if (min < INTMAX) /* 若找到最小dist */
        return minpos; /* 返回对应的顶点下标 */
    else return -1;  /* 若这样的顶点不存在，返回错误标记 */
}

bool Dijkstra(LGraph *lg, ElemType dist[], int path[], int v){
    int s[8] = {0};
    ENode *w;
    int h;
    /* 初始化：此处默认不存在的边用INTMAX表示 */
    for (w = lg->a[v];w;w=w->next){
        dist[w->adjVex] = w->Weight;
        if (dist[w->adjVex] < INTMAX)
            path[w->adjVex] = v;
        else
            path[w->adjVex] = -1;
    }
    /* 先将起点收入集合 */
    dist[v] = 0;
    s[v] = true;

    while (1) {
        /*未被收录顶点中dist最小者*/
        h = FindMin(dist, s, lg->n);
        if (h == 0) /* 若这样的h不存在 */
            break;      /* 算法结束 */
        s[h] = true;
        for (w = lg->a[h]; w; w = w->next) /* 对图中的每个顶点w */
            /* 若w是h的邻接点并且未被收录 */
            if (s[w->adjVex] == false && w->Weight < INTMAX) {
                /* 若收录V使得dist[W]变小 */
                if (dist[h] + w->Weight < dist[w->adjVex]) {
                    dist[w->adjVex] = dist[h] + w->Weight;
                    path[w->adjVex] = h; /* 更新S到W的路径 */
                }
            }
    } /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}

void Prim(LGraph *lg,int v){
    int dist[8] = { INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX,INTMAX };
    int close[8] = { 0,0,0 ,0 ,0 ,0 ,0 ,0 };
    ENode* w;
    int h,i;
    /* 初始化：此处默认不存在的边用INTMAX表示 */
    for (w = lg->a[v]; w; w = w->next) {
        dist[w->adjVex] = w->Weight;
        close[w->adjVex] = v;
    }
    /*收录起点*/
    dist[v] = 0;
    close[v] = -1;

    while (1) {
        /*未被收录顶点中dist最小者*/
        h = FindMin(dist, lg->n);
        if (h == -1) /* 若这样的h不存在 */
            break;      /* 算法结束 */
        /*收录*/
        dist[h] = 0;
        
        for (w = lg->a[h]; w; w = w->next) /* 对图中的每个顶点w */
            /* 若w是h的邻接点并且未被收录 */
            if (dist[w->adjVex]  && w->Weight < INTMAX) {
                /* 若收录V使得dist[W]变小 */
                if ( w->Weight < dist[w->adjVex]) {
                    dist[w->adjVex] =  w->Weight;
                    close[w->adjVex] = h; /* 更新S到W的路径 */
                }
            }
    } /* while结束*/
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