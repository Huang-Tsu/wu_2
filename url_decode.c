#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 4096
#define OK 1
#define NO 0

int main(){
	char line[MAX_LINE];
	char output[MAX_LINE];
	char *output_ptr;
	char *target, *now;
	char *line_end;
	int hex1, hex2;
	int state;
	char answer;

	while(fgets(line, MAX_LINE, stdin) != NULL){
		now = line;
		output_ptr = output;
		line_end = strchr(line, '\0');
		state = OK;

		while((target=strchr(now, '%')) != NULL){
			if(state == NO) break;

			while(now<target){
				*output_ptr++ = *now++;
			}
			now ++;

			if(isdigit(*now)){
				hex1 = *now-'0';
				now++;
			}
			else if(*now<='F' && *now>='A'){
				hex1 = *now-'A'+10;
				now++;
			}
			else{
				puts("error format");
				state = NO;
				break;
			}

			
			if(isdigit(*now)){
				hex2 = *now-'0';
				now++;
			}
			else if(*now<='F' && *now>='A'){
				hex2 = *now-'A'+10;
				now++;
			}
			else{
				puts("error format");
				state = NO;
				break;
			}
			
			answer = (hex1<<4) + hex2;
			*output_ptr++ = answer;
		}
		if(state == OK){
			while(now<=line_end){
				*output_ptr++ = *now++;
			}
			printf("%s", output);
		}
	}
}
