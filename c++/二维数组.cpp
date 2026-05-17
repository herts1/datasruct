#include<stdio.h>
#define N 4
#define M 3
int main(){
	int i,j,k,m[N][M],n[M][N];
	for(k=1,i=0;i<N;i++){
		for(j=0;j<M;printf("%3d",m[i][j++]=k++));
		putchar('\n');
		
	}
	printf("×ªÖÆºó£º\n");
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;printf("%3d",n[i][j]=m[j++][i]));
		putchar('\n');
	
	}
	return 0;
	
	
}
