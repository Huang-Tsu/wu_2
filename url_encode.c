#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	
	int input;
	int output;
	input = getchar();
	while(input!=EOF){
		if((input>='A'&&input<='Z') || (input>='a'&&input<='z') || (input>='0'&&input<='9') || input == '.' || input=='\n'){
			putchar(input);
			input = getchar();
			continue;
		}
		else{
			putchar('%');
			output = input/16;
			if(output>=10){
				output = 'A'+output-10;
				printf("%c", output);
			}
			else{
				printf("%d", output);
			}
			output = input%16;
			if(output>=10){
				output = 'A'+output-10;
				printf("%c", output);
			}
			else{
				printf("%d", output);
			}
			
			input = getchar();
		}
		
	}
	return 0;
}

