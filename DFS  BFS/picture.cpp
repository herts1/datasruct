#include <stdio.h>
#include <stdlib.h>
#define MAXV 100

int G[MAXV][MAXV] = {0};
int visited[MAXV] = {0};
int n, m;  // 顶点数，边数

// 初始化图
void initGraph() {
    printf("输入顶点数和边数: ");
    scanf("%d %d", &n, &m);
    
    printf("输入%d条边(格式: u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 1;  // 无向图
    }
}

// DFS递归
void DFS(int v) {
    visited[v] = 1;
    printf("%d ", v);
    
    for (int i = 0; i < n; i++) {
        if (G[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

// BFS
void BFS(int start) {
    int queue[MAXV];
    int rear = 0, front = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
    
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        
        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    initGraph();
    
    printf("\nDFS遍历结果: ");
    for (int i = 0; i < n; i++) visited[i] = 0;  // 重置访问标记
    DFS(0);
    
    printf("\nBFS遍历结果: ");
    for (int i = 0; i < n; i++) visited[i] = 0;  // 重置访问标记
    BFS(0);
    
    return 0;
}
