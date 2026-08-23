import java.util.Random;

/**
 * 暴力验证器（仅用于小 n 验证正确性，正式提交用 BD202404.java）
 * 思路：直接枚举 2^n 个最终串，检查 (1) 不含 110 (2) 与给定串汉明距离 <= k
 * 与 DP 结果逐项对比。
 */
public class Brute110 {

    static boolean has110(String t) {
        for (int i = 0; i + 2 < t.length(); i++)
            if (t.charAt(i) == '1' && t.charAt(i + 1) == '1' && t.charAt(i + 2) == '0') return true;
        return false;
    }

    static int hamming(String s, String t) {
        int d = 0;
        for (int i = 0; i < s.length(); i++) if (s.charAt(i) != t.charAt(i)) d++;
        return d;
    }

    static long brute(int n, int k, String s) {
        long cnt = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            char[] c = new char[n];
            for (int i = 0; i < n; i++) c[i] = ((mask >> i) & 1) == 1 ? '1' : '0';
            String t = new String(c);
            if (!has110(t) && hamming(s, t) <= k) cnt++;
        }
        return cnt % 998244353L;
    }

    public static void main(String[] args) {
        long checked = 0;

        // 1) n=1..10：所有可能的输入串 × 所有 k（彻底枚举）
        for (int n = 1; n <= 10; n++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                char[] c = new char[n];
                for (int i = 0; i < n; i++) c[i] = ((mask >> i) & 1) == 1 ? '1' : '0';
                String s = new String(c);
                for (int k = 0; k <= n; k++) {
                    long b = brute(n, k, s);
                    long d = BD202404.solve(n, k, s);
                    if (b != d) {
                        System.out.println("MISMATCH n=" + n + " k=" + k + " s=" + s + " brute=" + b + " dp=" + d);
                        return;
                    }
                    checked++;
                }
            }
        }

        // 2) n=11..14：随机 200 个（暴力 2^14 次枚举，稍慢但可接受）
        Random rnd = new Random(42);
        for (int t = 0; t < 200; t++) {
            int n = 11 + rnd.nextInt(4);
            int k = rnd.nextInt(n + 2);
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < n; i++) sb.append(rnd.nextInt(2));
            String s = sb.toString();
            long b = brute(n, k, s);
            long d = BD202404.solve(n, k, s);
            if (b != d) {
                System.out.println("MISMATCH n=" + n + " k=" + k + " s=" + s + " brute=" + b + " dp=" + d);
                return;
            }
            checked++;
        }

        System.out.println("[BRUTE] all " + checked + " cases match (n=1..10 exhaustive + n=11..14 random)");
        System.out.println("[SAMPLE] n=5 k=2 s=11000 => " + BD202404.solve(5, 2, "11000") + " (expect 8)");
    }
}
