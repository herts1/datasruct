#include<stdio.h>
#define m 3
#define n 4


int main(){
	int a,b,c,o[m][n],p[n][m];
	for(c=1,a=0;a<m;a++){
		for(b=0;b<n;b++){
			o[a][b]=c++;
			printf("%3d",o[a][b]);
		}
	
		putchar('\n');
	}
	printf(":\n");
	for(a=0;a<n;a++){
		for(b=0;b<m;b++){
		p[a][b]=o[b][a];
		printf("%3d",p[a][b]);
		
		}		
		putchar('\n');
	}
	return 0;
}
