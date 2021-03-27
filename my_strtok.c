#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_tok(char *src, char *token, char *delimiter);

int main(){
	char whole[1025];
	char delim[1025];
	char token[1025];
	char *ptr;

	while(scanf("%s%s", whole, delim) != EOF){
		if(strcmp(whole, delim)==0){
			printf("empty string\n");
			continue;
		}

		ptr = whole;
		ptr = get_tok(ptr, token, delim);
		printf("%s", token);

		while(ptr){
			ptr=get_tok(ptr, token, delim);
			if(strlen(token)!=0){
				printf(",%s", token);
			}
		}
		puts("");
	}
}

char *get_tok(char *src, char *token, char *delim){
	char *ptr = src;
	char *qtr = token;
	char *target;
	int delim_len = strlen(delim);
	int src_len = strlen(src);	
	char *end = src+src_len;

	while(ptr+delim_len<=end && strncmp(ptr, delim, delim_len)==0) ptr+=delim_len;
	
	if(target = strstr(ptr, delim)){
		for(ptr; ptr<target; ){
			*qtr++ = *ptr++;
		}
		*qtr = '\0';
		return ptr;
	}
	else{
		for(ptr; ptr<end;){
			*qtr++ = *ptr++;	
		}
		*qtr = '\0';
		return NULL;
	}
}
