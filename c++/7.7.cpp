#include <stdio.h>
#include <stdlib.h> // 用于动态内存分配

int main() {
    int n;
    printf("请输入要生成的斐波那契数的个数 n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n 必须为正整数！\n");
        return 1;
    }

    // 动态分配内存，避免VLA问题
    long int *f = (long int *)malloc(n * sizeof(long int));
    if (f == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }

    // 初始化前两项
    f[0] = 1;
    if (n >= 2) {
        f[1] = 1;
    }

    // 生成斐波那契数列
    for (int i = 2; i < n; i++) {
        f[i] = f[i - 2] + f[i - 1];
    }

    // 打印结果
    for (int i = 0; i < n; i++) {
        printf("%ld ", f[i]); // 调整为更合理的格式
    }
    printf("\n");

    free(f); // 释放内存
    return 0;
}
