#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE 4096
#define MAX_NUMBER 1500

int main(){

	char line[MAX_LINE];
	double stack[MAX_NUMBER] = {0};
	int cnt;


	while(fgets(line, 4096, stdin) != NULL){
		cnt = 0;
		while(sscanf(

	}

	return 0;
}
