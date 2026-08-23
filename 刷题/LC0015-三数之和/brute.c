/*
 * 暴力对照程序（仅用于验证，不是正式解）
 * 枚举所有 i<j<k，O(n^3)，只适合小 n 验证。
 * 会输出重复三元组（不同下标组合得到相同值组合），
 * 验证脚本用 Sort-Object -Unique 去重后再与主程序对比。
 */
#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &nums[i]);

    qsort(nums, n, sizeof(int), cmp);   /* 排序保证三元组内 a<=b<=c */

    for (int i = 0; i < n - 2; i++)
        for (int j = i + 1; j < n - 1; j++)
            for (int k = j + 1; k < n; k++)
                if (nums[i] + nums[j] + nums[k] == 0)
                    printf("%d %d %d\n", nums[i], nums[j], nums[k]);

    free(nums);
    return 0;
}
