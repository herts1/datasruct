#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD = 998244353;

/**
 * BD202404 110串（百度之星 2024）— C++ 版
 * 与 BD202404.java 完全相同的计数 DP：
 *   dp[state][cnt]，state = (last2 << 1) | last1，判断最后三位是否成 110。
 * 复杂度 O(n·k·8)，空间 O(4·k)。
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string s;
    cin >> n >> k >> s;
    if (k > n) k = n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = s[i] - '0';

    // dp[4][k+1]，滚动数组
    vector<vector<long long>> dp(4, vector<long long>(k + 1, 0));

    // 放第 1 位（虚拟前位 = 0）
    for (int b = 0; b <= 1; b++) {
        int cost = (b != a[0]) ? 1 : 0;
        if (cost <= k) dp[b][cost] = 1;
    }

    // 放第 2..n 位
    for (int i = 1; i < n; i++) {
        vector<vector<long long>> ndp(4, vector<long long>(k + 1, 0));
        for (int st = 0; st < 4; st++) {
            int last2 = st >> 1, last1 = st & 1;
            for (int cnt = 0; cnt <= k; cnt++) {
                long long v = dp[st][cnt];
                if (v == 0) continue;
                for (int b = 0; b <= 1; b++) {
                    if (last2 == 1 && last1 == 1 && b == 0) continue; // 110 非法
                    int nst = (last1 << 1) | b;
                    int ncnt = cnt + (b != a[i] ? 1 : 0);
                    if (ncnt <= k) {
                        ndp[nst][ncnt] += v;
                        if (ndp[nst][ncnt] >= MOD) ndp[nst][ncnt] -= MOD;
                    }
                }
            }
        }
        dp = move(ndp);
    }

    long long ans = 0;
    for (int st = 0; st < 4; st++)
        for (int cnt = 0; cnt <= k; cnt++) {
            ans += dp[st][cnt];
            if (ans >= MOD) ans -= MOD;
        }
    cout << ans << '\n';
    return 0;
}
