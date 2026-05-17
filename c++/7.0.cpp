#include<stdint.h>
#include<stdio.h>
int main(){
	int n;
	printf("请输入n=");
	scanf("%d",&n);
	if(n<0){
		printf("n不能小于0");
		
	}
 	int f[n];
	f[0] = 1;
	if (n >= 2) {
	         f[1] = 1;
	}
	 
	 
	 for (int i = 2; i < n; i++) {
        f[i] = f[i - 2] + f[i - 1];
    }

    // 打印结果
    for (int i = 0; i < n; i++) {
        printf("%ld ", f[i]); // 调整为更合理的格式
    }
    printf("\n");
	
	return 0;
}
