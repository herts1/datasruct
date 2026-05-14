#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// 定义迷宫坐标结构体
typedef struct {
    int x;
    int y;
} Pos;

// 定义栈结构
#define MAX_STACK_SIZE 100  // 栈最大容量
typedef struct {
    Pos data[MAX_STACK_SIZE];
    int top;  // 栈顶指针，-1表示空栈
} Stack;

// 栈初始化
void StackInit(Stack *s);

// 判断栈是否为空
bool StackIsEmpty(Stack *s);

// 入栈
bool StackPush(Stack *s, Pos pos);

// 出栈
bool StackPop(Stack *s, Pos *pos);

// 获取栈顶元素
bool StackTop(Stack *s, Pos *pos);

// 打印栈内路径（从栈底到栈顶）
void StackPrintPath(Stack *s);

#endif // STACK_H
