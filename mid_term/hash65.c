#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

unsigned int my_pow(int input, int times);
unsigned int hash65(char *input);
void only_char(char *input, char *output);
int main(){
	unsigned int answer;
	char input[6];
	char output[6];
	
	while(scanf("%s", input) != EOF){
		only_char(input, output);
		answer = hash65(output);
		printf("%u\n", answer);
	}

	return 0;
}
unsigned int hash65(char *input){
	unsigned int sum = 0;
	int len = strlen(input);

	for(int i=0; i<len; i++){
		sum += input[i] * my_pow(65, len-1-i);
	}

	return sum;
}
unsigned int my_pow(int input, int times){
	if(times == 0){
		return 1;
	}
	unsigned int result = 1;

	for(int i=1; i<=times; i++){
		result *= input;
	}
	return result;
}
void only_char(char *input, char *output){
	while(*input != '\0'){
		if(isalpha(*input)){
			*output++ = *input;	
		}
		input ++;
	}
	
	*output = '\0';
}
