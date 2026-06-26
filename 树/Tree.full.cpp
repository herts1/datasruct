#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct TNode{
	Elemtype foot;
	struct TNode *left;
	struct TNode *right; 
	
}TNode; 
//创建树节点 
TNode* TNode_create(int val){
	TNode* T=(TNode *)malloc(sizeof(TNode));
	T->foot=val;
	T->left=NULL;
	T->right=NULL;
	return T;
}
//前序遍历：根-左-右
void preorder(TNode *T){
	if(T==NULL)return;
	printf("%d ",T->foot);
	preorder(T->left);
	preorder(T->right);
} 
//中序遍历；左-根-右
void inorder(TNode *T){
	if(T==NULL)return;
	inorder(T->left);
	printf("%d ",T->foot);
	inorder(T->right);
} 
//后序遍历；左-右-根
void postorder(TNode *T){
	if(T==NULL)return;
	postorder(T->left);
	postorder(T->right);
	printf("%d ",T->foot);
} 
//求树的深度 
int Tree_depth(TNode *T){
	if(T==NULL)return 0;
	int left_depth=Tree_depth(T->left);
	int right_depth=Tree_depth(T->right);
	return (left_depth>right_depth)?left_depth+1:right_depth+1;
}
// 求节点总数
int Tree_count(TNode *T){
	if(T==NULL)return 0;
	return Tree_count(T->left)+Tree_count(T->right+1);
}

int main () {
	return 0;
} 

