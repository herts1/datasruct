/*
 * LC0011 盛最多水的容器 — C++ 版
 * 与 C 版相同的双指针思路。复杂度 O(n) 时间 / O(1) 空间。
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxArea(const vector<int> &height) {
    int l = 0, r = (int)height.size() - 1, best = 0;
    while (l < r) {
        int area = min(height[l], height[r]) * (r - l);
        best = max(best, area);
        if (height[l] < height[r]) l++;   /* 移动矮边 */
        else r--;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    cout << maxArea(h) << '\n';
    return 0;
}
