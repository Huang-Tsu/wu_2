#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 64
#define YES 1
#define NO 0

enum{
	POP, PUSH, PRINT
};
int queue[MAX_SIZE];
int head = 0;
int tail = 0;
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
	tail++;
	queue[(tail-1)%MAX_SIZE] = input;	
}
inline int pop(){
	//queue_now ++;
	head ++;
	return queue[(head-1)%MAX_SIZE];
}
inline int is_empty(){
	return (head==tail)? YES : NO;
}
inline int is_full(){
	return ((tail+1)%MAX_SIZE == head%MAX_SIZE)? YES : NO;
}
inline int print(){
	printf("Queue:");
	for(int i=head; i<tail; i++){
		printf(" %d", queue[i%MAX_SIZE]);
	}
	puts("");
}
