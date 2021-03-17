#include <stdio.h>
#include <stdlib.h>

int str_len(char *input){
	int cnt = 0;
	while(*input++) cnt++;
	return cnt;

}
char *my_strstr(char *input, char *pattern){
	int input_len = str_len(input);
	int pattern_len = str_len(pattern);
	for(int i=0; i<input-pattern_len; i++){
		for(int j=0; j<pattern_len; j++){
			if(input[i+j] != pattern[j]){
				break;
			}
			if(j == pattern_len-1){
				return input+i;
			}
		}
	}
	return NULL;
}
int main(){

	char src[2049];
	char whole[3073];
	char target[1024]; 

	while(fgets(whole, 3073, stdin) != NULL){	
		sscanf(whole, "%[^,],%s", src, target);
		printf("src:%s, target:%s\n", src, target);
	}
}
