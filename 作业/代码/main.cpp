#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// -------------------------- 迷宫数据定义 --------------------------
// 1表示墙壁，0表示通路，入口(1,1)，出口(6,6)
int maze[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1},
    {1,0,0,1,1,0,1,1},
    {1,1,0,0,1,0,1,1},
    {1,1,0,0,0,1,1,1},
    {1,0,0,1,0,1,1,1},
    {1,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

// 方向数组：上、下、左、右
int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

// -------------------------- 队列实现（用于BFS求最短路径） --------------------------
#define MAX_QUEUE_SIZE 100
typedef struct {
    Pos data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int dist[MAX_QUEUE_SIZE];  // 记录到每个位置的距离
    Pos prev[MAX_QUEUE_SIZE];  // 记录每个位置的前驱，用于回溯路径
} Queue;

// 队列初始化
void QueueInit(Queue *q) {
    q->front = q->rear = 0;
}

// 判断队列是否为空
bool QueueIsEmpty(Queue *q) {
    return q->front == q->rear;
}

// 入队
bool QueueEnqueue(Queue *q, Pos pos, int distance, Pos pre) {
    if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front) {
        printf("队列已满，无法入队！\n");
        return false;
    }
    q->data[q->rear] = pos;
    q->dist[q->rear] = distance;
    q->prev[q->rear] = pre;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    return true;
}

// 出队
bool QueueDequeue(Queue *q, Pos *pos, int *dist, Pos *pre) {
    if (QueueIsEmpty(q)) {
        printf("队列为空，无法出队！\n");
        return false;
    }
    *pos = q->data[q->front];
    *dist = q->dist[q->front];
    *pre = q->prev[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return true;
}

// -------------------------- DFS输出所有路径（用栈回溯） --------------------------
int path_count = 0;  // 路径计数器

void DFS(Pos cur, Stack *s, bool visited[8][8]) {
    // 到达出口，输出路径
    if (cur.x == 6 && cur.y == 6) {
        path_count++;
        printf("路径 %d: ", path_count);
        StackPrintPath(s);
        return;
    }

    // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        int nx = cur.x + dirs[i][0];
        int ny = cur.y + dirs[i][1];
        // 判断是否越界、是否是通路、是否已访问
        if (nx >= 0 && nx < 8 && ny >=0 && ny <8 && maze[nx][ny] == 0 && !visited[nx][ny]) {
            visited[nx][ny] = true;
            Pos next = {nx, ny};
            StackPush(s, next);
            DFS(next, s, visited);
            // 回溯
            StackPop(s, &next);
            visited[nx][ny] = false;
        }
    }
}

// -------------------------- BFS求最短路径（用队列） --------------------------
void BFS(Pos start, Pos end) {
    Queue q;
    QueueInit(&q);
    bool visited[8][8] = {false};
    // 起点入队
    QueueEnqueue(&q, start, 0, (Pos){-1,-1});
    visited[start.x][start.y] = true;

    int min_dist = -1;
    Pos end_pre = {-1, -1};
    
    // 创建前驱数组
    Pos predecessor[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            predecessor[i][j] = (Pos){-1, -1};
        }
    }

    while (!QueueIsEmpty(&q)) {
        Pos cur;
        int dist;
        Pos pre;
        QueueDequeue(&q, &cur, &dist, &pre);

        // 记录前驱
        if (pre.x != -1) {
            predecessor[cur.x][cur.y] = pre;
        }

        // 到达出口
        if (cur.x == end.x && cur.y == end.y) {
            min_dist = dist;
            break;
        }

        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dirs[i][0];
            int ny = cur.y + dirs[i][1];
            if (nx >=0 && nx <8 && ny >=0 && ny <8 && maze[nx][ny] ==0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                Pos next = {nx, ny};
                QueueEnqueue(&q, next, dist+1, cur);
            }
        }
    }

    if (min_dist == -1) {
        printf("无路径可达出口！\n");
        return;
    }

    // 回溯输出最短路径
    printf("最短路径长度：%d\n", min_dist);
    printf("最短路径：");
    Stack path_stack;
    StackInit(&path_stack);
    Pos cur = end;
    
    // 从终点回溯到起点
    while (cur.x != -1 && cur.y != -1) {
        StackPush(&path_stack, cur);
        cur = predecessor[cur.x][cur.y];
    }
    
    // 创建反转栈
    Stack reverse_stack;
    StackInit(&reverse_stack);
    
    // 反转路径顺序
    while (!StackIsEmpty(&path_stack)) {
        Pos p;
        StackPop(&path_stack, &p);
        StackPush(&reverse_stack, p);
    }
    
    // 输出路径
    while (!StackIsEmpty(&reverse_stack)) {
        Pos p;
        StackPop(&reverse_stack, &p);
        printf("(%d, %d)", p.x, p.y);
        if (!StackIsEmpty(&reverse_stack)) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// -------------------------- 主函数 --------------------------
int main() {
    // 1. 输出所有路径（DFS+栈）
    printf("=================== 迷宫路径搜索 ===================\n");
    printf("迷宫起点: (%d, %d)\n", 1, 1);
    printf("迷宫终点: (%d, %d)\n\n", 6, 6);
    
    printf("所有通往出口的路径：\n");
    Stack s;
    StackInit(&s);
    bool visited[8][8] = {false};
    Pos start = {1, 1};
    visited[start.x][start.y] = true;
    StackPush(&s, start);
    
    path_count = 0;  // 重置路径计数器
    DFS(start, &s, visited);
    
    if (path_count == 0) {
        printf("未找到通往出口的路径！\n");
    } else {
        printf("\n共找到 %d 条路径\n", path_count);
    }
    
    printf("\n--------------------------\n\n");

    // 2. BFS求最短路径（队列）
    printf("最短路径搜索结果：\n");
    Pos end = {6, 6};
    BFS(start, end);

    return 0;
}
