#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct List List;

struct List{
	char word[1024];
	List *next;
};

List *insert_node(List *node, char *word);
List *node_initialize(char *word);
void print_re_linkedlist(List *node);
void FreeList(List *node){
	if(!node)
		return;


	FreeList(node->next);

	free(node);

	return;
}


int main(){
	char input[1024];
	List *top = NULL;
		int cnt = 0;

	while(scanf("%s", input) != EOF){
		if(isspace(*input))
			continue;	
		top = insert_node(top, input);
			cnt++;
				printf("cnt:%d\n", cnt);
	}

	//print_re_linkedlist(top->next);

	FreeList(top);

	return 0;
}
List *insert_node(List *node, char *word){
	if(node == NULL){
		node = node_initialize(word);
		return node;
	}
	if(strcmp(node->word, word) == 0)
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
