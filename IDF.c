#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct List List;

struct List{
	char *word;
	int visited;
	int cnt;
	List *next;
};

void InsertNode(List **node, char *word);
void BackToZero(List *node);
List *InitializeNode(char *word);
void FreeList(List *node);
void PrintResult(List *node);
char *getword(char *input, char *output);

int main(){
	List *head = NULL;
	char input[100001];
	char word[100001];
	char *ptr;
	
	while(fgets(input, 100001 ,stdin)){
		BackToZero(head);
		ptr = input;

		while((ptr = getword(ptr, word)) != NULL){
			InsertNode(&head, word);
		}
	}

	PrintResult(head);

	FreeList(head);

	return 0;
}
void InsertNode(List **node, char *word){
	if(!*node)
		*node = InitializeNode(word);

	int return_value = strcmp(word, (*node)->word);
	if(return_value == 0){
		if((*node)->visited == 0){
			(*node)->cnt ++;
			(*node)->visited = 1;
		}

		return;
	}
	
	if(return_value < 0){
		List *new_node = InitializeNode(word);
		new_node->next = (*node);
		*node = new_node;

		return;
	}

	InsertNode(&(*node)->next, word);
}
void BackToZero(List *node){
	if(!node)
		return;

	node->visited = 0;
	BackToZero(node->next);
}
List *InitializeNode(char *word){
	List *new_node = (List*)calloc(1, sizeof(List));

	new_node->word = strdup(word);
	new_node->cnt = 1;
	new_node->visited = 1;
	new_node->next = NULL;
	
	return new_node;
}
void FreeList(List *node){
	if(!node)
		return;

	List *next = node->next;

	free(node->word);
	free(node);

	FreeList(next);

}
void PrintResult(List *node){
	int largest_cnt;
	List *largest_node;
	List *ptr;
	for(int i=0; i<10; i++){
		largest_node = node;
		largest_cnt = node->cnt;
		ptr = node->next;
		for(ptr; ptr; ptr=ptr->next){
			if(ptr->cnt > largest_cnt){
				largest_node = ptr;
				largest_cnt = ptr->cnt;
			}
		}

		printf("%s\n", largest_node->word);
		largest_node->cnt = -1;
		
	}
}
char *getword(char *ptr, char *word){
	char *qtr = word;

	while(*ptr && isspace(*ptr))
			ptr ++;

	while(*ptr && !isspace(*ptr))
		*qtr++ = *ptr++;

	*qtr = '\0';

	if(qtr == word)
		return NULL;
	
	return ptr;
}
