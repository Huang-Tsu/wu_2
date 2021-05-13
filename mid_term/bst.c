#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_node Tree_node;

enum{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
};

void rm_new_line(char *input);
void add_node(Tree_node *root, char *input);
void node_initialize(Tree_node *node, char *word);
void tree_traversal(Tree_node *node);

struct Tree_node{
	char word[1025];
	Tree_node *left;
	Tree_node *right;
};

Tree_node *root;

int main(int argc, char **argv){
	char input[1025];
	int line_cnt = 0;

	root = (Tree_node*)calloc(1, sizeof(Tree_node));
	fgets(input, 1025, stdin);
	rm_new_line(input);
	node_initialize(root, input);

	while(fgets(input, 1025, stdin) && line_cnt++<100){
		rm_new_line(input);
		add_node(root, input);		
	}

	tree_traversal(root);

	return 0;
}
void add_node(Tree_node *node, char *input){
	int return_value = strcmp(input, node->word);
	if(return_value == 0)
		return;
	if(return_value < 0){
		if(node->left == NULL){
			node->left = (Tree_node*)calloc(1, sizeof(Tree_node));
			node_initialize(node->left, input);
			return;
		}

		add_node(node->left, input);
	}
	else{
		if(node->right == NULL){
			node->right = (Tree_node*)calloc(1, sizeof(Tree_node));
			node_initialize(node->right, input);
			return;
		}

		add_node(node->right, input);
	}
}
void node_initialize(Tree_node *node, char *word){
	strcpy(node->word, word);
	node->left = node->right = NULL;
}


void tree_traversal(Tree_node *node){
	if(node == NULL){
		return;
	}

	tree_traversal(node->left);
	printf("%s\n", node->word);
	tree_traversal(node->right);

	free(node);
}
void rm_new_line(char *input){
	int end_idx = strlen(input);

	if(input[end_idx-1] == '\n')
		input[end_idx-1] = '\0';

	return;
}
