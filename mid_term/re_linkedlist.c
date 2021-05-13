#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

struct List{
	char word[1024];
	List *next;
};

List *insert_node(List *node, char *word);
List *node_initialize(char *word);
void print_re_linkedlist(List *node);


int main(){
	char input[1024];
	List *top = NULL;

	while(scanf("%s", input) != EOF){
		top = insert_node(top, input);
	}

	print_re_linkedlist(top);
	return 0;
}
List *insert_node(List *node, char *word){
	if(node == NULL){
		node = node_initialize(word);
	}
	else if(strcmp(node->word, word) == 0)
		;
	else{
		node->next = insert_node(node->next, word);
	}
	
	return node;
}
List *node_initialize(char *word){
	List *new_node = (List*)calloc(1, sizeof(List));
	strcpy(new_node->word, word);
	new_node->next = NULL;
	return new_node;
}
void print_re_linkedlist(List *node){
	if(node == NULL){
		return;
	}

	print_re_linkedlist(node->next);
	printf("%s\n", node->word);

	free(node);
}
