/*
 * 暴力对照程序（仅用于验证，不是正式解）
 * 枚举所有子串 [i, j]，判断是否回文，取最长。
 * 复杂度 O(n^3)，只适合小 n 验证。
 */
#include <stdio.h>
#include <string.h>

static int isPal(const char *s, int l, int r) {
    while (l < r)
        if (s[l++] != s[r--]) return 0;
    return 1;
}

int main(void) {
    char s[1005];
    if (scanf("%s", s) != 1) return 0;

    int n = (int)strlen(s);
    int start = 0, maxLen = 1;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (isPal(s, i, j) && j - i + 1 > maxLen) {
                maxLen = j - i + 1;
                start = i;
            }

    printf("%.*s\n", maxLen, s + start);
    return 0;
}
