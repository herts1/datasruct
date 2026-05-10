#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode{
	int foot;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
	
	
}TreeNode,*BiTree;


void preorder(BiTree T){
	if(T){
		printf("%d",T->foot);
		preorder(T->lchild);
		preorder(T->rchild);
	}
} //«∞–Ú

void inorder(BiTree T){
	if(T){
		inorder(T->lchild);
		printf("%d",T->foot);
		inorder(T->rchild);
	}
} //÷––Ú

void postorder(BiTree T){
	if(T){
		postorder(T->lchild);
		postorder(T->rchild);
		printf("%d",T->foot);
	}
} //∫Û–Ú 


int main () {
	return 0;
} 
