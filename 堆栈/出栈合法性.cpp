#include <stdio.h>

int main() {
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    
    for (int i = 0; i < k; i++) {
        int seq[1000];  // 存储出栈序列
        for (int j = 0; j < n; j++) {
            scanf("%d", &seq[j]);
        }
        
        // 模拟栈
        int stack[1000];
        int top = -1;  // 栈顶指针
        int current = 1;  // 下一个要入栈的数字
        int valid = 1;    // 标记是否合法
        
        for (int j = 0; j < n; j++) {
            int target = seq[j];  // 当前需要出栈的数字
            
            // 如果栈为空或栈顶不是目标数字，就不断入栈
            while ((top == -1 || stack[top] != target) && current <= n) {
                stack[++top] = current++;
                
                // 检查栈容量是否超限
                if (top + 1 > m) {  // 栈的大小是 top+1
                    valid = 0;
                    break;
                }
            }
            
            if (!valid) break;
            
            // 此时栈顶应该是目标数字
            if (top == -1 || stack[top] != target) {
                valid = 0;
                break;
            }
            
            // 出栈
            top--;
        }
        
        if (valid) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}


/*#include <stdio.h>

int checkSequence(int m, int n, int seq[]) {
    int stack[1000];
    int top = -1;
    int current = 1;
    
    for (int i = 0; i < n; i++) {
        int target = seq[i];
        
        // 入栈直到栈顶等于目标值
        while ((top == -1 || stack[top] != target) && current <= n) {
            stack[++top] = current++;
            if (top + 1 > m) {
                return 0;  // 栈溢出
            }
        }
        
        // 检查是否可以出栈
        if (top == -1 || stack[top] != target) {
            return 0;  // 不匹配
        }
        
        // 出栈
        top--;
    }
    
    return 1;  // 合法
}

int main() {
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    
    for (int i = 0; i < k; i++) {
        int seq[1000];
        for (int j = 0; j < n; j++) {
            scanf("%d", &seq[j]);
        }
        
        if (checkSequence(m, n, seq)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}*/ 
