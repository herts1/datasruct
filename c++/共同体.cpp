#include<stdio.h>
#include<string.h>
union Data{
	int i;
	float f;
	char str[20];
	
	
};
int main (){
	union Data date;
	printf("dateµÄsize´óÐ¡£º%d\n",sizeof(date));
	return 0 ;
	

}
