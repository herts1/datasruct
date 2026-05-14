#include<stdio.h>
#include<stdlib.h>
/* =========================
   常量定义
   ========================= */
#define MAXV 1000        // 最大顶点数
#define INF 32767        // 表示无穷大（∞），用于无连接边

/* =========================
   顶点附加信息类型
   ========================= */
typedef int InfoType;    // 顶点附加信息类型（如权值、编号等）

/* =========================
   顶点类型定义
   ========================= */
typedef struct {
    int no;              // 顶点编号
    InfoType info;       // 顶点附加信息
} VertexType;

/* =========================
   邻接矩阵存储结构
   ========================= */
typedef struct {
    int edges[MAXV][MAXV]; // 邻接矩阵，edges[i][j] 表示边权
    int n;                 // 顶点数
    int e;                 // 边数
    VertexType vexs[MAXV]; // 顶点数组
} MatGraph;

/* =========================
   边结点（邻接表用）
   ========================= */
typedef struct ANode {
    int adjvex;          // 该边指向的顶点编号
    struct ANode *nextarc; // 指向下一条边的指针
    int weight;          // 边权
} ArcNode;

/* =========================
   邻接表中顶点结点
   ========================= */
typedef struct Vnode {
    InfoType data;       // 顶点信息
    ArcNode *firstarc;   // 指向第一条依附该顶点的边
} VNode;

/* =========================
   邻接表存储结构
   ========================= */
typedef struct {
    VNode adjlist[MAXV]; // 邻接表头结点数组
    int n;               // 顶点数
    int e;               // 边数
} AdjGraph;



void CreateAdj(AdjGraph *&G,int A[MAXV][MAXV],int n,int e){
	int i,j;
	ArcNode *p;
	G=(AdjGraph*)malloc(sizeof(AdjGraph));
	for(i=0;i<n;i++){
		G->adjlist[i].firstarc=NULL;
		}
	for(int i=0;i<n;i++){
		for(int j=n-1;j>=0;j--){
			if(A[i][j]!=0&&A[i][j]!=INF){
				p=(ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex=j;
				p->weight=A[i][j];
				p->nextarc=G->adjlist[i].firstarc;
				G->adjlist[i].firstarc=p;
			}
		}
	} 
	 G->n=n;
	 G->e=e;
} 


































