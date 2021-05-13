#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getword(char *ptr, char *word);

char delim[] = ", .";

int main(){
	char input[1001];
	char word[1001];
	char longest[1001];
	int longest_len;
	char *ptr;

	while(fgets(input, 1001, stdin) != NULL){
		ptr = input;
		longest_len = 0;

		while((ptr = getword(ptr, word)) != NULL){
			if(strlen(word) > longest_len){
				strcpy(longest, word);
				longest_len = strlen(longest);
			}
		}
		printf("%s\n", longest);

	}

	return 0;
	
}
char *getword(char *ptr, char *word){
	char *qtr = word;

	while(*ptr && strchr(delim, *ptr) && isspace(*ptr)) 
		ptr++;

	while(*ptr && !strchr(delim, *ptr) && !isspace(*ptr)){
		*qtr ++ = *ptr ++;
	}
	*qtr = '\0';

	if(word == qtr) return NULL;
	else return ptr;
}
