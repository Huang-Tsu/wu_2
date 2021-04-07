#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 4096

int main(){

	char line[MAX_LINE];
	char *ptr, *qtr, *line_end;
	char *last;
	int hex1, hex2;
	unsigned char c;

	while(fgets(line, MAX_LINE, stdin)){
		ptr = line;
		last = line;
		line_end = line + strlen(line);
		while(ptr){
			ptr = strchr(ptr, '%');
			qtr = last;
			if(ptr == NULL){
				while(qtr < line_end){
					putchar(*qtr);
					qtr++;
				}
				break;
			}
			else{
				while(qtr < ptr){
					putchar(*qtr);
					qtr++;
				}
				ptr ++;
				if(isdigit(*ptr)){
					hex1 = *ptr - '0';
				}
				else{
					hex1 = *ptr - 'A' + 10;
				}
				ptr ++;
				if(isdigit(*ptr)){
					hex2 = *ptr - '0';
				}
				else{
					hex2 = *ptr - 'A' + 10;
				}
				c = (hex1<<4) + hex2;
				putchar(c);
				ptr++;
				last = ptr;
				
			}
		}
	}
}
