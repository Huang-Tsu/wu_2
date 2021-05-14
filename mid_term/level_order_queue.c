#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tree_node Tree_node;
typedef struct Queue Queue;


struct Tree_node{
	char word[2049];
	Tree_node *left;
	Tree_node *right;
};

struct Queue{
	Tree_node *tree_node;
	Queue *next;
};

	//for test
	void tree_traversal(Tree_node *node);
void rm_new_line(char *input);
void free_tree(Tree_node *node);
Tree_node *add_node(Tree_node *root, char *input);
Tree_node *node_initialize(char *word);
void level_order_traversal(Tree_node *node);

Queue *en_queue(Queue *head, Tree_node *input);
Queue *queue_initialize(Tree_node *input);
Queue *de_queue(Queue *front);

	Tree_node *root;

int main(int argc, char **argv){
	char input[2049];


	while(fgets(input, 2049, stdin) != NULL){
		rm_new_line(input);
		if(isspace(*input))
			continue;
		root = add_node(root, input);
	}

	//tree_traversal(root);
	level_order_traversal(root);

	free_tree(root);

	return 0;
}

	//function for Binary Search Tree
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
	Queue *front, *rear;
	Tree_node *ptr;

	front = rear = queue_initialize(node);

	while(front){
		ptr = front->tree_node;

		if(ptr->left)
			rear = en_queue(rear, ptr->left);
		if(ptr->right)
			rear = en_queue(rear, ptr->right);

		printf("%s\n", front->tree_node->word);

		front = de_queue(front);
	}
}
void free_tree(Tree_node *node){
	if(!node)
		return;

	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

	//function for Queue
Queue *en_queue(Queue *rear, Tree_node *input){
	rear->next = queue_initialize(input);
	return rear->next;
}
Queue *de_queue(Queue *front){
	Queue *new_front = front->next;

	free(front);

	return new_front;

}
Queue *queue_initialize(Tree_node *input){
	Queue *new_node = (Queue*)calloc(1, sizeof(Queue));
	if(!new_node){
		puts("calloc failed!");
		exit(1);
	}
	new_node->tree_node = input;
	new_node->next = NULL;
	return new_node;

}



void rm_new_line(char *input){
	int end_idx = strlen(input);

	if(input[end_idx-1] == '\n')
		input[end_idx-1] = '\0';

	return;
}


	//for test
void tree_traversal(Tree_node *node){
	if(node == NULL){
		return;
	}

	tree_traversal(node->left);
	printf("%s\n", node->word);
	tree_traversal(node->right);

	//free(node);
}
