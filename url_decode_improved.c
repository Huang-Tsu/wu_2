#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YES 1
#define NO 0


int main(){
	char input[4096];
	char delim[] = "0123456789ABCDEF";
	char output[4096];
	char *output_ptr;
	char *input_end;
	char answer;
	char *now, *target;
	int hex1, hex2;
	int state;

	while(fgets(input, 1024, stdin) != NULL){
		now = input;
		output_ptr = output;
		input_end = strchr(input, '\0');
		state = YES;

		while((target=strchr(now, '%')) != NULL){
			if(strchr(delim, *(target+1)) && strchr(delim, *(target+2))){

				strncpy(output_ptr, now, target-now);
				output_ptr += target-now;	//這裡超重要! 複製完的下一個字元是+target-now 不是+target-now+1 (ex.target-now是複製的個數，若複製一個，則下一個帶輸入字元是+1)
				now = target+3;

				hex1 = strchr(delim, *(target+1)) - delim;
				hex2 = strchr(delim, *(target+2)) - delim;
				answer = hex1*16 + hex2;
				*output_ptr++ = answer;
					
			}
			else{
				puts("error format");
				state = NO;
				break;
			}
		}
		if(state == YES){
			strncpy(output_ptr, now, input_end-now+1);
			printf("%s", output);
		}
	}
	return 0;
}

