#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 4096

char *get_term(char *src, char *term, char *delimiter);
int is_delim(int test, char *delim);

int main(){
	char line[MAX_LINE];
	char *ptr, *qtr, *text_end;
	char term[MAX_LINE];
	char delim[] = " \t,.;[]()@#S";

	while(fgets(line, MAX_LINE, stdin)!=NULL){
		ptr = line;
		while(ptr){
			ptr = get_term(ptr, term, delim);
			printf("%s\n", term);
		}
	}
}
char *get_term(char *src, char *term, char *delim){
	char *ptr, *qtr;
	ptr = src;

	//while(is_dilim(*ptr)) ptr ++;
	while(is_delim(*ptr, delim) && *ptr) ptr++;
	qtr = term;

	//while(!is_dilim(*ptr) && *ptr){
	while(!is_delim(*ptr, delim) && *ptr){
		*qtr ++ = *ptr ++;
	}
	*qtr = '\0';
	if(term[0] == '\0') return NULL;
	else return ptr;
}
int is_delim(int test, char *delim){
	return (strchr(delim, test)!=NULL) ? 1 : 0;
}
