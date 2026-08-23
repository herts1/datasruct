/*
 * LC0008 字符串转换整数 myAtoi — C 版
 * 复杂度：O(n) 时间 / O(1) 空间
 *
 * 四阶段流程：跳过前导空格 -> 读符号 -> 读数字 -> 溢出截断。
 *
 * 核心考点（防溢出）：
 *   朴素写法 ans = ans*10 + d 在 ans 接近 INT_MAX 时先溢出（UB）。
 *   正确做法是"乘法前判断"：
 *     ans*10 + d > INT_MAX  <=>  ans > (INT_MAX - d) / 10
 *   成立时直接返回边界值，全程只用 32 位 int，不会溢出。
 *   负数边界 INT_MIN 的绝对值比 INT_MAX 大 1，用"正数累加 + 符号"统一处理。
 */
#include <stdio.h>
#include <limits.h>
#include <string.h>

int myAtoi(const char *s) {
    int n = (int)strlen(s);
    int i = 0;

    /* 1) 跳过前导空格 */
    while (i < n && s[i] == ' ') i++;

    /* 2) 符号（可有可无） */
    int sign = 1;
    if (i < n && (s[i] == '-' || s[i] == '+')) {
        if (s[i] == '-') sign = -1;
        i++;
    }

    /* 3) 读数字，用正数累加，边读边防溢出 */
    int ans = 0;
    while (i < n && s[i] >= '0' && s[i] <= '9') {
        int d = s[i] - '0';
        if (ans > (INT_MAX - d) / 10) {        /* 再乘 10 必超界 */
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        ans = ans * 10 + d;
        i++;
    }

    /* 4) 未溢出，套符号返回 */
    return sign * ans;
}

int main(void) {
    /* 输入可能含空格（前导/行内），用 fgets 读整行 */
    char s[205];
    if (fgets(s, sizeof(s), stdin) == NULL) return 0;
    s[strcspn(s, "\r\n")] = '\0';      /* 去掉行尾换行符 */

    printf("%d\n", myAtoi(s));
    return 0;
}
