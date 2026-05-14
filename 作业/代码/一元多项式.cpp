#include<stdio.h>
#include<stdlib.h>
#define max_size 1000

typedef int ElemType;

typedef struct {
    ElemType data[max_size];  // 存储系数和指数，data[0]系数，data[1]指数，data[2]系数，data[3]指数...
    int length;               // 多项式的项数
} List;

void list_create(List *L) {
    int n;
    scanf("%d", &n);          // 先读取项数
    L->length = n * 2;        // 每项包含系数和指数，所以总长度是2n
    
    for(int i = 0; i < n * 2; i += 2) {
        scanf("%d %d", &L->data[i], &L->data[i+1]);  // 读取系数和指数
    }
}

void list_add(List *L1, List *L2) {
    int i = 0, j = 0;  // i指向L1的当前项，j指向L2的当前项
    int count = 0;     // 结果多项式的项数
    
    while(i < L1->length && j < L2->length) {
        // 比较指数
        if(L1->data[i+1] == L2->data[j+1]) {
            // 指数相同，系数相加
            int coef = L1->data[i] + L2->data[j];
            if(coef != 0) {  // 系数不为0才输出
                if(count > 0) printf(" ");  // 项之间用空格分隔
                printf("%d %d", coef, L1->data[i+1]);
                count++;
            }
            i += 2;
            j += 2;
        }
        else if(L1->data[i+1] > L2->data[j+1]) {
            // L1的指数更大
            if(count > 0) printf(" ");
            printf("%d %d", L1->data[i], L1->data[i+1]);
            count++;
            i += 2;
        }
        else {
            // L2的指数更大
            if(count > 0) printf(" ");
            printf("%d %d", L2->data[j], L2->data[j+1]);
            count++;
            j += 2;
        }
    }
    
    // 处理剩余项
    while(i < L1->length) {
        if(count > 0) printf(" ");
        printf("%d %d", L1->data[i], L1->data[i+1]);
        count++;
        i += 2;
    }
    
    while(j < L2->length) {
        if(count > 0) printf(" ");
        printf("%d %d", L2->data[j], L2->data[j+1]);
        count++;
        j += 2;
    }
    
    if(count == 0) {
        printf("0 0");  // 如果结果多项式为0
    }
    printf("\n");
}

int main() {
    // 分配内存！！！！ 
    List *L1 = (List*)malloc(sizeof(List));
    List *L2 = (List*)malloc(sizeof(List));
    
    if(L1 == NULL || L2 == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    
    // 创建多项式
    list_create(L1);
    list_create(L2);
    
    // 相加并输出结果
    list_add(L1, L2);
    
    // 释放内存
    free(L1);
    free(L2);
    
    return 0;
}
