#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTEX_NUM 100
#define INFINITY 99999 // 表示无穷大，用于路径计算

// 边结点结构
typedef struct ArcNode {
    int adjvex;             // 该边指向的顶点位置
    int weight;             // 权值（题目要求增加权值域）
    struct ArcNode *nextarc; // 指向下一条边
} ArcNode;

// 顶点结点结构
typedef struct VNode {
    int data;               // 顶点信息
    int inDegree;           // 入度（题目要求增加入度域）
    ArcNode *firstarc;      // 指向第一条依附于该顶点的边
} VNode, AdjList[MAX_VERTEX_NUM];

// 图结构
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;     // 图的当前顶点数和边数
} GraphAdjList;

// 菜单及主程序声明
void menu();
int CreateAdj(GraphAdjList *G);
void DispAdj(GraphAdjList G);
void DestroyAdj(GraphAdjList *G);
void PathlenAll(GraphAdjList G, int start, int end, int k); // 找长度为k的所有路径
void ShortPath(GraphAdjList G, int start, int end);         // 最短路径（BFS）
void KeyPath(GraphAdjList G);                              // 关键活动（AOE网）

#endif
