#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUM	5

typedef struct node Node;

struct node{
	char name[1024];
	int score[6];
	Node *next;
};


int insert(Node *list, Node input);
int output(Node *list);
void add_node(Node *list, Node new_node);
void node_cpy(Node *now, Node input);

int main(){
	
	Node temp_student;	
	Node *new_node;
	Node *list = (Node*)calloc(1, sizeof(Node));
	list->score[SUM] = 0;
	scanf("%s", list->name);
	for(int i=0; i<5; i++){
		scanf("%d", &list->score[i]);	
		list->score[SUM] += list->score[i];
	}
	list->next = NULL;

	while(scanf("%s", temp_student.name) != EOF){

		temp_student.score[SUM] = 0;

		for(int i=0; i<5; i++){
			scanf("%d", &temp_student.score[i]);	
			temp_student.score[SUM] += temp_student.score[i];
		}

		if(temp_student.score[SUM] > list->score[SUM]){
			new_node = (Node*)calloc(1, sizeof(Node));	
			new_node->next = list;
			node_cpy(new_node, temp_student);
			list = new_node;
		}
		else{
			insert(list, temp_student);
		}
	}

	
	output(list);

	return 0;
}
int insert(Node *now, Node input){
	if(now->next == NULL){
		add_node(now, input);	
		return 0;
	}

	if(input.score[SUM] > now->next->score[SUM]){
		add_node(now, input);
		return 0;
	}
	else{
		insert(now->next, input);
		return 0;
	}
}
inline int output(Node *now){
	if(now == NULL){
		return 0;
	}
	
	printf("%s\t", now->name);
	for(int i=0; i<4; i++){
		printf("%d\t", now->score[i]);	
	}
	printf("%d\n", now->score[4]);	

	output(now->next);

	free(now);
	return 0;
}
inline void add_node(Node *list, Node input){
	Node *new_node = (Node*)calloc(1, sizeof(Node));	
	new_node->next = list->next;	
	list->next = new_node;
	node_cpy(new_node, input);
	return;	
}
inline void node_cpy(Node *now, Node input){
	strcpy(now->name, input.name);
	for(int i=0; i<6; i++){
		now->score[i] = input.score[i];
	}
	return;
}
