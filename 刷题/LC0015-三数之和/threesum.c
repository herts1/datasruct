/*
 * LC0015 三数之和 — C 版
 * 算法：排序 + 双指针
 * 复杂度：O(n^2) 时间 / O(1) 额外空间（排序 O(n log n)）
 *
 * 思路：
 *   1. 排序，让重复值相邻，且固定顺序可去重
 *   2. 固定第一个数 nums[i]，问题变成：在 [i+1, n-1] 找两数和 = -nums[i]
 *   3. 两数之和用双指针 l、r 夹逼（有序数组的经典做法）
 *   4. 去重三处：
 *      - 外层：nums[i] == nums[i-1] 跳过（同一首元素只处理一次）
 *      - 内层：找到一组后，跳过重复的 nums[l]、nums[r]
 *   5. 剪枝：nums[i] > 0 时后面全 > 0，直接结束
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

    qsort(nums, n, sizeof(int), cmp);

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;   /* 去重①：首元素 */
        if (nums[i] > 0) break;                          /* 剪枝：最小数 > 0，三数和必 > 0 */

        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                printf("%d %d %d\n", nums[i], nums[l], nums[r]);
                while (l < r && nums[l] == nums[l + 1]) l++;   /* 去重②：跳过重复左值 */
                while (l < r && nums[r] == nums[r - 1]) r--;   /* 去重③：跳过重复右值 */
                l++;
                r--;
            } else if (sum < 0) {
                l++;                    /* 和太小，左指针右移增大 */
            } else {
                r--;                    /* 和太大，右指针左移减小 */
            }
        }
    }

    free(nums);
    return 0;
}
