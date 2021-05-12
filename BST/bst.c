#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_node Tree_node;

void add_node(Tree_node *root, char *input);
void node_initialize(Tree_node *node, char *word);
void pre_order_traversal(Tree_node *node);
void in_order_traversal(Tree_node *node);
void post_order_traversal(Tree_node *node);

struct Tree_node{
	char *word;
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
			pre_order_traversal(root);
			break;
		case 'P':
			post_order_traversal(root);
			break;
		case 'i':
			in_order_traversal(root);
			break;
	}

	free_tree(root);

}
void add_node(Tree_node *node, char *input){
	int return_value = strcmp(node->word, input);
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

	add_node(node->next, input);
}
void node_initialize(Tree_node *node, char *word){
	strcpy(node->word, word);
	node->left = NULL;
	node->right = NULL;
}


void pre_order_traversal(Tree_node *node){
	if(node->next == NULL){
		printf("%s\n", node->word);
		free(node);
		return;
	}
	printf("%s\n", node->word);
	pre_order_traversal(node->left);
	pre_order_traversal(node->right);
	free(node);
}
void in_order_traversal(Tree_node *node){
	if(node->next == NULL){
		printf("%s\n", node->word);
		free(node);
		return;
	}
	pre_order_traversal(node->left);
	printf("%s\n", node->word);
	pre_order_traversal(node->right);
	free(node);
}
void post_order_traversal(Tree_node *node){
	if(node->next == NULL){
		printf("%s\n", node->word);
		free(node);
		return;
	}
	pre_order_traversal(node->left);
	pre_order_traversal(node->right);
	printf("%s\n", node->word);
	free(node);
}
