#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_node Tree_node;

enum{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
};

void add_node(Tree_node *root, char *input);
void node_initialize(Tree_node *node, char *word);
void tree_traversal(Tree_node *node ,int flag);

struct Tree_node{
	char word[65];
	Tree_node *left;
	Tree_node *right;
};

Tree_node *root;

int main(int argc, char **argv){
	char input[65];

	root = (Tree_node*)calloc(1, sizeof(Tree_node));
	scanf("%s", input);
	node_initialize(root, input);

	while(scanf("%s", input) != EOF){
		add_node(root, input);		
	}

	switch(argv[1][1]){
		case 'p':
			tree_traversal(root, PRE_ORDER);
			break;
		case 'P':
			tree_traversal(root, POST_ORDER);
			break;
		case 'i':
			tree_traversal(root, IN_ORDER);
			break;
	}

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
	node->left = NULL;
	node->right = NULL;
}


void tree_traversal(Tree_node *node, int flag){
		if(flag == PRE_ORDER){
			printf("%s\n", node->word);
		}
	if(node->left != NULL){
		tree_traversal(node->left, flag);
	}
		if(flag == IN_ORDER){
			printf("%s\n", node->word);
		}
	if(node->right != NULL){
		tree_traversal(node->right, flag);
	}
		if(flag == POST_ORDER){
			printf("%s\n", node->word);
		}
	free(node);
}
