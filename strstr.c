#include <stdio.h>
#include <stdlib.h>

int str_len(char *input){
	int cnt = 0;
	while(*input++) cnt++;
	return cnt;
}
int str_n_cmp(char *str1, char *str2, int len){
	for(int i=0; i<len-1; i++){
		if(*str1!='\0' && *str2!='\0' && *str1==*str2){
			str1 ++;
			str2 ++;
		}
		else{
			break;	
		}
	}
	return (*str1 - *str2);
}
char *my_strstr(char *input, char *pattern){
	int input_len = str_len(input);
	int pattern_len = str_len(pattern);
	for(int i=0; i<=input_len-pattern_len; i++){
		if(str_n_cmp(input+i, pattern, pattern_len)==0){
			return input+i;
		}
	}
	return NULL;
}
int main(){

	char whole[3073];
	char src[2049];
	char *src_ptr;
	char *final_ptr;
	char target[1024]; 
	int idx = 0;
	int target_len;

	while(fgets(whole, 3073, stdin) != NULL){	

		sscanf(whole, "%[^,],%[^\n]", src, target);

		src_ptr = src;
		final_ptr = NULL;
		target_len = str_len(target);
		while( (src_ptr=my_strstr(src_ptr, target)) != NULL){
			final_ptr = src_ptr;
			src_ptr ++;
		}
		if(final_ptr){
			idx = final_ptr-src;
			printf("%d,%d\n", idx, idx+target_len-1);
		}
		else{
			puts("-1");
		}
	}
	return 0;
}
