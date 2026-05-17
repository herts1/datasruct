#include<stdio.h>
int main(){
	int n;
	printf("«Î ‰»În=");
	scanf("%d",&n);
	
	if(n<0){
		printf("≥ˆ¥Ì£°");
		return 1;
		
		//TODO
	}
	
	if(n>=0){
		long int f[n]={1,1};
		int i;
		for(i=2;i<=n;i++)
		{
			//TODO
		
		f[i]=f[i-1]+f[i-2];
		}
		//TODO
		for(i=0;i<=n;i++)
		{
			printf("%41d",f[i]);
		}
	}
}
