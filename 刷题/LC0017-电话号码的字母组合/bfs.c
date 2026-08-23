/*
 * 独立对照实现：迭代（BFS）版，与回溯代码结构完全不同，可互相抓 bug。
 * 思路：结果列表初始为 [""]，每处理一个数字，
 *       把当前每个前缀分别拼接该数字的所有映射字母，形成新列表。
 * 只用于本地验证（固定上限：digits <= 4 位，最多 4^4 = 256 个组合）。
 */
#include <stdio.h>
#include <string.h>

static const char *table[10] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

int main(void) {
    char digits[8];
    if (scanf("%s", digits) != 1) return 0;
    int n = (int)strlen(digits);
    if (n == 0) return 0;          /* 空串 -> 无输出 */

    char cur[256][5], nxt[256][5]; /* 当前列表 / 下一列表 */
    int cnt = 1;
    cur[0][0] = '\0';

    for (int d = 0; d < n; d++) {
        const char *letters = table[digits[d] - '0'];
        int len = (int)strlen(letters);
        int k = 0;
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < len; j++) {
                strcpy(nxt[k], cur[i]);          /* 复制前缀 */
                nxt[k][d] = letters[j];          /* 拼接新字母 */
                nxt[k][d + 1] = '\0';
                k++;
            }
        }
        cnt = k;
        for (int i = 0; i < cnt; i++) strcpy(cur[i], nxt[i]);
    }

    for (int i = 0; i < cnt; i++) printf("%s\n", cur[i]);
    return 0;
}
