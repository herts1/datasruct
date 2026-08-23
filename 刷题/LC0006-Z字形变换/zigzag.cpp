/*
 * LC0006 Z字形变换 — C++ 版
 * 算法：按行模拟（与 C 版相同思路）
 * 复杂度：O(n) 时间 / O(n) 空间
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string convert(string s, int numRows) {
    /* 特判：1 行或行数 >= 长度时，结果就是原串 */
    if (numRows == 1 || (int)s.size() <= numRows) return s;

    vector<string> rows(numRows);
    int row = 0, dir = 1;   /* dir = 1 向下，-1 向上 */
    for (char c : s) {
        rows[row] += c;
        row += dir;
        if (row == numRows - 1 || row == 0) dir = -dir;   /* 撞到边界转向 */
    }

    string res;
    for (const string &r : rows) res += r;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int numRows;
    cin >> s >> numRows;
    cout << convert(s, numRows) << '\n';
    return 0;
}
