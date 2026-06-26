#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_text 1000
#define max_pattern 1000
int BF(char text[],char pattern[],int len_text,int len_pattern){
	int i=0,j=0;

	while(i<len_text&&j<len_pattern){
		if(text[i]==pattern[j]){
			i++;
			j++;
		}else{
			j=i-j+1;
		}
		if(j==len_pattern){
			return i-j;
		}
	}
	return -1;
}
int main () {
	char text[max_text];
	char pattern[max_pattern];
	fgets(text,max_text,stdin);
	fgets(pattern,max_pattern,stdin);
	int len_text=strlen(text);
	int len_pattern=strlen(pattern);
	if(len_pattern>0&&pattern[len_pattern-1]=='\n'){
		pattern[len_pattern-1]='\0';
		len_pattern--;
	}
	if(len_text>0&&text[len_text-1]=='\n'){
			text[len_text-1]='\0';
			len_text--;
	}
	int result=BF(text,pattern,len_text,len_pattern);
	printf("%d",result);
}
