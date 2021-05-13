#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tree_node Tree_node;


struct Tree_node{
	char word[1025];
	int cnt;
	Tree_node *left;
	Tree_node *right;
};

void rm_new_line(char *input);
Tree_node *add_node(Tree_node *root, char *input);
Tree_node *node_initialize(char *word);
void tree_traversal(Tree_node *node);

Tree_node *root;

int main(int argc, char **argv){
	char input[1025];
	int line_cnt = 0;


	while(fgets(input, 1025, stdin) != NULL && line_cnt<100){
		if(isspace(*input))
			continue;
		rm_new_line(input);
		root = add_node(root, input);		
		line_cnt ++;
	}

	tree_traversal(root);

	return 0;
}
Tree_node *add_node(Tree_node *node, char *input){
	if(node == NULL){
		node = node_initialize(input);
		return node;
	}

	int return_value = strcmp(input, node->word);
	if(return_value == 0){
		node->cnt ++;
	}
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
	new_node->cnt = 1;
	strcpy(new_node->word, word);
	new_node->left = new_node->right = NULL;
	return new_node;
}


void tree_traversal(Tree_node *node){
	if(node == NULL){
		return;
	}

	tree_traversal(node->left);
	for(int i=0; i<node->cnt; i++){
		printf("%s\n", node->word);
	}
	tree_traversal(node->right);

	free(node);
}
void rm_new_line(char *input){
	int end_idx = strlen(input);

	if(input[end_idx-1] == '\n')
		input[end_idx-1] = '\0';

	return;
}
