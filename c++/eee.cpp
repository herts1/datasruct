#include<stdio.h>
#include<math.h>
int main () {
    int a,n;
    scanf("%d %d",&a,&n);
    int m=0;
    int o,sum=0;
    for(int t=0;t<=n-1;t++){
        o=pow(10,t);
       
        
        sum+=m;
    }
	printf("s = %d",a*(sum+1));
	
}
