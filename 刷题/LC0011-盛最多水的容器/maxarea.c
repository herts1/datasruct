/*
 * LC0011 盛最多水的容器 — C 版
 * 算法：双指针（左右夹逼）
 * 复杂度：O(n) 时间 / O(1) 空间
 *
 * 核心思想：
 *   容器容量 = min(height[l], height[r]) * (r - l)
 *   每次固定一个窗口 [l, r]，容量只由"矮边"决定。
 *   移动"高边"只会让宽度变小，容量不可能增大；
 *   所以只移动"矮边"——虽然宽度变小，但有机会遇到更高的边。
 *
 * 正确性（反证）：假设最优解是 (L, R)。双指针扫描到某一步
 *   矮边在 L 侧且被移动——若 height[l] <= height[R]，那么以 l 为左边
 *   的任何容器都 <= 以 R 为右边、l 为左边的容器 <= 最优解，
 *   所以丢掉 l 不损失最优解。对称同理。因此贪心不丢解。
 */
#include <stdio.h>

static int maxArea(const int *height, int n) {
    int l = 0, r = n - 1, best = 0;
    while (l < r) {
        int h = height[l] < height[r] ? height[l] : height[r];   /* 容量取矮边 */
        int area = h * (r - l);
        if (area > best) best = area;
        if (height[l] < height[r]) l++;   /* 矮边在左 -> 左指针右移 */
        else r--;                          /* 否则右指针左移（相等时移哪边都行） */
    }
    return best;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int h[100005];
    for (int i = 0; i < n; i++) scanf("%d", &h[i]);
    printf("%d\n", maxArea(h, n));
    return 0;
}
