import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/**
 * BD202404 110串（百度之星 2024）— Java 版
 *
 * 题意：修改不超过 k 个字符，使最终串不含子串 "110"，求方案数 mod 998244353。
 * 方案数 = 与给定串汉明距离 <= k 且不含 "110" 的串的数量。
 *
 * 计数 DP：
 *   "110" 是长度为 3 的模式，所以判断是否合法只需看"最后两位"。
 *   从左到右构造最终串，维护最后两位 (last2, last1)（4 种状态），
 *   以及已经修改的次数 cnt。
 *
 *   状态：dp[state][cnt]，state = (last2 << 1) | last1
 *   转移：放新位 b ∈ {0,1}，若 (last2,last1,b) == (1,1,0) 则非法跳过；
 *        新状态 nstate = (last1 << 1) | b；修改次数 += (b != 原串当前位)。
 *
 *   初始：第 1 位前没有前两位，用一个"虚拟前位 0"（不会误判 110，
 *        因为 110 需要 last2=1；而第 2 位时串长还不到 3，本来就不可能出 110）。
 *
 * 时间复杂度 O(n·k·8) ≈ 2e8，空间 O(4·k)（滚动数组）。
 */
public class BD202404 {
    static final int MOD = 998244353;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] parts = br.readLine().trim().split("\\s+");
        int n = Integer.parseInt(parts[0]);
        int k = Integer.parseInt(parts[1]);
        String s = br.readLine().trim();
        System.out.println(solve(n, k, s));
    }

    static long solve(int n, int k, String s) {
        k = Math.min(k, n);              // 最多只能改 n 个位置
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = s.charAt(i) - '0';

        // dp[state][cnt]：state = (last2 << 1) | last1
        long[][] dp = new long[4][k + 1];

        // ---- 放第 1 位：虚拟前位 = 0，状态 (0, b) ----
        for (int b = 0; b <= 1; b++) {
            int cost = (b != a[0]) ? 1 : 0;
            if (cost <= k) dp[b][cost] = 1;
        }

        // ---- 依次放第 2..n 位 ----
        for (int i = 1; i < n; i++) {
            long[][] ndp = new long[4][k + 1];
            for (int st = 0; st < 4; st++) {
                int last2 = st >> 1, last1 = st & 1;
                long[] cur = dp[st];
                for (int cnt = 0; cnt <= k; cnt++) {
                    long v = cur[cnt];
                    if (v == 0) continue;
                    for (int b = 0; b <= 1; b++) {
                        if (last2 == 1 && last1 == 1 && b == 0) continue; // 会形成 110，非法
                        int nst = (last1 << 1) | b;
                        int ncnt = cnt + (b != a[i] ? 1 : 0);
                        if (ncnt <= k) {
                            ndp[nst][ncnt] += v;
                            if (ndp[nst][ncnt] >= MOD) ndp[nst][ncnt] -= MOD;
                        }
                    }
                }
            }
            dp = ndp;
        }

        // ---- 统计所有状态、所有修改次数 <= k 的方案 ----
        long ans = 0;
        for (int st = 0; st < 4; st++)
            for (int cnt = 0; cnt <= k; cnt++) {
                ans += dp[st][cnt];
                if (ans >= MOD) ans -= MOD;
            }
        return ans;
    }
}
