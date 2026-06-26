#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define max_size 1000
typedef int Elemtype;
typedef struct{
	Elemtype data[max_size];
	int top;
	
}Stack;

void stack_initial(Stack *S){
	S->top=-1;
}

bool stack_isempty(Stack *S){
	return S->top==-1;
	
}

bool stack_isfull(Stack *S){
	return S->top==max_size-1;
}

void push(Stack *S , int n){
	if(!stack_isfull(S)){
		S->data[++(S->top)]=n;
		 
	}else{
		printf("栈已满，无法入栈"); 
	}
}

int pop(Stack *S){
	if(!stack_isempty(S)){
		return S->data[(S->top)--];
		
	} 
}


int main () {
	
}







