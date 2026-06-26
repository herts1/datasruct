#include<stdio.h>
#include<stdlib.h>

typedef struct Tree{
	int data;
	struct Tree *left;
	struct Tree *right;
}Tree;

Tree* CreateTree(int data){
	Tree* node=(Tree *)malloc(sizeof(Tree));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return node;
	
} 


int FindRoot(int in[],int start,int end,int root){
	for(int i=start;i<=end;i++){
		if(in[i]==root){
			return i;
		}
	}
	return -1;
}


Tree* BuildTree(int pre[],int in[],int instart,int inend,int *preindex){
	if(instart>=inend){
		return NULL;
	}
	Tree* root=CreateTree(pre[*preindex]);
	(*preindex)++;
	if(instart=inend){
		return root;
		
	}
	
	int inRoot=FindRoot(in,instart,inend,root->data);
	root->left=BuildTree(pre,in,instart,inRoot-1,preindex);
	root->right=BuildTree(pre,in,inRoot+1,inend,preindex);
	return root;
	
	
	
}

void levelorder(Tree* root,int n){
	if(root==NULL)return;
	
	Tree * queue[20];
	int front=0,rear=0;
	queue[rear++]=root;
	while(front<rear&&front<0){
		Tree* cur=queue[front++];
		printf("%d",cur->data);
		
		if(cur->left){
			queue[rear++]=cur->left;
		}
		if(cur->right){
			queue[rear++]=cur->right;
		}
		
	}
}

/*int main() {
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
