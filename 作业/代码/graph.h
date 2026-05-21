#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAXV 100 //最大顶点数 


// 邻接矩阵结构
typedef struct {
	int edgs[MAXV][MAXV]; //边权
	int n,e;   //顶点数，边数
}MGraph;


// 邻接表节点结构
typedef struct ArcNode{
	int adjvex;  //邻接点下标
	int weight;  //边权
	struct ArcNode *nextarc; 
}ArcNode;


// 顶点结构
typedef struct VNode{
	int data;
	ArcNode *firstarc;
}VNode,AdjList[MAXV];


// 邻接表结构
typedef struct {
	AdjList vertices;
	int n,e;
}ALGraph;

//函数声明
void CreateMat(MGraph *G); // 建立邻接矩阵
void CreateAdj(ALGraph *G); // 建立邻接表
void DispMat(MGraph G);  // 输出邻接矩阵
void DispAdj(ALGraph G);  // 输出邻接表


//DFS(递归)
void DFS(ALGraph G,int v,int visited[]);
//DFS(非递归)
void DFS1(ALGraph G,int v,int visited[]);
//BFS
void BFS(ALGraph G,int v,int visited[]);

//生成树（记录父节点） 
void DFSTree(ALGraph G,int v,int parent[]);
void BFSTree(ALGraph G,int v,int parent[]);

//销毁
void DestroyMat(MGraph *G);
void DestroyAdj(ALGraph *G); 


#endif
