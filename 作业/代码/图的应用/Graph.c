 #include "Graph.h"
 #include<stdio.h>
 #include<stdlib.h>
 int visited[MAX_VERTEX_NUM];
 int path_stack[MAX_VERTEX_NUM];
 int path_count = 0;
 
 /* ================= 创建图 ================= */
 int CreateAdj(GraphAdjList *G) {
     int i, j, k, w;
     ArcNode *p;
 
     printf("请输入顶点数 n 和边数 e: ");
     scanf("%d %d", &G->vexnum, &G->arcnum);
 
     printf("请输入 %d 个顶点的值:\n", G->vexnum);
     for (i = 0; i < G->vexnum; i++) {
         scanf("%d", &G->vertices[i].data);
         G->vertices[i].inDegree = 0;
         G->vertices[i].firstarc = NULL;
     }
 
     printf("请输入 %d 条弧（起点 终点 权值）:\n", G->arcnum);
     for (k = 0; k < G->arcnum; k++) {
         scanf("%d %d %d", &i, &j, &w);
         p = (ArcNode *)malloc(sizeof(ArcNode));
         p->adjvex = j;
         p->weight = w;
         p->nextarc = G->vertices[i].firstarc;
         G->vertices[i].firstarc = p;
         G->vertices[j].inDegree++;
     }
     return 1;
 }
 
 /* ================= 输出邻接表 ================= */
 void DispAdj(GraphAdjList G) {
     int i;
     ArcNode *p;
     printf("\n--- 邻接表 ---\n");
     for (i = 0; i < G.vexnum; i++) {
         printf("[%d | 入度:%d]: ", G.vertices[i].data, G.vertices[i].inDegree);
         p = G.vertices[i].firstarc;
         while (p) {
             printf("→ [%d|w=%d] ", G.vertices[p->adjvex].data, p->weight);
             p = p->nextarc;
         }
         printf("\n");
     }
 }
 
 /* ================= 销毁图 ================= */
 void DestroyAdj(GraphAdjList *G) {
     int i;
     ArcNode *p, *q;
     for (i = 0; i < G->vexnum; i++) {
         p = G->vertices[i].firstarc;
         while (p) {
             q = p;
             p = p->nextarc;
             free(q);
         }
     }
     G->vexnum = 0;
     printf("图已销毁。\n");
 }
 
 /* ================= DFS 找长度为 K 的路径 ================= */
 void DFS_Path(GraphAdjList G, int v, int end, int k, int depth) {
     visited[v] = 1;
     path_stack[depth] = v;
 
     if (depth == k && v == end) {
         printf("路径 %d: ", ++path_count);
         for (int i = 0; i <= k; i++) {
             printf("%d", G.vertices[path_stack[i]].data);
             if (i < k) printf(" → ");
         }
         printf("\n");
     }
 
     ArcNode *p = G.vertices[v].firstarc;
     while (p) {
         if (!visited[p->adjvex])
             DFS_Path(G, p->adjvex, end, k, depth + 1);
         p = p->nextarc;
     }
     visited[v] = 0;
 }
 
 /* ================= 所有长度为 K 的简单路径 ================= */
 void PathlenAll(GraphAdjList G, int x, int y, int k) {
     int i, start = -1, end = -1;
     for (i = 0; i < G.vexnum; i++) {
         if (G.vertices[i].data == x) start = i;
         if (G.vertices[i].data == y) end = i;
     }
 
     if (start == -1 || end == -1) {
         printf("顶点不存在！\n");
         return;
     }
 
     path_count = 0;
     DFS_Path(G, start, end, k, 0);
     if (!path_count) printf("未找到路径。\n");
 }
 
 /* ================= BFS 最短路径 ================= */
 void ShortPath(GraphAdjList G, int x, int y) {
     int i, start = -1, end = -1;
     for (i = 0; i < G.vexnum; i++) {
         if (G.vertices[i].data == x) start = i;
         if (G.vertices[i].data == y) end = i;
     }
 
     int dist[MAX_VERTEX_NUM], path[MAX_VERTEX_NUM], vis[MAX_VERTEX_NUM] = {0};
     int q[MAX_VERTEX_NUM], front = 0, rear = 0;
 
     for (i = 0; i < G.vexnum; i++) dist[i] = INFINITY;
 
     q[rear++] = start;
     dist[start] = 0;
     path[start] = -1;
 
     while (front < rear) {
         int u = q[front++];
         if (u == end) break;
 
         ArcNode *p = G.vertices[u].firstarc;
         while (p) {
             int v = p->adjvex;
             if (!vis[v]) {
                 vis[v] = 1;
                 dist[v] = dist[u] + 1;
                 path[v] = u;
                 q[rear++] = v;
             }
             p = p->nextarc;
         }
     }
 
     if (dist[end] == INFINITY)
         printf("不可达。\n");
     else
         printf("最短路径长度：%d\n", dist[end]);
 }
 
 /* ================= 关键活动（AOE） ================= */
 void KeyPath(GraphAdjList G) {
     int i, j, k, topo[MAX_VERTEX_NUM];
     int ve[MAX_VERTEX_NUM] = {0}, vl[MAX_VERTEX_NUM];
     int stack[MAX_VERTEX_NUM], top = -1;
 
     for (i = 0; i < G.vexnum; i++)
         if (G.vertices[i].inDegree == 0)
             stack[++top] = i;
 
     int cnt = 0;
     while (top != -1) {
         j = stack[top--];
         topo[cnt++] = j;
 
         ArcNode *p = G.vertices[j].firstarc;
         while (p) {
             k = p->adjvex;
             if (--G.vertices[k].inDegree == 0)
                 stack[++top] = k;
             if (ve[j] + p->weight > ve[k])
                 ve[k] = ve[j] + p->weight;
             p = p->nextarc;
         }
     }
 
     for (i = 0; i < G.vexnum; i++)
         vl[i] = ve[G.vexnum - 1];
 
     for (i = cnt - 1; i >= 0; i--) {
         j = topo[i];
         ArcNode *p = G.vertices[j].firstarc;
         while (p) {
             k = p->adjvex;
             if (vl[k] - p->weight < vl[j])
                 vl[j] = vl[k] - p->weight;
             p = p->nextarc;
         }
     }
 
     printf("\n--- 关键活动 ---\n");
     for (i = 0; i < G.vexnum; i++) {
         ArcNode *p = G.vertices[i].firstarc;
         while (p) {
             j = p->adjvex;
             if (ve[i] == vl[j] - p->weight)
                 printf("<%d, %d> 权值=%d\n",
                        G.vertices[i].data,
                        G.vertices[j].data,
                        p->weight);
             p = p->nextarc;
         }
     }
 }
