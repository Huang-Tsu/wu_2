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
		if(ptr == NULL){
			puts("");
			continue;
		}
		else{
			while( (ptr=get_tok(ptr, token, delim))!=NULL){
				printf(",%s", token);
			}
			puts("");
		}
	}
}
char *get_tok(char *src, char *token, char *delim){
	char *ptr = src;
	char *qtr = token;
	int delim_len = strlen(delim);
	int src_len = strlen(src);	
	char *end = src +src_len;

	while(ptr<end && strncmp(ptr, delim, delim_len)==0) ptr+=delim_len;
	
	while(ptr<end && strncmp(ptr, delim, delim_len)!=0){
		*qtr++ = *ptr++;
	}
	if(end-ptr<src_len && end-ptr!=0){
		while(ptr<end){
			*qtr++ = *ptr;	
		}
		return NULL;
	}
	else{
		return ptr;
	}
	/*
	for(int i=0; i<=src_len-delim_len+1; i++){
		if(strncmp(ptr, delim, delim_len)!=0){
			*qtr++ = *ptr++;	
		}
		else{
			ptr += delim_len;
			while(src+src_len-ptr>=delim_len && strncmp(ptr, delim, delim_len)==0){
				ptr += delim_len;
			}
			*qtr = '\0';
			return ptr;
		}
	}
	*/
}
