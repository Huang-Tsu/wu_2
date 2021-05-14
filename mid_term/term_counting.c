#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct List List;

struct List{
	char word[1024];
	int cnt;
	List *next;
};

List *insert_node(List *node, char *word);
List *node_initialize(char *word);
void print_term_count(List *node, int node_cnt);
void find_largest(List *node);
void free_linked_list(List *node);
void rm_new_line(char *input);

List *largest;
int node_cnt = 0;

int main(){
	char input[301];
	List *top = NULL;

	while(scanf("%s", input) != EOF){
		if(*input == 'a' || *input == 'A'){	
			top = insert_node(top, input);
		}
	}

	print_term_count(top, node_cnt);

	free_linked_list(top);

	return 0;
}
List *insert_node(List *node, char *word){
	if(node == NULL){
		node = node_initialize(word);
		node_cnt ++;
		return node;
	}
	if(strcmp(node->word, word) == 0){
		node->cnt ++;
	}
	else{
		node->next = insert_node(node->next, word);
	}
	
	return node;
}
List *node_initialize(char *word){
	List *new_node = (List*)calloc(1, sizeof(List));
	strcpy(new_node->word, word);
	new_node->next = NULL;
	new_node->cnt = 1;
	return new_node;
}
void print_term_count(List *top, int node_cnt){
	for(int i=0; i<node_cnt; i++){
		largest = top;
		find_largest(top);
		printf("%s %d\n", largest->word, largest->cnt);
		largest->cnt = -1;
	}
}
void find_largest(List *node){
	List *ptr;
	for(ptr=node; ptr!=NULL; ptr=ptr->next){
		if(ptr->cnt > largest->cnt)
			largest = ptr;
		else if(ptr->cnt == largest->cnt){
			if(strcmp(ptr->word, largest->word) < 0)
				largest = ptr;
		}
	}
/*
	if(node == NULL)
		return;

	if(node->cnt > largest->cnt)
		largest = node;
	else if(node->cnt == largest->cnt){
		if(strcmp(node->word, largest->word) < 0)
			largest = node;
	}

	find_largest(node->next);
*/
}
void free_linked_list(List *node){
	if(node == NULL){
		return;
	}

	free_linked_list(node->next);
	free(node);
}
void rm_new_line(char *input){
	int end = strlen(input);
	if(input[end-1] == '\n'){
		input[end-1] = '\0';
	}
}
