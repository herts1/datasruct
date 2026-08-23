/*
 * LC0008 字符串转换整数 myAtoi — C++ 版
 * 与 C 版完全相同的思路：四阶段 + 乘法前防溢出判断。
 * 复杂度：O(n) 时间 / O(1) 空间
 */
#include <iostream>
#include <string>
#include <climits>
using namespace std;

int myAtoi(string s) {
    int n = (int)s.size();
    int i = 0;

    /* 1) 跳过前导空格 */
    while (i < n && s[i] == ' ') i++;

    /* 2) 符号 */
    int sign = 1;
    if (i < n && (s[i] == '-' || s[i] == '+')) {
        if (s[i] == '-') sign = -1;
        i++;
    }

    /* 3) 读数字，正数累加 + 乘法前防溢出 */
    int ans = 0;
    while (i < n && s[i] >= '0' && s[i] <= '9') {
        int d = s[i] - '0';
        if (ans > (INT_MAX - d) / 10) {        /* ans*10+d 必超 INT_MAX */
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        ans = ans * 10 + d;
        i++;
    }

    /* 4) 套符号 */
    return sign * ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);             /* 整行读入，保留行内空格 */
    cout << myAtoi(s) << '\n';
    return 0;
}
