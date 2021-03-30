#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(){
	double stack[1501];
	char str[4096];
	char *ptr;
	int endofstack;
	double a,b;

	while(fgets(str,4096,stdin)){
		endofstack=0;
		ptr=strtok(str," ");
		while(ptr){
			if(isdigit(*ptr)){
				sscanf(ptr,"%lf",&stack[endofstack++]);
				//stack[endofstack++]=atoi(ptr);
				//printf("input= %f\n",stack[endofstack-1]);
			}
			else{
				a=stack[endofstack-2];
				b=stack[endofstack-1];
				switch(*ptr){
					case '+':
						stack[endofstack-2]=a+b;
						break;
					case '-':
						stack[endofstack-2]=a-b;
						break;
					case '*':
						stack[endofstack-2]=a*b;
						break;
					case '/':
						stack[endofstack-2]=a/b;
						break;
				}
				endofstack-=1;
			}
			ptr=strtok(NULL," ");
		}
		//printf("stack result=\n");
		printf("%.2f",stack[0]);

		printf("\n");
	}
}
