/*
 * 暴力对照程序（仅用于验证，不是正式解）
 * 真·按定义模拟：建一个 numRows x n 的字符网格，按 Z 字形路径
 * 逐字符填入，最后按行从左到右读出。实现思路与"按行模拟"完全独立，
 * 可以互相抓 bug。复杂度 O(numRows * n)，只适合小数据验证。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char s[1005];
    int numRows;
    if (scanf("%s %d", s, &numRows) != 2) return 0;
    int n = (int)strlen(s);

    /* 特判：只有 1 行时就是原样，网格路径不会转向（否则 row 会越界） */
    if (numRows == 1) {
        printf("%s\n", s);
        return 0;
    }

    /* 网格：numRows 行 x n 列，初始全 '\0'（当作空格占位） */
    char **grid = (char **)malloc(numRows * sizeof(char *));
    for (int i = 0; i < numRows; i++) {
        grid[i] = (char *)malloc((n + 1) * sizeof(char));
        memset(grid[i], 0, (n + 1) * sizeof(char));
    }

    int row = 0, col = 0, dir = 1;   /* dir=1 向下，-1 向上 */
    for (int i = 0; i < n; i++) {
        grid[row][col] = s[i];
        if (dir == 1) {
            if (row + 1 < numRows) row++;          /* 还能往下就走 */
            else { dir = -1; col++; row--; }       /* 到底：转向 + 换列 */
        } else {
            if (row - 1 >= 0) row--;               /* 还能往上就走 */
            else { dir = 1; col++; row++; }        /* 到顶：转向 + 换列 */
        }
    }

    /* 按行读出非空字符 */
    char *res = (char *)malloc(n + 1);
    int p = 0;
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c]) res[p++] = grid[r][c];
    res[p] = '\0';

    printf("%s\n", res);

    for (int i = 0; i < numRows; i++) free(grid[i]);
    free(grid);
    free(res);
    return 0;
}
