/*
 * 本地测试 driver（C 版）：模拟评测器调用 letterCombinations，
 * 逐行输出组合，并 free 所有分配。提交时不需要本文件。
 */
#include <stdio.h>
#include <stdlib.h>

char **letterCombinations(char *digits, int *returnSize);

int main(void) {
    char digits[8];
    if (scanf("%s", digits) != 1) return 0;

    int returnSize;
    char **res = letterCombinations(digits, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", res[i]);
        free(res[i]);
    }
    free(res);
    return 0;
}
