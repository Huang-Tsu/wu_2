#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct term_cnt{
	int cnt;
	char word[1025];
	struct term_cnt *next;
};

typedef struct term_cnt Term_cnt;

int word_cnt(Term_cnt *now, char *input);
int word_cnt_diff(Term_cnt *now, char *input);
void initialize_node(Term_cnt *node, char *input);
void output(Term_cnt *list);
void free_all(Term_cnt *list);
void rm_new_line(char *input_str);

int main(){
	char input_word[1025];	
	char *ptr;
	Term_cnt *list = (Term_cnt*)calloc(1, sizeof(Term_cnt)); 

	fgets(input_word, 1025, stdin);
	rm_new_line(input_word);
	ptr = input_word;
	initialize_node(list, ptr);

	while(fgets(input_word, 1025, stdin)!=NULL && !isspace(input_word[0])){
		rm_new_line(input_word);
		
		ptr = input_word;
		if(ptr[0]=='-'){
			ptr ++;
			word_cnt_diff(list, ptr);
		}
		else{
			word_cnt(list, ptr);
		}
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

	printf("%s: %d\n", now->word, now->cnt);
	output(now->next);
}
void free_all(Term_cnt *now){
	if(now == NULL)	return;
	else free_all(now->next);

	free(now);
}
int word_cnt_diff(Term_cnt *now, char *input){
	if(strcmp(now->word, input)==0){
		now->cnt --;
		return 0;
	}

	if(now->next == NULL){
		now->next = (Term_cnt*)calloc(1, sizeof(Term_cnt));	
		initialize_node(now->next, input);
		now->next->cnt = -1;
		return 0;
	}
	else{
		word_cnt_diff(now->next, input);
	}
}
void rm_new_line(char *input_str){
	if(input_str[strlen(input_str)-1] == '\n'){
		input_str[strlen(input_str)-1] = '\0';
	}
}
