#include "Graph.h"
#include<stdio.h>
#include<stdlib.h> 
void menu() {
    printf("\n========== 有向图操作菜单 ==========\n");
    printf("1. 建立有向图\n");
    printf("2. 输出邻接表\n");
    printf("3. 销毁图\n");
    printf("4. 所有长度为 K 的路径\n");
    printf("5. 最短路径\n");
    printf("6. 关键活动\n");
    printf("0. 退出\n");
    printf("==================================\n");
}

int main() {
    GraphAdjList G = {0};
    int x, y, k;

    while (1) {
        menu();
        int op;
        scanf("%d", &op);

        switch (op) {
            case 1:
                CreateAdj(&G);
                break;

            case 2:
                DispAdj(G);
                break;

            case 3:
                DestroyAdj(&G);
                break;

            case 4:
                printf("输入起点 终点 长度: ");
                scanf("%d %d %d", &x, &y, &k);
                PathlenAll(G, x, y, k);
                break;

            case 5:
                printf("输入起点 终点: ");
                scanf("%d %d", &x, &y);
                ShortPath(G, x, y);
                break;

            case 6:
                KeyPath(G);
                break;

            case 0:
                DestroyAdj(&G);
                return 0;

            default:
                printf("无效选择！\n");
        }
    }
}
