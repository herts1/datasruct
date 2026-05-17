#include <stdio.h>
#include <string.h> // 用于字符串比较

int main() {
    printf("czg是最帅的吗？(输入yes或no): ");
    
    char answer[10]; // 定义一个足够大的字符数组来存储输入
    scanf("%9s", answer); // 限制输入长度防止溢出
    
    if(strcmp(answer, "no") == 0) {
        printf("你错了！czg明明是最帅的！\n");
    }
    else if(strcmp(answer, "yes") == 0) {
        printf("有眼光！你说得对！\n");
    }
    else {
        printf("请输入yes或no！\n");
    }
    
    return 0;
}
