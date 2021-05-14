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

void free_tree(Tree_node *node);
Tree_node *add_node(Tree_node *root, char *input);
Tree_node *node_initialize(char *word);
void level_order_traversal(Tree_node *node);

Queue *en_queue(Queue *head, Tree_node *input);
Queue *queue_initialize(Tree_node *input);
Queue *de_queue(Queue *front);


int main(int argc, char **argv){
	char input[2049];
	Tree_node *root;


	while(scanf("%s", input) != EOF){
		if(isspace(*input))
			continue;
		root = add_node(root, input);		
	}

	level_order_traversal(root);

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
		printf("node_left:%p\tnode_right:%p\n", new_node->left, new_node->right);
	return new_node;
}




void level_order_traversal(Tree_node *node){
	Queue *front, *rear;
	front = rear = queue_initialize(node);
		printf("front:%p\trear:%p\n", front->tree_node, rear->tree_node);

	if(rear->tree_node->left)
		rear = en_queue(rear, node->left);
	if(rear->tree_node->right)
		rear = en_queue(rear, node->right);
	printf("%s\n", front->tree_node->word);
	front = de_queue(front);

	while(front){
			puts("hi");
		if((rear->tree_node->left)!=NULL)
			rear = en_queue(rear, rear->tree_node->left);
		if(rear->tree_node->right)
			rear = en_queue(rear, rear->tree_node->right);
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
	new_node->tree_node = input;
		printf("tree_node:%p\tinput_node:%p\n", new_node->tree_node, input);
	new_node->next = NULL;
	return new_node;

}
