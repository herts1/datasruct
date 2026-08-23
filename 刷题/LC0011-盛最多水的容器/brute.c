/*
 * 暴力对照程序（仅用于验证，不是正式解）
 * 枚举所有 (i, j) 对，O(n^2) 算面积取最大。
 */
#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int h[1005];
    for (int i = 0; i < n; i++) scanf("%d", &h[i]);

    int best = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int area = (h[i] < h[j] ? h[i] : h[j]) * (j - i);
            if (area > best) best = area;
        }
    printf("%d\n", best);
    return 0;
}
