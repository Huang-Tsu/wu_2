#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_node Tree_node;

struct Tree_node{
	char *word;
	Tree_node *left;
	Tree_node *right;
};

Tree_node *root;

int main(){
	root = (Tree_node*)calloc(1, sizeof(Tree_node));

}
