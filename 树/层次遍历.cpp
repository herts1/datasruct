#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/* 队列结构（用于层次遍历） */
typedef struct {
    TreeNode* data[MAX];
    int front;
    int rear;
} Queue;

/* 初始化队列 */
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

/* 入队 */
void enqueue(Queue *q, TreeNode *node) {
    if ((q->rear + 1) % MAX == q->front) {
        printf("队列已满\n");
        return;
    }
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % MAX;
}

/* 出队 */
TreeNode* dequeue(Queue *q) {
    if (q->front == q->rear) {
        return NULL;
    }
    TreeNode *node = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    return node;
}

/* 判断队列是否为空 */
int isEmpty(Queue *q) {
    return q->front == q->rear;
}

/* 创建二叉树（先序输入，#表示空） */
TreeNode* createTree() {
    char ch;
    scanf(" %c", &ch);
    if (ch == '#') return NULL;

    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = ch;
    node->left = createTree();
    node->right = createTree();
    return node;
}

/* 层次遍历 */
void levelOrder(TreeNode *root) {
    if (!root) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        TreeNode *cur = dequeue(&q);
        printf("%c ", cur->data);

        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
}

int main() {
    printf("请输入先序序列（#表示空节点）：\n");
    TreeNode *root = createTree();

    printf("层次遍历结果：\n");
    levelOrder(root);

    return 0;
}
