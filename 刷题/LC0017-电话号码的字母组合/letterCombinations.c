/*
 * LC0017 电话号码的字母组合 — LeetCode 官方 C 提交格式
 *
 * 可直接提交版本：
 *   char **letterCombinations(char *digits, int *returnSize)
 * 返回 malloc 分配的字符串数组，*returnSize 为组合个数，
 * 每个字符串也是 malloc 分配，由评测器统一 free。
 *
 * 算法：回溯（DFS）
 *   逐位选择：对 digits[pos] 的每个映射字母，递归处理下一位，
 *   到末尾时把当前组合写入结果。
 * 复杂度：O(3^m * 4^n) 个结果（m 个 3 字母数字、n 个 4 字母数字），
 *         每个结果长度 len，总时间 O(结果数 * len)，空间 O(len + 结果数)。
 */
#include <stdlib.h>
#include <string.h>

/* 数字 -> 字母映射表（0/1 无对应，留空） */
static const char *table[10] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

static void dfs(const char *digits, int pos, int n,
                char *buf, char **res, int *cnt) {
    if (pos == n) {                      /* 所有位都选好了 */
        buf[n] = '\0';
        res[*cnt] = (char *)malloc((n + 1) * sizeof(char));
        strcpy(res[*cnt], buf);
        (*cnt)++;
        return;
    }
    const char *letters = table[digits[pos] - '0'];
    for (int i = 0; letters[i] != '\0'; i++) {
        buf[pos] = letters[i];           /* 第 pos 位选 letters[i] */
        dfs(digits, pos + 1, n, buf, res, cnt);
    }
}

char **letterCombinations(char *digits, int *returnSize) {
    *returnSize = 0;
    int n = (int)strlen(digits);
    if (n == 0) return NULL;

    /* 组合总数 = 每个数字字母数的乘积 */
    int total = 1;
    for (int i = 0; i < n; i++)
        total *= (int)strlen(table[digits[i] - '0']);

    char **res = (char **)malloc(total * sizeof(char *));
    char *buf = (char *)malloc((n + 1) * sizeof(char));

    dfs(digits, 0, n, buf, res, returnSize);

    free(buf);
    return res;
}
