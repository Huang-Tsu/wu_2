#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_node Tree_node;

enum{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
};

Tree_node *add_node(Tree_node *root, char *input);
Tree_node *node_initialize(char *word);
void tree_traversal(Tree_node *node ,int flag);

struct Tree_node{
	char word[65];
	Tree_node *left;
	Tree_node *right;
};

Tree_node *root;

int main(int argc, char **argv){
	char input[65];

	root = NULL;
	while(scanf("%s", input) != EOF){
		root = add_node(root, input);		
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
Tree_node *add_node(Tree_node *node, char *input){
	if(node == NULL){
		node = node_initialize(input);
		return node;
	}

	int return_value = strcmp(input, node->word);
	if(return_value == 0)
		;	//do noting
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


void tree_traversal(Tree_node *node, int flag){
	if(node == NULL){
		return;
	}

		if(flag == PRE_ORDER){
			printf("%s\n", node->word);
		}
	tree_traversal(node->left, flag);
		if(flag == IN_ORDER){
			printf("%s\n", node->word);
		}
	tree_traversal(node->right, flag);
		if(flag == POST_ORDER){
			printf("%s\n", node->word);
		}

	free(node);
}
