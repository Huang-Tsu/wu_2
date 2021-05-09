#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b){
	return strcmp(*(char**)a, *(char**)b);
}
void rm_new_line(char *input){
	if(input[strlen(input)-1] == '\n') 
		input[strlen(input)-1] = '\0';
}

int main(){
	char *strings[32];
	char temp[1024];
	int cnt = 0;
	
	while(fgets(temp, 1024, stdin) != NULL){
		rm_new_line(temp);
		strings[cnt] = (char*)calloc(strlen(temp)+1, sizeof(char));
		strcpy(strings[cnt++], temp);
	}

	qsort(strings, cnt, sizeof(char*), compare);

	for(int i=0; i<cnt ;i++){
		printf("%s\n", strings[i]);
		free(strings[i]);
	}
}
