/*
 * LC0017 电话号码的字母组合 — LeetCode 官方 C++ 提交格式
 * class Solution { vector<string> letterCombinations(string digits); }
 * 算法：回溯（DFS），与 C 版相同。
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) return res;
        string buf(digits.size(), ' ');
        dfs(digits, 0, buf, res);
        return res;
    }

private:
    static const char *table[10];

    void dfs(const string &digits, int pos, string &buf, vector<string> &res) {
        if (pos == (int)digits.size()) {
            res.push_back(buf);
            return;
        }
        for (const char *p = table[digits[pos] - '0']; *p != '\0'; p++) {
            buf[pos] = *p;
            dfs(digits, pos + 1, buf, res);
        }
    }
};

const char *Solution::table[10] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};
