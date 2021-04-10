#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 63
#define YES 1
#define NO 0

enum{
	POP, PUSH, PRINT
};
int stack[MAX_SIZE];
int stack_now = 0;
int command_interpret(char *command);

int push(int input);
int pop();
int is_empty();
int is_full();
int print();

int main(){
	char command[10];
	int number;

	while(scanf("%s", command) != EOF){
		switch(command_interpret(command)){
			case POP:
				if(is_empty()){
					puts("Is empty!");
				}
				else{
					number = pop();
					printf("Pop %d\n", number); 
				}
				break;

			case PUSH:
				scanf("%d", &number);
				if(is_full()){
					puts("Is full!");
				}
				else{
					push(number);
				}
				break;

			case PRINT:
				print();
				break;
		}
	}
}
inline int command_interpret(char *command){
	if(strcmp(command, "pop")==0) return POP;
	if(strcmp(command, "push")==0) return PUSH;
	if(strcmp(command, "print")==0) return PRINT;
}
inline int push(int input){
	stack[stack_now++] = input;	
}
inline int pop(){
	stack_now --;
	return stack[stack_now];
}
inline int is_empty(){
	if(stack_now == 0)return YES;
	else return NO;
}
inline int is_full(){
	if(stack_now > MAX_SIZE) return YES;
	else return NO;
}
inline int print(){
	printf("Stack:");
	for(int i=0; i<stack_now; i++){
		printf(" %d", stack[i]);
	}
	puts("");
}
