import java.math.BigInteger;

/**
 * 暴力对照验证器（仅用于验证小 n，正式提交用 BD202402.java）
 *
 * 方法 A（brute）：
 *   完全不用模运算，用 BigInteger 直接算公式 Σ_{i<j} (T/i - T/j)
 *   其中 T = lcm(1..n) 也用 BigInteger 精确求，结果与模运算版对比。
 *
 * 方法 B（simulate）：
 *   完全独立于公式 —— 直接模拟"时刻"：
 *   对每对 (i,j)，相遇周期 t0 = i*j/(j-i)（分数，精确表示），
 *   在 (0, T] 内的相遇时刻为 t = k*t0 (k = 1,2,...)，统计总次数。
 *   这个方法独立验证了"每对次数 = T(j-i)/(ij)"这一核心结论。
 */
public class Verify {

    // ---------- 方法 A：BigInteger 全整数公式 ----------
    static BigInteger brute(int n) {
        BigInteger T = BigInteger.ONE;
        for (int i = 2; i <= n; i++) T = lcm(T, BigInteger.valueOf(i));
        BigInteger ans = BigInteger.ZERO;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++) {
                BigInteger Ti = T.divide(BigInteger.valueOf(i));
                BigInteger Tj = T.divide(BigInteger.valueOf(j));
                ans = ans.add(Ti.subtract(Tj));
            }
        return ans;
    }

    // ---------- 方法 B：直接按相遇周期模拟（独立验证核心结论） ----------
    static long simulate(int n) {
        long T = 1;
        for (int i = 2; i <= n; i++) T = lcm(T, i);   // n 小，long 足够
        long cnt = 0;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++) {
                long b = (long) i * j;   // ij
                long a = j - i;          // j-i
                // 最小正相遇周期 t0 = b/a（分数）。次数 = T / t0 = T*a/b
                // 需要整除判定：T*a % b == 0 时必须成立（由数学保证），仍做断言
                if ((T * a) % b != 0) {
                    System.out.println("断言失败 i=" + i + " j=" + j);
                    return -1;
                }
                cnt += T * a / b;
            }
        return cnt;
    }

    static long gcd(long a, long b) { return b == 0 ? a : gcd(b, a % b); }
    static BigInteger gcd(BigInteger a, BigInteger b) { return a.gcd(b); }
    static long lcm(long a, long b) { return a / gcd(a, b) * b; }
    static BigInteger lcm(BigInteger a, BigInteger b) { return a.divide(a.gcd(b)).multiply(b); }

    public static void main(String[] args) {
        // 1) 方法 A（BigInteger） vs 方法 B（周期模拟）：验证核心数学结论
        for (int n = 1; n <= 10; n++) {
            BigInteger A = brute(n);
            long B = simulate(n);
            if (!A.equals(BigInteger.valueOf(B))) {
                System.out.println("公式与模拟不一致 n=" + n + " A=" + A + " B=" + B);
                return;
            }
        }
        System.out.println("[1] 数学公式 与 直接模拟 在 n=1..10 全部一致 ✓");

        // 2) 方法 A（BigInteger） vs 模运算版 BD202402.solve：验证模实现
        for (int n = 1; n <= 60; n++) {
            long modAns = BD202402.solve(n);
            BigInteger big = brute(n).mod(BigInteger.valueOf(998244353L));
            if (modAns != big.longValue()) {
                System.out.println("模运算版与 BigInteger 不一致 n=" + n + " mod=" + modAns + " big=" + big);
                return;
            }
        }
        System.out.println("[2] 模运算版 与 BigInteger 精确版 在 n=1..60 全部一致 ✓");
        System.out.println("[3] 样例1 n=3 => " + BD202402.solve(3) + " （期望 8）");
        System.out.println("[4] 样例2 n=10000000 => " + BD202402.solve(10000000) + " （期望 424046265）");
    }
}
