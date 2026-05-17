#include<stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	long int f[n]={1,1};
	int i;
	for(i=2;i<=n-1;i++)
	{
		f[i]=f[i-2]+f[i-1];
		
	}
	for(i=0;i<=n-1;i++)
	{
		printf("%41ld",f[i]);
		
	}
}
