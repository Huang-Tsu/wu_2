#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tree_node Tree_node;
typedef struct Tree_queue Tree_queue;


struct Tree_node{
	char word[2049];
	Tree_node *left;
	Tree_node *right;
};

struct Tree_queue{
	Tree_node *node_now;
	Tree_queue *next;
};

Tree_node *add_node(Tree_node *root, char *input);
Tree_node *node_initialize(char *word);
void level_order_traversal(Tree_node *node);
Tree_queue *add_queue(Tree_queue *head, Tree_node *input);

Tree_node *root;

int main(int argc, char **argv){
	char input[2049];


	while(scanf("%s", input) != EOF){
		if(isspace(*input))
			continue;
		root = add_node(root, input);		
	}

	level_order_traversal(root);

	return 0;
}
Tree_node *add_node(Tree_node *node, char *input){
	if(node == NULL){
		node = node_initialize(input);
		return node;
	}

	int return_value = strcmp(input, node->word);
	if(return_value == 0)
		;
	else if(return_value < 0){
		node->left = add_node(node->left, input);
	}
	else{
		node->right = add_node(node->right, input);
	}

	return node;
}
Tree_node *node_initialize(char *word){
	Tree_node *new_node = (Tree_node*)calloc(1, sizeof(Tree_node));
	strcpy(new_node->word, word);
	new_node->left = new_node->right = NULL;
	return new_node;
}


void level_order_traversal(Tree_node *node){
	Tree_queue *queue_now = (Tree_queue*)calloc(1, sizeof(Tree_queue));
	Tree_queue *queue_next = (Tree_queue*)calloc(1, sizeof(Tree_queue));

	queue_now->now = node;

	traversal_start(queue_now, queue_next);
	//level_order_traversal(node->left);
	//level_order_traversal(node->right);

	//free(node);
}
void traversal_start(Tree_queue *queue_now, Tree_queue *queue_next){
	if(queue_now == NULL)
		return;

	printf("%s\n", queue_now->node_now.word);
	add_queue(queue_next, queue_now->node_now.left);	
	add_queue(queue_next, queue_now->node_now.right);	

	traversal_start(queue_now->next, queue_next);

	free(queue_now);
}
Tree_queue *add_queue(Tree_queue *head, Tree_node *input){
	Tree_queue *ptr;
	for(ptr=head; ptr->next!=NULL; ptr=ptr->next)
		;
	
	ptr->next = (Tree_queue*)calloc(1, sizeof(Tree_queue));
	ptr->node_now = input;
}
