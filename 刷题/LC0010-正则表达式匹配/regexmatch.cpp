/*
 * LC0010 正则表达式匹配 — C++ 版
 * 与 C 版完全相同的 DP 思路。
 * 复杂度：O(n*m) 时间 / O(n*m) 空间
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

static bool matchChar(char pc, char sc) {
    return pc == '.' || pc == sc;
}

bool isMatch(string s, string p) {
    int n = (int)s.size(), m = (int)p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    dp[0][0] = true;
    /* 空串：只有 x* 能匹配空（零个） */
    for (int j = 2; j <= m; j++)
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];                        /* 零个 */
                if (matchChar(p[j - 2], s[i - 1]))              /* 一个或多个 */
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
            } else {
                dp[i][j] = matchChar(p[j - 1], s[i - 1]) && dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, p;
    cin >> s >> p;
    cout << (isMatch(s, p) ? 1 : 0) << '\n';
    return 0;
}
