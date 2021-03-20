#include <stdio.h>
#include <stdlib.h>
	#include <unistd.h>

int str_len(char *input){
	int cnt = 0;
	while(*input++) cnt++;
	return cnt;

}
int str_n_cmp(char *str1, char *str2, int len){
	for(int i=0; i<len; i++){
		if(*str1!='\0' && *str2!='\0' && *str1==*str2){
			str1 ++;
			str2 ++;
		}
		else{
			break;	
		}
	}
		printf("*str1-*str2:%d\n", *str1-*str2);
		usleep(1000000);	
	return (*str1 - *str2);
}
char *my_strstr(char *input, char *pattern){
	int input_len = str_len(input);
	int pattern_len = str_len(pattern);
		printf("input_len:%d\tpattern_len:%d\n", input_len, pattern_len);
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
	char *src_ptr = src;
	char *final_ptr = NULL;
	char target[1024]; 
	int idx = 0;
	int target_len;

	while(fgets(whole, 3073, stdin) != NULL){	
		sscanf(whole, "%[^,],%s", src, target);
		target_len = str_len(target);
				printf("src:%s\ttarget:%s\n", src, target);
		while( (src_ptr=my_strstr(src_ptr, target)) != NULL){
				printf("src_ptr:%p\n", src_ptr);
			final_ptr = src_ptr;
		}
			printf("final_ptr:%p\n", final_ptr);	
		if(final_ptr){
					puts("HI, in if(final_ptr)");
			for(char *i=src; i<final_ptr; i++){
				idx ++;
			}
			printf("%d,%d\n", idx, idx+target_len);
		}
		else{
					puts("HI, in else(final_ptr)");
			puts("-1");
		}
	}
	return 0;
}
