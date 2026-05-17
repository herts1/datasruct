#include<stdio.h>
#include<stdlib.h>
#define SIZE 3
int main(){
	int *pt=NULL;
	pt=(int*)malloc(SIZE*sizeof(int));
	if (pt==NULL){
		printf("内存未被申请成功");
		return 0;
		
	}
	for(int i=0;i<SIZE;i++){
		pt[i]=i;
		//TODO
	}
	for(int i=0;i<SIZE;i++){
	printf("%d\n",pt[i]);
			//TODO
	}
	free(pt);
	return 0;
}
