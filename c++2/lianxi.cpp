#include<stdio.h>
#include<math.h>
int main () {
	 int a;
	 scanf("%d",&a);
	 
	 
	 for(int n=10;n<100;n*=10){
	            if(a%n==1){
	                int o,p;
	                o = pow(2, n / 10);  // 使用C语言的幂运算函数
					p = o + temp;
					temp = o; 
					 
	               printf("n=%d, o=%d, p=%d, temp=%d\n", n, o, p, temp);
	
	            
				}
				
				 
	 }
	  return 0;
}
