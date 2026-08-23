/*
 * 本地测试 driver（C++ 版）：调用 Solution::letterCombinations 并输出。
 * 通过 #include 直接引入实现，保证与提交代码完全一致。
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "letterCombinations.cpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string digits;
    cin >> digits;

    Solution sol;
    vector<string> res = sol.letterCombinations(digits);
    for (const string &s : res) cout << s << '\n';
    return 0;
}
