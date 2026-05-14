#include "stack.h"
#include <stdio.h>

// 栈初始化
void StackInit(Stack *s) {
    s->top = -1;
}

// 判断栈是否为空
bool StackIsEmpty(Stack *s) {
    return s->top == -1;
}

// 入栈
bool StackPush(Stack *s, Pos pos) {
    if (s->top >= MAX_STACK_SIZE - 1) {
        printf("栈已满，无法入栈！\n");
        return false;
    }
    s->top++;
    s->data[s->top] = pos;
    return true;
}

// 出栈
bool StackPop(Stack *s, Pos *pos) {
    if (StackIsEmpty(s)) {
        printf("栈为空，无法出栈！\n");
        return false;
    }
    *pos = s->data[s->top];
    s->top--;
    return true;
}

// 获取栈顶元素
bool StackTop(Stack *s, Pos *pos) {
    if (StackIsEmpty(s)) {
        printf("栈为空，无栈顶元素！\n");
        return false;
    }
    *pos = s->data[s->top];
    return true;
}

// 打印栈内路径（从栈底到栈顶）
void StackPrintPath(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        printf("(%d, %d) ", s->data[i].x, s->data[i].y);
        if (i < s->top) {
            printf("-> ");
        }
    }
    printf("\n");
}
