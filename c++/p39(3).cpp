#include <stdio.h>

int main() {
    int numbers[10];  // 存储10个数字的数组
    int i, j, temp;

    // 输入10个数字
    printf("请输入10个数字（用空格或回车分隔）:\n");
    for (i = 0; i < 10; i++) {
        scanf("%d", &numbers[i]);
    }

    // 冒泡排序（从小到大）
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                // 交换两个数
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    // 输出排序后的结果
    printf("排序后的数字（从小到大）:\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}  
