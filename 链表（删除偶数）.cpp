#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createlist();
struct ListNode *deleteeven( struct ListNode *head );
void printlist( struct ListNode *head )
{
     struct ListNode *p = head;
     while (p) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("\n");
}

int main()
{
    struct ListNode *head;

    head = createlist();
    head = deleteeven(head);
    printlist(head);

    return 0;
}

/* 你的代码将被嵌在这里 */
struct ListNode *createlist() {
    struct ListNode *head = NULL;  // 链表头
    struct ListNode *tail = NULL;  // 链表尾，用于尾插法
    int num;
    
    while (scanf("%d", &num) && num != -1) {
        struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        newNode->data = num;
        newNode->next = NULL;
        
        if (head == NULL) {
            // 链表为空，新节点既是头也是尾
            head = newNode;
            tail = newNode;
        } else {
            // 链表非空，插入到尾部
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    return head;
}

struct ListNode *deleteeven(struct ListNode *head) {
    // 先删除链表头部的偶数节点
    while (head != NULL && head->data % 2 == 0) {
        struct ListNode *temp = head;
        head = head->next;
        free(temp);
    }
    
    if (head == NULL) {
        return NULL;
    }
    
    // 删除链表中间的偶数节点
    struct ListNode *prev = head;  // 前驱节点
    struct ListNode *curr = head->next;  // 当前节点
    
    while (curr != NULL) {
        if (curr->data % 2 == 0) {
            // 删除当前节点
            prev->next = curr->next;
            free(curr);
            curr = prev->next;  // curr移动到下一个节点
        } else {
            // 保留当前节点，继续向后
            prev = curr;
            curr = curr->next;
        }
    }
    
    return head;
}
