#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YES	1
#define NO	0

void rm_new_line(char *input);
int is_palid(char *input);

int main(){
	char input[1025];

	while(fgets(input, 1025, stdin) != NULL){
		rm_new_line(input);

		if(is_palid(input))
			printf("%s\n", input);
	}

	return 0;
}
void rm_new_line(char *input){
	int end = strlen(input);
	if(input[end-1] == '\n'){
		input[end-1] = '\0';
	}
}
int is_palid(char *input){
	int len = strlen(input);
	for(int i=0, j=len-1; i<=j; i++, j--){
		if(input[i] != input[j]){
			return NO;
		}
	}
	return YES;
}
