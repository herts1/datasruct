/*
 * 暴力对照程序（仅用于验证，不是正式解）
 * 独立思路：递归回溯 + 记忆化。与 DP 表格的代码结构完全不同，
 * 可以互相抓 bug。
 *
 * can(i, j)：s[i..n-1] 能否被 p[j..m-1] 匹配
 *   - j 到末尾：必须 i 也到末尾
 *   - 下一个字符是 '*'：尝试"零个"（跳过 x*）或"一个"（x 吃掉 s[i] 后继续）
 *   - 普通字符/'.'：匹配则双双前进一步
 */
#include <stdio.h>
#include <string.h>

static char s[25], p[25];
static int n, m;
static int memo[21][21];

static int can(int i, int j) {
    if (memo[i][j] != -1) return memo[i][j];

    int res;
    if (j == m) {
        res = (i == n);                     /* 模式用完了，串必须也用完 */
    } else if (j + 1 < m && p[j + 1] == '*') {
        if (can(i, j + 2)) res = 1;         /* 零个 x */
        else if (i < n && (p[j] == '.' || p[j] == s[i]) && can(i + 1, j)) res = 1;  /* 一个 x */
        else res = 0;
    } else if (i < n && (p[j] == '.' || p[j] == s[i])) {
        res = can(i + 1, j + 1);            /* 普通匹配 */
    } else {
        res = 0;
    }

    memo[i][j] = res;
    return res;
}

int main(void) {
    if (scanf("%s %s", s, p) != 2) return 0;
    n = (int)strlen(s);
    m = (int)strlen(p);
    memset(memo, -1, sizeof(memo));
    printf("%d\n", can(0, 0));
    return 0;
}
