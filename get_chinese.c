#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *GetChinese(char *input, char *output);

int main(){
	char input_line[4096];	
	char output[5];
	unsigned char *ptr;

	while(fgets(input_line, 4096, stdin)){
		ptr = input_line;
		while( (ptr = GetChinese(ptr, output) ) != NULL ){
			printf("%s\n", output);
		}
	}
}

char *GetChinese(char *input, char *output){
	if(*input == '\0')
		return NULL;
	static unsigned char *qtr, *ptr;
	ptr = input;
	qtr = output;

	if(*ptr >= 224){
		*qtr++ = *ptr++;
		*qtr++ = *ptr++;
		*qtr++ = *ptr++;
	}
	else if(*ptr > 194){
		*qtr++ = *ptr++;
		*qtr++ = *ptr++;
	}
	else if(*ptr > 128){
		ptr ++;
	}
	else{
		*qtr++ = *ptr++;
	}

	*qtr = '\0';

	return ptr;
}

