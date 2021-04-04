#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct term_cnt{
	int cnt;
	char word[65];
	struct term_cnt *next;
};

typedef struct term_cnt Term_cnt;

int word_cnt(Term_cnt *now, char *input);
void initialize_node(Term_cnt *node, char *input);
void output(Term_cnt *list);
void free_all(Term_cnt *list);

int main(){
	char input_word[65];	
	Term_cnt *list = (Term_cnt*)calloc(1, sizeof(Term_cnt)); //The reason why previous edition RE is that I forgot to allocate memory to this pointer......

	scanf("%s", input_word);
	initialize_node(list, input_word);

	while(scanf("%s", input_word) != EOF){
		word_cnt(list, input_word);
	}

	output(list);

	free_all(list);

	return 0;
}
int word_cnt(Term_cnt *now, char *input){
	if(strcmp(now->word, input)==0){
		now->cnt ++;
		return 0;
	}

	if(now->next == NULL){
		now->next = (Term_cnt*)calloc(1, sizeof(Term_cnt));
		initialize_node(now->next, input); 
		return 0;
	}
	else{
		word_cnt(now->next, input);
	}
	
}
inline void initialize_node(Term_cnt *node, char *input){
	node->next = NULL;
	node->cnt = 1;
	strcpy(node->word, input);
}
void output(Term_cnt *now){
	if(now == NULL) return;

	printf("%s %d\n", now->word, now->cnt);
	output(now->next);
}
void free_all(Term_cnt *now){
	if(now == NULL)	return;
	else free_all(now->next);

	free(now);
}
