#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

/**
 * BD202402 跑步（百度之星 2024）— C++ 版
 * 与 BD202402.java 完全相同的算法：
 *   T = lcm(1..n) mod MOD；答案 = T * ((n+1)*H - 2n) mod MOD，H = Σ inv(i)
 * 复杂度 O(n) 时间 / O(n) 内存
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // ---------- 1. 欧拉筛：找 [2, n] 的所有素数 ----------
    vector<char> isComposite(n + 1, 0);   // 标记合数（char 当 bool，省内存）
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (!isComposite[i]) primes.push_back(i);
        for (int j = 0; j < (int)primes.size() && (long long)i * primes[j] <= n; j++) {
            isComposite[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;   // 关键：保证每个合数只被最小质因子筛一次
        }
    }

    // ---------- 2. T = lcm(1..n) mod MOD = Π p^{e_p} ----------
    long long T = 1;
    for (int p : primes) {
        long long pe = 1;
        while (pe * p <= n) pe *= p;         // pe = p^{e_p}（完整值，仍 <= n）
        T = T * (pe % MOD) % MOD;
    }

    // ---------- 3. 线性求逆元 + 累加 H = Σ inv(i) ----------
    vector<int> inv(n + 1);
    inv[1] = 1;
    long long H = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (int)(MOD - (long long)(MOD / i) * inv[MOD % i] % MOD);
        H += inv[i];
        if (H >= MOD) H -= MOD;
    }

    // ---------- 4. 答案 = T * ((n+1)*H - 2n) mod MOD ----------
    long long sum = ((long long)(n + 1) % MOD * H % MOD
                   - (long long)2 * n % MOD + MOD) % MOD;
    cout << T * sum % MOD << '\n';
    return 0;
}
