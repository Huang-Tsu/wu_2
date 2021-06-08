#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *GetwordInDoubleQuotes(char *input, char *output);

int main(){
	char input_line[2049];
	char word[2049];
	char *ptr;

	while(fgets(input_line, 2049, stdin)){
		ptr = input_line;

		while( (ptr=GetwordInDoubleQuotes(ptr, word)) ){
			printf("%s\n", word);
		}
	}

	return 0;
}
char *GetwordInDoubleQuotes(char *input, char *word){
	char *ptr = strchr(input, '"');
	char *qtr = word;

	if(ptr){	//這行有雙引號(strchr()有找到東西)
		ptr ++;	//skip "
		while(*ptr && *ptr != '"')
			*qtr++ = *ptr++;

		ptr ++;		//skip "
		*qtr = '\0';
	}else
		return NULL;

	return ptr;
}
