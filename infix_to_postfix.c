#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_LINE 3073

void ToPrefix(char *line);
void RmNewLine(char *input);
int main(){
	char line_input[MAX_LINE];

	while(fgets(line_input, MAX_LINE, stdin)){
		RmNewLine(line_input);
		ToPrefix(line_input);
	}

	return 0;
}
void ToPrefix(char *ptr){
	char stack[MAX_LINE];
	int stack_cnt = 0;
	while(*ptr){
		if(isalnum(*ptr)){
			while(*ptr && (isalnum(*ptr) || *ptr=='.')){
				printf("%c", *ptr++);
			}
			printf(" ");
		}

		else if(*ptr && (*ptr=='+' || *ptr=='-')){
			if(stack_cnt==0 || stack[stack_cnt-1]=='(')
				stack[stack_cnt++] = *ptr++;
			else{
					printf("%c ", stack[--stack_cnt]);
				for(int i=stack_cnt; i!=0&&stack[i-1]!='*'&&stack[i-1]!='/'&&stack[i-1]!='('; i--){	
					printf("%c ", stack[--stack_cnt]);
				}
				stack[stack_cnt++] = *ptr++;
			}

		}
		else if(*ptr && (*ptr=='*' || *ptr=='/')){
			if(stack_cnt!=0 && (stack[stack_cnt-1]=='*' || stack[stack_cnt-1]=='/')){
				printf("%c ", stack[--stack_cnt]);
			}

			stack[stack_cnt++] = *ptr++;
		}
		else if(*ptr && *ptr==')'){
			for(int i=stack_cnt; stack[i-1]!='('; i--){
				printf("%c ", stack[--stack_cnt]);
			}
			stack_cnt --;	//扣掉'('
			ptr ++;
		}
		else if(*ptr && *ptr=='(')  
			stack[stack_cnt++] = *ptr++;
	}
	for(int i=stack_cnt; i!=0; i--){
		printf("%c ", stack[i-1]);
	}
	puts("");
}
void RmNewLine(char *input){
	int len = strlen(input);
	if(input[len-1] == '\n')
		input[len-1] = '\0';
}
