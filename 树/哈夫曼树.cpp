
/*哈夫曼树及哈夫曼编码算法说明?
哈夫曼树是一种最优二叉树，用于构造前缀编码。算法首先根据给定的 n 个权值构造 n 棵只有根结点的二叉树森林，每次从中选取两棵权值最小的二叉树合并为一棵新二叉树，新结点权值为二者之和，重复直至只剩一棵二叉树，即哈夫曼树。
从每个叶子结点出发，沿双亲回溯至根，走向左孩子记 '0'，右孩子记 '1'，逆向得到该字符的哈夫曼编码。
时间复杂度：O(n2)（简单选择），可用小顶堆优化至 O(n log n)
空间复杂度：O(n)

*/ 






#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100

typedef struct {
    int weight;
    int parent, lchild, rchild;
} HTNode;

typedef char* HuffmanCode;

/* 选择两个最小权值的结点 */
void select(HTNode *HT, int n, int *s1, int *s2) {
    int min1 = 1e9, min2 = 1e9;
    *s1 = *s2 = 0;
    for (int i = 1; i <= n; i++) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < min1) {
                min2 = min1; *s2 = *s1;
                min1 = HT[i].weight; *s1 = i;
            } else if (HT[i].weight < min2) {
                min2 = HT[i].weight; *s2 = i;
            }
        }
    }
    if (*s1 == *s2) *s2 = 0;
}

/* 构建哈夫曼树 */
void createHuffmanTree(HTNode *HT, int n, int w[]) {
    int m = 2 * n - 1;
    for (int i = 1; i <= n; i++) {
        HT[i].weight = w[i - 1];
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }
    for (int i = n + 1; i <= m; i++) {
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }

    for (int i = n + 1; i <= m; i++) {
        int s1, s2;
        select(HT, i - 1, &s1, &s2);
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[s1].parent = HT[s2].parent = i;
    }
}

/* 生成哈夫曼编码 */
void createHuffmanCode(HTNode *HT, HuffmanCode HC[], int n) {
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';

    for (int i = 1; i <= n; i++) {
        int start = n - 1;
        int c = i, p = HT[c].parent;
        while (p != 0) {
            if (HT[p].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            c = p;
            p = HT[c].parent;
        }
        HC[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}

int main() {
    int n;
    int w[MAXN];
    HTNode HT[MAXN * 2];
    HuffmanCode HC[MAXN];

    printf("请输入字符个数：");
    scanf("%d", &n);
    printf("请输入 %d 个权值：\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &w[i]);

    createHuffmanTree(HT, n, w);
    createHuffmanCode(HT, HC, n);

    printf("\n哈夫曼编码如下：\n");
    for (int i = 1; i <= n; i++)
        printf("字符%c(权%d): %s\n", 'a' + i - 1, HT[i].weight, HC[i]);

    return 0;
}
