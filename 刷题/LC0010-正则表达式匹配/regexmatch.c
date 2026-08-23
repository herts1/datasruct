/*
 * LC0010 正则表达式匹配 — C 版
 * 算法：二维 DP
 * 复杂度：O(n*m) 时间 / O(n*m) 空间（n、m <= 20）
 *
 * 状态：dp[i][j] = s 的前 i 个字符能否被 p 的前 j 个字符匹配
 *
 * 转移（设 dp[i][j] 对应 s[0..i-1] 与 p[0..j-1]）：
 *   1) p[j-1] == '*'
 *      - 匹配零个：x* 整体丢弃 -> dp[i][j-2]
 *      - 匹配一个或多个：x 能匹配 s[i-1] 时 -> dp[i-1][j]
 *        （dp[i-1][j] 表示 s 前 i-1 个字符已匹配，再用一个 x 吃掉 s[i-1]）
 *   2) 普通字符或 '.'
 *      - p[j-1] 能匹配 s[i-1]（相同或 '.'）-> dp[i-1][j-1]
 *
 * 初始化：dp[0][0] = true；dp[0][j] 只有形如 a*b*c* 的模式能匹配空串。
 */
#include <stdio.h>
#include <string.h>

/* 单字符匹配：'.' 通配任意，否则必须相同 */
static int matchChar(char pc, char sc) {
    return pc == '.' || pc == sc;
}

int isMatch(const char *s, const char *p) {
    int n = (int)strlen(s), m = (int)strlen(p);
    int dp[21][21] = {{0}};

    dp[0][0] = 1;
    /* 空串 vs 模式：只有 x* 组合能匹配空（零个 x） */
    for (int j = 2; j <= m; j++)
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                /* 零个 */
                dp[i][j] = dp[i][j - 2];
                /* 一个或多个：x 匹配 s[i-1]，再看 s 的前 i-1 个 */
                if (matchChar(p[j - 2], s[i - 1]))
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
            } else {
                dp[i][j] = matchChar(p[j - 1], s[i - 1]) && dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main(void) {
    char s[25], p[25];
    if (scanf("%s %s", s, p) != 2) return 0;
    printf("%d\n", isMatch(s, p));
    return 0;
}
