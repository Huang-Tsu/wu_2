#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void rm_new_line(char *input);
double calucate(double input1, double input2, char *operator);

int main(){
	double stack[1500];
	double pop1, pop2;
	char input_str[4097];
	char *ptr;
	int stack_cnt;

	while(fgets(input_str, 4097, stdin) != NULL){
		rm_new_line(input_str);
		stack_cnt = 0;
		ptr = input_str;	
		ptr = strtok(ptr," ");
		stack[stack_cnt++] = strtod(ptr, NULL);

		while( (ptr = strtok(NULL, " ")) != NULL){
			if(isdigit(*ptr)){
				stack[stack_cnt++] = strtod(ptr, NULL);
			}
			else{
				pop1 = stack[--stack_cnt];
				pop2 = stack[--stack_cnt];
				stack[stack_cnt++] = calucate(pop1, pop2, ptr);
			}
		}

		printf("%.2f\n", stack[stack_cnt-1]);
	}

	return 0;
}
void rm_new_line(char *input){
	int end = strlen(input);
	if(input[end-1] == '\n'){
		input[end-1] = '\0';
	}
}
double calucate(double input1, double input2, char *operator){
	switch(*operator){
		case '+':
			return input1 + input2;
		case '-':
			return input2 - input1;
		case '*':
			return input1 * input2;
		case '/':
			return input2 / input1;
	}
}
