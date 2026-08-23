/*
 * LC0005 最长回文子串 — C 版
 * 算法：中心扩展法（枚举所有"回文中心"，向两边扩展）
 * 复杂度：O(n^2) 时间 / O(1) 空间
 *
 * 核心思想：回文串关于中心对称。
 * 中心分两类：
 *   1) 奇数长度回文：中心是 1 个字符，如 "aba" 的中心 'b'
 *   2) 偶数长度回文：中心在 2 个字符之间，如 "bb" 的中心在 b|b 之间
 * 所以共有 2n-1 个中心（n 个字符中心 + n-1 个空隙中心），
 * 对每个中心向两边扩展，取能扩出的最长回文。
 */
#include <stdio.h>
#include <string.h>

/* 以 (l, r) 为中心向外扩展，返回能形成的最大回文长度。
 * 奇数中心：expand(s, n, i, i)；偶数中心：expand(s, n, i, i+1) */
static int expand(const char *s, int n, int l, int r) {
    while (l >= 0 && r < n && s[l] == s[r]) {
        l--;
        r++;
    }
    return r - l - 1;   /* 退出时 s[l] != s[r] 或越界，长度 = r-l-1 */
}

int main(void) {
    char s[1005];
    if (scanf("%s", s) != 1) return 0;

    int n = (int)strlen(s);
    int start = 0, maxLen = 1;          /* 单字符必是回文，兜底答案 */

    for (int i = 0; i < n; i++) {
        int len1 = expand(s, n, i, i);      /* 奇数中心 */
        int len2 = expand(s, n, i, i + 1);  /* 偶数中心 */
        int len = len1 > len2 ? len1 : len2;
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;      /* 由中心和长度反推左端点（奇偶通用） */
        }
    }

    printf("%.*s\n", maxLen, s + start);    /* 打印 [start, start+maxLen) 子串 */
    return 0;
}
