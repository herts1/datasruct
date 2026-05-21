#include "graph.h"

int main() {
    MGraph Gm;
    ALGraph Ga;
    int choice, v, i;
    int visited[MAXV] = {0};
    int parent[MAXV] = {0};

    while (1) {
        printf("\n========== 图的存储及其遍历（***实验六参考_yyh***） ==========\n");
        printf("1.构造图的邻接矩阵Gm\n");
        printf("2.构造图的邻接表Ga\n");
        printf("3.图的深度优先遍历（DFS）【递归】\n");
        printf("4.图的广度优先遍历（BFS）\n");
        printf("5.顶点3出发的生成树【DFSTree & BFSTree】\n");
        printf("0.退出\n");
        printf("=============================================================\n");
        printf("请选择0-5：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                CreateMat(&Gm);
                DispMat(Gm);
                break;
            case 2:
                CreateAdj(&Ga);
                DispAdj(Ga);
                break;
            case 3:
                printf("请输入起始顶点（0-%d）：", Ga.n - 1);
                scanf("%d", &v);
                for (i = 0; i < Ga.n; i++) visited[i] = 0;
                printf("DFS（递归）遍历结果：");
                DFS(Ga, v, visited);
                printf("\n");
                break;
            case 4:
                printf("请输入起始顶点（0-%d）：", Ga.n - 1);
                scanf("%d", &v);
                for (i = 0; i < Ga.n; i++) visited[i] = 0;
                printf("BFS遍历结果：");
                BFS(Ga, v, visited);
                printf("\n");
                break;
            case 5:
                printf("顶点3出发的DFS生成树：");
                for (i = 0; i < Ga.n; i++) parent[i] = -1;
                DFSTree(Ga, 3, parent);
                printf("\n");

                printf("顶点3出发的BFS生成树：");
                for (i = 0; i < Ga.n; i++) parent[i] = -1;
                BFSTree(Ga, 3, parent);
                printf("\n");
                break;
            case 0:
                printf("程序结束。\n");
                return 0;
            default:
                printf("无效选择，请重新输入。\n");
        }
    }

    return 0;
}
