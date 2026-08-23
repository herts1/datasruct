/*
 * 本地测试 driver：模拟 LeetCode 评测器调用 threeSum，
 * 读入 n 和数组，输出结果三元组（每行 "a b c"），并负责 free。
 * 仅用于验证 threeSum_solution.c，提交时不需要本文件。
 */
#include <stdio.h>
#include <stdlib.h>

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes);

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &nums[i]);

    int returnSize;
    int *returnColumnSizes;
    int **res = threeSum(nums, n, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        printf("%d %d %d\n", res[i][0], res[i][1], res[i][2]);
        free(res[i]);
    }
    free(res);
    free(returnColumnSizes);
    free(nums);
    return 0;
}
