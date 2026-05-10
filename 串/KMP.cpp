#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_text 1000
#define max_pattern 1000

int kmpsearch(char text[], char pattern[]) {
    int len_text = strlen(text);
    int len_pattern = strlen(pattern);
    
    if (len_pattern == 0) return 0;  // 空模式串
    
    int next[len_pattern];
    next[0] = -1;
    int j = -1, i = 0;
    
    // 计算next数组
    while (i < len_pattern - 1) {  // 防止越界
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    
    i = 0;
    j = 0;
    
    // 主匹配过程
    while (i < len_text && j < len_pattern) {
        if (j == -1 || text[i] == pattern[j]) {  // 处理j=-1的情况
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    
    if (j == len_pattern) {
        return i - j;
    }
    
    return -1;
}
int main () {
	return 0;
} 
