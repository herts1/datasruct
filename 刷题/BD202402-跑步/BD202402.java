import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * BD202402 跑步（百度之星 2024）
 *
 * 思路：
 * 1. 总时间 T = lcm(1, 2, ..., n)（所有人同时回到起点）
 * 2. 同学 i 与同学 j (i < j) 的打招呼次数 = T/i - T/j
 *    （推导：两人位置相同当且仅当路程差为整圈，
 *      相遇周期 t0 = i*j/(j-i)，次数 = T/t0 = T(j-i)/(ij) = T/i - T/j）
 * 3. 总次数 = Σ_{i<j} (T/i - T/j)
 *           = Σ_i (n-i)(T/i) - Σ_j (j-1)(T/j)
 *           = Σ_i (n+1-2i) * (T/i)
 *           = (n+1) * Σ_{i=1..n} (T/i) - 2n * T
 * 4. 模 p 下：因为 i | T（lcm 的定义！），所以 T/i 是整数，
 *    且 T * inv(i) ≡ (T/i) * i * inv(i) ≡ T/i (mod p)，
 *    故 Σ(T/i) ≡ T * Σ inv(i) (mod p)
 * 5. 实现：欧拉筛求素数 → 每个素数算最大幂 e_p，T ≡ Π p^{e_p} (mod p)
 *          线性递推求 1..n 的逆元 → 累加 H = Σ inv(i)
 * 6. 答案 = T * ((n+1)*H - 2n) mod p
 *
 * 时间复杂度 O(n)，空间复杂度 O(n)
 */
public class BD202402 {
    static final int MOD = 998244353;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());
        System.out.println(solve(n));
    }

    static long solve(int n) {
        // ---------- 1. 欧拉筛：找出 [2, n] 的所有素数 ----------
        boolean[] isComposite = new boolean[n + 1]; // 标记合数
        int[] primes = new int[n + 1];              // 素数表
        int pc = 0;                                 // 素数个数
        for (int i = 2; i <= n; i++) {
            if (!isComposite[i]) primes[pc++] = i;  // i 是素数
            for (int j = 0; j < pc && (long) i * primes[j] <= n; j++) {
                isComposite[i * primes[j]] = true;  // 用最小质因子筛合数
                if (i % primes[j] == 0) break;      // 保证每个合数只被筛一次
            }
        }

        // ---------- 2. T = lcm(1..n) mod MOD = Π p^{e_p} ----------
        // e_p = floor(log_p n)，即 p 的指数最大能到多少（p^{e_p} <= n < p^{e_p+1}）
        long T = 1;
        for (int k = 0; k < pc; k++) {
            long p = primes[k];
            long pe = 1;
            while (pe * p <= n) pe *= p;   // pe = p^{e_p}（完整值，仍 <= n）
            T = T * (pe % MOD) % MOD;
        }

        // ---------- 3. 线性求 1..n 的逆元，并累加 H = Σ inv(i) ----------
        // 递推公式：inv[i] = -(MOD/i) * inv[MOD%i]  (mod MOD)
        // 因为 n <= 10^7 < MOD，所以 MOD % i 一定落在 [1, i-1]，inv[MOD%i] 已算好
        long H = 1;                         // inv[1] = 1
        int[] inv = new int[n + 1];
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = (int) (MOD - (long) (MOD / i) * inv[MOD % i] % MOD);
            H += inv[i];
            if (H >= MOD) H -= MOD;
        }

        // ---------- 4. 答案 = T * ((n+1)*H - 2n) mod MOD ----------
        long sum = ((long) (n + 1) % MOD * H % MOD - (long) 2 * n % MOD + MOD) % MOD;
        return T * sum % MOD;
    }
}
