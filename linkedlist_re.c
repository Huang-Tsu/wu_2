#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node{
	char word[65];
	Node *next;
}*list = NULL;

Node *add_node(char *input);
void print_node(Node *now);
//void rm_new_line(char *input);

int main(){
	char input[65];
	
	while(scanf("%s", input) != EOF){
		//rm_new_line(input);
		list = add_node(input);
	}

	print_node(list);

	return 0;
}
inline Node *add_node(char *input){
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->next = list;
	strcpy(new_node->word, input);
	return new_node;
}
void print_node(Node *now){
	if(now == NULL) return;	

	printf("%s\n", now->word);

	print_node(now->next);

	printf("%s\n", now->word);
	free(now);
}
/*inline void rm_new_line(char *input){
	char *ptr;
	if(ptr = strchr(input, '\n')){
		*ptr = '\0';
	}
}
*/
