/*
 * LC0006 Z字形变换 — C 版
 * 算法：按行模拟（方向变量 dir）
 * 复杂度：O(n) 时间 / O(n) 空间
 *
 * 思路：Z 字形的写入路径 = 从第 0 行向下走到最后一行，
 *       再向上走回第 0 行，如此往复。用一个方向变量 dir 记录
 *       当前是向下(+1)还是向上(-1)，碰到边界就转向。
 *       每个字符直接追加到"它所在行"的缓冲里，最后把所有行拼起来。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert(const char *s, int numRows) {
    int n = (int)strlen(s);

    /* 特判：只有 1 行，或行数不少于长度（每行最多 1 个字符），结果就是原串 */
    if (numRows == 1 || numRows >= n) {
        char *res = (char *)malloc(n + 1);
        strcpy(res, s);
        return res;
    }

    /* 每行一个字符缓冲（n 个字符最多，给满 n+1） */
    char **rows = (char **)malloc(numRows * sizeof(char *));
    int *len = (int *)calloc(numRows, sizeof(int));
    for (int i = 0; i < numRows; i++) rows[i] = (char *)malloc((n + 1) * sizeof(char));

    int row = 0, dir = 1;          /* dir = 1 向下，-1 向上 */
    for (int i = 0; i < n; i++) {
        rows[row][len[row]++] = s[i];
        row += dir;
        if (row == numRows - 1 || row == 0) dir = -dir;   /* 撞到边界转向 */
    }

    /* 按行顺序拼接结果 */
    char *res = (char *)malloc(n + 1);
    int p = 0;
    for (int i = 0; i < numRows; i++) {
        memcpy(res + p, rows[i], len[i]);
        p += len[i];
    }
    res[p] = '\0';

    for (int i = 0; i < numRows; i++) free(rows[i]);
    free(rows);
    free(len);
    return res;
}

int main(void) {
    char s[1005];
    int numRows;
    if (scanf("%s %d", s, &numRows) != 2) return 0;

    char *res = convert(s, numRows);
    printf("%s\n", res);
    free(res);
    return 0;
}
