/*
 * 暴力对照程序（仅用于验证，不是正式解）
 * 独立思路：用 long long 累加，一旦绝对值超过 int 范围就提前 break
 * （后续数字只会更大，结果必为边界值），最后统一 clamp。
 * 由于"超过 2^31 即 break"，long long 永远不会真正溢出。
 */
#include <stdio.h>
#include <limits.h>
#include <string.h>

int main(void) {
    char s[205];
    if (fgets(s, sizeof(s), stdin) == NULL) return 0;
    s[strcspn(s, "\r\n")] = '\0';

    int n = (int)strlen(s);
    int i = 0;
    while (i < n && s[i] == ' ') i++;

    int sign = 1;
    if (i < n && (s[i] == '-' || s[i] == '+')) {
        if (s[i] == '-') sign = -1;
        i++;
    }

    /* 正数累加（绝对值），超过 2^31 就停 */
    long long val = 0;
    while (i < n && s[i] >= '0' && s[i] <= '9') {
        int d = s[i] - '0';
        if (val > 2147483648LL) break;      /* 已远超 int 范围，结果定死 */
        val = val * 10 + d;
        i++;
    }

    /* clamp 到 [INT_MIN, INT_MAX] */
    if (val > 2147483647LL) {
        printf("%d\n", sign == 1 ? INT_MAX : INT_MIN);
    } else {
        printf("%d\n", (int)(sign * val));
    }
    return 0;
}
