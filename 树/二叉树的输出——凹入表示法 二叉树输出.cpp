#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/* 创建结点 */
TreeNode* createNode(char c) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 在中序中找根位置 */
int findRoot(char in[], int L, int R, char root) {
    for (int i = L; i <= R; i++) {
        if (in[i] == root)
            return i;
    }
    return -1;
}

/* 建树 */
TreeNode* buildTree(char pre[], char in[], int L, int R, int *preIndex) {
    if (L > R) return NULL;

    TreeNode* root = createNode(pre[*preIndex]);
    (*preIndex)++;

    if (L == R) return root;

    int inRoot = findRoot(in, L, R, root->data);
    root->left = buildTree(pre, in, L, inRoot - 1, preIndex);
    root->right = buildTree(pre, in, inRoot + 1, R, preIndex);

    return root;
}

/* 计算结点凹入长度 */
int calcLen(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return calcLen(root->left) + calcLen(root->right);
}

/* 凹入表示法输出 */
void printIndent(TreeNode* root) {
    if (root == NULL) return;

    int len = calcLen(root);
    for (int i = 0; i < len; i++)
        printf("%c", root->data);
    printf("\n");

    printIndent(root->left);
    printIndent(root->right);
}

int main() {
    char pre[55], in[55];
    scanf("%s", pre);
    scanf("%s", in);

    int preIndex = 0;
    TreeNode* root = buildTree(pre, in, 0, strlen(in) - 1, &preIndex);

    printIndent(root);
    return 0;
}
