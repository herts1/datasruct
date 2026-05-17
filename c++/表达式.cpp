#include <stdio.h>

int main() {
    int a, b, max;
    printf("请输入两个整数，用逗号分隔（例如：5,3）：");
    if (scanf("%d,%d", &a, &b) != 2) {
        printf("输入格式错误！\n");
        return 1;
    }
    max = (a > b) ? a : b;
    printf("较大的数是：%d\n", max);
    return 0;
}
