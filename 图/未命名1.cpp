#include <stdio.h>
#include <stdlib.h>

/* =========================
   常量定义
   ========================= */
#define MAXV 1000        // 图中最多允许的顶点数
#define INF 32767        // 表示“无穷大”，用于代表两点之间没有直接边

/* =========================
   顶点附加信息类型
   ========================= */
typedef int InfoType;    // 顶点附加信息的数据类型（可改为结构体）

/* =========================
   顶点类型定义
   ========================= */
typedef struct {
    int no;              // 顶点编号（0 ~ n-1）
    InfoType info;       // 顶点附加信息（如权值、编号等）
} VertexType;

/* =========================
   邻接矩阵存储结构
   ========================= */
typedef struct {
    int edges[MAXV][MAXV]; // 邻接矩阵，edges[i][j] 表示 i→j 的边权
    int n;                 // 当前图的顶点数
    int e;                 // 当前图的边数
    VertexType vexs[MAXV]; // 顶点信息数组
} MatGraph;

/* =========================
   边结点（邻接表使用）
   ========================= */
typedef struct ANode {
    int adjvex;           // 该边所指向的邻接点编号
    struct ANode *nextarc; // 指向下一条邻接边的指针
    int weight;            // 该边的权值
} ArcNode;

/* =========================
   邻接表中的顶点结点
   ========================= */
typedef struct Vnode {
    InfoType data;        // 顶点数据（可扩展）
    ArcNode *firstarc;    // 指向第一条依附于该顶点的边
} VNode;

/* =========================
   邻接表存储结构
   ========================= */
typedef struct {
    VNode adjlist[MAXV];  // 所有顶点的邻接表头结点
    int n;                // 顶点数
    int e;                // 边数
} AdjGraph;


/*
 * 函数名：CreateAdj
 * 功能  ：由邻接矩阵 A 创建邻接表 G
 * 参数  ：
 *   G - 邻接表（二级指针，用于返回创建结果）
 *   A - 邻接矩阵
 *   n - 顶点个数
 *   e - 边的个数
 */
void CreateAdj(AdjGraph *&G, int A[MAXV][MAXV], int n, int e)
{
    int i, j;
    ArcNode *p;

    // 为邻接表分配存储空间
    G = (AdjGraph *)malloc(sizeof(AdjGraph));

    // 初始化每个顶点的邻接表为空
    for (i = 0; i < n; i++) {
        G->adjlist[i].firstarc = NULL;
    }

    // 遍历邻接矩阵
    for (i = 0; i < n; i++) {
        // 从后向前遍历，使生成的邻接表顺序更直观
        for (j = n - 1; j >= 0; j--) {
            // 若存在边（权值不为 0 且不是无穷大）
            if (A[i][j] != 0 && A[i][j] != INF) {
                // 创建新的边结点
                p = (ArcNode *)malloc(sizeof(ArcNode));

                p->adjvex = j;           // 邻接点编号
                p->weight = A[i][j];     // 边权
                p->nextarc = G->adjlist[i].firstarc; // 头插法
                G->adjlist[i].firstarc = p;
            }
        }
    }

    // 设置顶点数和边数
    G->n = n;
    G->e = e;
}


/*
 * 函数名：DispAdj
 * 功能  ：输出邻接表结构
 * 参数  ：G - 邻接表
 */
void DispAdj(AdjGraph *G)
{
    int i;
    ArcNode *p;

    // 遍历所有顶点
    for (i = 0; i < G->n; i++) {
        printf("%3d:", i);      // 输出顶点编号
        p = G->adjlist[i].firstarc;

        // 遍历该顶点的所有邻接边
        while (p != NULL) {
            printf("%3d[%d]", p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("\n");
    }
}


/*
 * 函数名：DestroyAdj
 * 功能  ：释放邻接表占用的全部内存
 * 参数  ：G - 邻接表
 */
void DestroyAdj(AdjGraph *&G)
{
    int i;
    ArcNode *pre, *p;

    // 遍历所有顶点
    for (i = 0; i < G->n; i++) {
        pre = G->adjlist[i].firstarc;

        // 若当前顶点存在邻接边
        if (pre != NULL) {
            p = pre->nextarc;

            // 逐个释放边结点
            while (p != NULL) {
                free(pre);
                pre = p;
                p = p->nextarc;
            }
            free(pre); // 释放最后一个结点
        }
    }

    // 释放邻接表本身
    free(G);
}
























