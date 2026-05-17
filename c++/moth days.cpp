#include<stdio.h>
int main(){
	int year,mouth;
	int mouth_days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	printf("请输入年份和月份：");
	scanf("%d%d",&year,&mouth);
	if(year%4==0){
		mouth_days[2]=29;
		
		//TODO
	}
	printf("该月份的天数=%d",mouth_days[mouth]);
	
	}
