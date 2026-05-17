 #include <stdio.h>
 #include <stdlib.h>
 
 typedef struct TreeNode {
     int data;
     struct TreeNode *left;
     struct TreeNode *right;
 } TreeNode;
 
 /* 创建新结点 */
 TreeNode* createNode(int data) {
     TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
     node->data = data;
     node->left = NULL;
     node->right = NULL;
     return node;
 }
 
 /* 在中序序列中查找根结点位置 */
 int findRoot(int in[], int start, int end, int root) {
     for (int i = start; i <= end; i++) {
         if (in[i] == root)
             return i;
     }
     return -1;
 }
 
 /*
    构建二叉树
    preStart: 先序起始下标
    inStart, inEnd: 中序区间
 */
 TreeNode* buildTree(int pre[], int in[], int inStart, int inEnd, int *preIndex) {
     if (inStart > inEnd)
         return NULL;
 
     TreeNode* root = createNode(pre[*preIndex]);
     (*preIndex)++;
 
     if (inStart == inEnd)
         return root;
 
     int inRoot = findRoot(in, inStart, inEnd, root->data);
     root->left = buildTree(pre, in, inStart, inRoot - 1, preIndex);
     root->right = buildTree(pre, in, inRoot + 1, inEnd, preIndex);
 
     return root;
 }
 
 /* 按层遍历（队列实现） */
 void levelOrder(TreeNode* root, int n) {
     if (root == NULL) return;
 
     TreeNode* queue[20];   // 最多10个结点，队列足够大
     int front = 0, rear = 0;
 
     queue[rear++] = root;
 
     while (front < rear && front < n) {
         TreeNode* cur = queue[front++];
         printf("%d ", cur->data);
 
         if (cur->left)
             queue[rear++] = cur->left;
         if (cur->right)
             queue[rear++] = cur->right;
     }
 }
 
 int main() {
     int n;
     scanf("%d", &n);
 
     int pre[15], in[15];
     for (int i = 0; i < n; i++)
         scanf("%d", &pre[i]);
     for (int i = 0; i < n; i++)
         scanf("%d", &in[i]);
 
     int preIndex = 0;
     TreeNode* root = buildTree(pre, in, 0, n - 1, &preIndex);
 
     levelOrder(root, n);
     printf("\n");
 
     return 0;
 }
