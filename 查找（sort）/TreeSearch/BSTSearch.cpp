#include<stdio.h>
#include<stdlib.h>
typedef int KeyType ;
typedef int InfoType;

typedef struct node{
	KeyType key;     
	InfoType data; 
	struct node *lchild,*rchild;
}BSTNode;

BSTNode* InsertBST(BSTNode * bt,KeyType k){
	if(bt==NULL){
		bt=(BSTNode *)malloc(sizeof(BSTNode));
		bt->key=k;
		bt->lchild=bt->rchild=NULL;
	}
	else if(k<bt->key){
		bt->lchild=InsertBST(bt->lchild,k);
	}else if(k>bt->key){
		bt->rchild=InsertBST(bt->rchild,k);
	}
	return bt;
}

BSTNode *CreateBST(KeyType a[],int n){
	BSTNode *bt=NULL;
	int i=0;
	while(i<n){
		bt=InsertBST(bt,a[i]);
		i++;
	}
	return bt;
}

BSTNode *SearchBST(BSTNode *bt,KeyType k){
	if((bt==NULL) || (bt->key=k)){
		return bt;
	}
	if(k<bt->key){
		return SearchBST(bt->lchild,k);
	}else{
		return SearchBST(bt->rchild,k);
		
	}
}


int main () {
	return 0;
} 
