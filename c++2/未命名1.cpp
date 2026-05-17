#include<stdio.h>
#include<math.h>
int main () {
    double a,b,c;
    scanf("%lf %lf %lf",&a,&b,&c);
    double o=b*b-4*a*c;
  
    double p=pow(o,0.5);
    double n,m;
    n=(-b+p)/2.0/a;
    m=(-b-p)/2.0/a;
    if(o<0){
		o=-o;
		printf("%.2f+%.2f\i",-b/2,p/2);
		printf("\n");
		printf("%.2f-%.2fi",-b/2,p/2);
		return 0;
		
	}
	if(n!=m){
        printf("%.2f",fmax(n,m));
        printf("\n");
		printf("%.2f",fmin(n,m));
        
    }else{
        printf("%.2f",m);
        
    }
    if(a==0&&b==0&&c==0){
        printf("Zero Equation");
    }
    if(a==0&&b==0&&c!=0){
        printf("Not An Equation");
    }
}
