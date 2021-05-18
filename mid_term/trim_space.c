#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *getword(char *ptr, char *word);

int main(){
	char input[1025];
	char word[1025];
	char *ptr;

	while(fgets(input, 1025, stdin) != NULL){
		ptr = input;
		ptr = getword(ptr, word);
		printf("%s", word);

		while( (ptr=getword(ptr, word)) != NULL){
			printf(" %s", word);
		}
		puts("");
	}

	return 0;
}
char *getword(char *ptr, char *word){
	static char *qtr;
	qtr = word;

	while(*ptr && isspace(*ptr)) 
		ptr++;

	while(*ptr && !isspace(*ptr))
		*qtr++ = *ptr++;

	*qtr = '\0';

	if(qtr == word) return NULL;
	else return ptr;
}
