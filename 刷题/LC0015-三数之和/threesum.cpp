/*
 * LC0015 三数之和 — C++ 版
 * 与 C 版相同的"排序 + 双指针"思路。
 * 复杂度：O(n^2) 时间 / O(1) 额外空间
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;   /* 去重① */
        if (nums[i] > 0) break;                          /* 剪枝 */

        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                cout << nums[i] << ' ' << nums[l] << ' ' << nums[r] << '\n';
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
    return 0;
}
