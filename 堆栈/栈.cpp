#include<stdio.h>
#define max_size 8
typedef struct SNode *Stack;
typedef int ElementType;

struct SNode {
	ElementType Data[max_size];
	int top;
};
void Push(Stack Ptrs, ElementType item){
	if(Ptrs->top==max_size-1){
		printf("Тњ");
		return;
	}else {
		Ptrs->Data[++(Ptrs->top)] =item;
		return;
		}
		 
}

/*void Push(struct DStack *Ptrs,Elementtype item,int tag){
	if(PtrS->Top2-PtrS->top1==1){
		printf("full");
		return ;
	}
	if(tsg==1){
	PtrS->Data[++(PtrS->Top1)]=item;
	}else{
	PtrS->Data[--(PtrS->Top2]]=item;

}

}*/








ElementType Pop(Stack Ptrs){
	if(Ptrs->top==-1){
		printf("Пе");
		return -1;//ERROR?
	}else{
		return (Ptrs->Data[(Ptrs->top)--]);
	}
}

int main () {
	return 0;
}
