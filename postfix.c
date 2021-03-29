#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE 4096
#define MAX_NUMBER 1500
struct node{
		double number;
		struct node *next;
};
typedef struct node Node;

char *getword(char *input_str, char *word);
double pop(Node *node);

int main(){

	char line[MAX_LINE];
	char temp_str[MAX_LINE];
	char *ptr;
	char **end_ptr;		//strtod需要的參數
	double pop1, pop2, result; 
	double input_number;


	while(fgets(line, 4096, stdin) != NULL){

		ptr = getword(ptr, temp_str);	
		input_number = strtod(temp_str, end_ptr);
		Node top;
		top.number = input_number;
		top.next = NULL;

		while(ptr=getword(ptr, temp_str) != NULL){
				if(isdigit(temp_str[0])){
						input_number = strtod(temp_str, end_ptr);
						push(top, input_number);
				}
				else{
					pop1 = pop(top);
					pop2 = pop(top);
					result = operate(pop1, pop2, temp_str);
					push(top, result);
				}

		}
		result = pop(top);
		printf("%.2lf\n", result);
	}

	return 0;
}
char *getword(char *input_str, char *word){
		char *ptr, *qtr;
		ptr = input_str;

		while(*ptr && isspace(ptr)) ptr++;

		while(*ptr && !isspace(ptr)){
				*qtr++ = *ptr++;
		}

		if(word == qtr) return NULL;
		else return ptr;
}
double pop(Node node){
		if(node.next == NULL){
				return
		}
}
