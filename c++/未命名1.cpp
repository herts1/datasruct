#include<stdio.h>
int main(){
	int milk_score;
	milk_score=98;
	
	int john_score;
	john_score=89;
	
	int lastmilk_score=john_score;
	john_score=milk_score;
	
	printf("jhon的成绩: %d\n",john_score);
	printf("milk的成绩：%d\n",lastmilk_score);
	return 0;}
