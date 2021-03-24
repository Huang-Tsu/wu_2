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
		ptr = whole;
		ptr = get_tok(ptr, token, delim);
		printf("%s", token);
		while( (ptr=get_tok(ptr, token, delim))!=NULL){
			printf(",%s", token);
		}
		printf(",%s", token);
		puts("");
	}
}
char *get_tok(char *src, char *token, char *delim){
	char *ptr = src;
	char *qtr = token;
	int delim_len = strlen(delim);
	int process_len = strlen(src)-delim_len;	

	for(int i=0; i<=process_len; i++){
		if(strncmp(ptr, delim, delim_len)!=0){
			*qtr++ = *ptr++;	
		}
		else{
			*qtr = '\0';
			return ptr+delim_len-1;
		}
	}
	*qtr = '\0';
	return NULL;
}
