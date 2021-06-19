#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_LINE 3073

void ToPostfix(char *line);
void RmNewLine(char *input);

char output[2*MAX_LINE];

int main(){
	char line_input[MAX_LINE];

	while(fgets(line_input, MAX_LINE, stdin)){
		RmNewLine(line_input);
		ToPostfix(line_input);

		printf("%s\n", output);
	}

	return 0;
}
void ToPostfix(char *ptr){
	char stack[MAX_LINE];
	int stack_cnt = 0;
	char *qtr = output;

	while(*ptr){
		if(isalnum(*ptr)){
			while(*ptr && (isalnum(*ptr) || *ptr=='.')){
				//printf("%c", *ptr++);
				*qtr++ = *ptr++;
			}
			//printf(" ");
			*qtr++ = ' ';
		}

		else if(*ptr && (*ptr=='+' || *ptr=='-')){
			if(stack_cnt==0 || stack[stack_cnt-1]=='(')		//是stack的第一個 or 前一個是左括
				;
			else{
				for(int i=stack_cnt; i!=0&&stack[i-1]!='('; i--){	
					//printf("%c ", stack[--stack_cnt]);
					*qtr++ = stack[--stack_cnt];
					*qtr++ = ' ';
				}
			}

			stack[stack_cnt++] = *ptr++;

		}
		else if(*ptr && (*ptr=='*' || *ptr=='/')){
			if(stack_cnt==0 || stack[stack_cnt-1]=='+' || stack[stack_cnt-1]=='-' || stack[stack_cnt-1]=='(')
				;
			else{
				for(int i=stack_cnt; i!=0&&stack[i-1]!='+'&&stack[i-1]!='-'&&stack[i-1]!='('; i--){	
					//printf("%c ", stack[--stack_cnt]);
					*qtr++ = stack[--stack_cnt];
					*qtr++ = ' ';
				}
			}

			stack[stack_cnt++] = *ptr++;
		}
		else if(*ptr && *ptr==')'){
			for(int i=stack_cnt; stack[i-1]!='('; i--){
				//printf("%c ", stack[--stack_cnt]);
				*qtr++ = stack[--stack_cnt];
				*qtr++ = ' ';
			}
			stack_cnt --;	//扣掉'('
			ptr ++;
		}
		else if(*ptr && *ptr=='(')  
			stack[stack_cnt++] = *ptr++;
	}
	for(int i=stack_cnt; i!=0; i--){
		//printf("%c ", stack[i-1]);
		*qtr++ = stack[--stack_cnt];
		*qtr++ = ' ';
	}

	if(*(qtr-1) == ' ')
		*(qtr-1) = '\0';
	*qtr = '\0';
}
void RmNewLine(char *input){
	int len = strlen(input);
	if(input[len-1] == '\n')
		input[len-1] = '\0';
}
