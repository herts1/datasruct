/*
 * LC0005 最长回文子串 — C++ 版
 * 算法：中心扩展法（与 C 版完全相同的思路）
 * 复杂度：O(n^2) 时间 / O(1) 空间
 */
#include <iostream>
#include <string>
using namespace std;

/* 以 (l, r) 为中心向外扩展，返回最大回文长度 */
static int expand(const string &s, int l, int r) {
    int n = (int)s.size();
    while (l >= 0 && r < n && s[l] == s[r]) {
        l--;
        r++;
    }
    return r - l - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    int start = 0, maxLen = 1;   /* 单字符兜底 */

    for (int i = 0; i < n; i++) {
        int len1 = expand(s, i, i);      /* 奇数中心：1 个字符 */
        int len2 = expand(s, i, i + 1);  /* 偶数中心：2 个字符之间 */
        int len = max(len1, len2);
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;   /* 反推左端点（奇偶通用） */
        }
    }

    cout << s.substr(start, maxLen) << '\n';
    return 0;
}
