#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getword2(char *input, char *output);

int main(){
	char input_line[2049];
	char word[2049];
	char *ptr;

	while(fgets(input_line, 2049, stdin)){
		ptr = input_line;

		while( (ptr=getword2(ptr, word)) ){
			printf("%s\n", word);
		}
	}

	return 0;
}
char *getword2(char *input, char *word){
	unsigned char *ptr = (unsigned char*)input;
	unsigned char *qtr = (unsigned char*)word;
	int i;

	while(*ptr && isspace(*ptr)) 
		ptr ++;

	if(*ptr && !isspace(*ptr)){ 
		if(*ptr >= 240){
			for(i=0; i<4; i++){
				*qtr++ = *ptr++;
			}
		}
		else if(*ptr >= 224){	//Chinese
			for(i=0; i<3; i++){
				*qtr++ = *ptr++;
			}
		}else if(*ptr >= 192){	//Chinese
			for(i=0; i<2; i++){
				*qtr++ = *ptr++;
			}
		}else{				//English
			while(*ptr && !isspace(*ptr)){
				*qtr++ = *ptr++;
			}
		}

		*qtr = '\0';
	}

	if(qtr == (unsigned char*)word)
		return NULL;

	return (char*)ptr;
	
}
