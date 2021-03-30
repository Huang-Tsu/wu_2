#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE 4096

struct node{
		double number;
		struct node *next;
};
typedef struct node Node;

char *getword(char *input_str, char *word);
double pop(Node **node);
Node *add_node();
Node *creat_top_node(double input);
Node *push(Node *top, double input);
double operate(double num1, double num2, char *str);

int main(){

	char line[MAX_LINE];
	char temp_str[MAX_LINE];
	char *ptr;
	char **end_ptr;		//strtod需要的參數
	double pop1, pop2, result; 
	double input_number;
	Node *top;


	while(fgets(line, 4096, stdin) != NULL){

		ptr = line;
		ptr = getword(ptr, temp_str);	
		input_number = strtod(temp_str, end_ptr);
		top = creat_top_node(input_number);

		while((ptr=getword(ptr, temp_str)) != NULL){
				if(isdigit(temp_str[0])){
						input_number = strtod(temp_str, end_ptr);
						top = push(top, input_number);
				}
				else{
					pop1 = pop(&top);
					pop2 = pop(&top);

					result = operate(pop1, pop2, temp_str);
					top = push(top, result);
				}

		}
		result = top->number;
		free(top);
		printf("%.2f\n", result);
	}

	return 0;
}
char *getword(char *ptr, char *word){
	
		char *qtr = word;

		while(*ptr && isspace(*ptr)) ptr++;

		while(*ptr && !isspace(*ptr)){
				*qtr++ = *ptr++;
		}
		
		*qtr = '\0';

		if(word == qtr) return NULL;
		else return ptr;
}
double pop(Node **top){
	Node *old_node = *top;
	double result = (*top)->number;
	*top = (*top)->next;
	free(old_node);
	return result;
}
Node *add_node(){
	return (Node*)calloc(1, sizeof(Node));
}
Node *push(Node *top, double input){
	Node *new_node = add_node();
	new_node->next = top;
	new_node->number = input;
	return new_node;
}
double operate(double num1, double num2, char *str){
	switch(*str){
		case '+':
			return num2+num1;	
			break;
		case '-':
			return num2-num1;	
			break;
		case '*':
			return num2*num1;	
			break;
		case '/':
			return num2/num1;	
			break;
	}
}
Node *creat_top_node(double input){
	Node *new_node = add_node();
	new_node->number = input;
	new_node->next = NULL;
	return new_node;
}
