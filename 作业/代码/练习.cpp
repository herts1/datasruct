#include<stdio.h>
#define max_size 8

typedef struct snode *stack;
typedef int elementtype;
struct snode{
	elementtype data[max_size];
	int top;
	
};
void push (stack strs,elementtype item){
	if(strs->top==max_size-1){
		printf("full");
		return;
	}else{
		strs->data[++(strs->top)]=item;
		return;
	}
}
elementtype pop(stack strs){
	if(strs->top==-1){
		printf("space");
		return -1;
	}
	else{
		return (strs->data[(strs->top)--]);
		
	}
}

int main() {
	return 0;
}




