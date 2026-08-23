/*
 * LC0015 三数之和 — LeetCode 官方 C 提交格式
 *
 * 直接可提交版本：函数返回 int**（三元组数组），
 *   *returnSize 存放三元组个数，
 *   *returnColumnSizes 存放每个三元组的列数（本题恒为 3）。
 * 返回的数组和 columnSizes 均为 malloc 分配，由评测器负责 free。
 *
 * 算法：排序 + 双指针（与 threesum.c 相同），O(n^2) 时间 / O(n) 额外空间（结果数组）。
 */
#include <stdlib.h>

/* qsort 比较函数 */
static int cmp(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    *returnSize = 0;
    if (numsSize < 3) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), cmp);

    /* 结果数组动态增长（容量倍增） */
    int cap = 64;
    int **res = (int **)malloc(cap * sizeof(int *));

    for (int i = 0; i < numsSize - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;   /* 去重① */
        if (nums[i] > 0) break;                          /* 剪枝 */

        int l = i + 1, r = numsSize - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                /* 容量不够就扩容 */
                if (*returnSize == cap) {
                    cap *= 2;
                    res = (int **)realloc(res, cap * sizeof(int *));
                }
                int *tri = (int *)malloc(3 * sizeof(int));
                tri[0] = nums[i];
                tri[1] = nums[l];
                tri[2] = nums[r];
                res[(*returnSize)++] = tri;

                while (l < r && nums[l] == nums[l + 1]) l++;   /* 去重② */
                while (l < r && nums[r] == nums[r - 1]) r--;   /* 去重③ */
                l++;
                r--;
            } else if (sum < 0) {
                l++;
            } else {
                r--;
            }
        }
    }

    /* 每行列数恒为 3 */
    *returnColumnSizes = (int *)malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = 3;

    return res;
}
