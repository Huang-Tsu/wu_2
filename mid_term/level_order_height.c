#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tree_node Tree_node;


struct Tree_node{
	char word[2049];
	Tree_node *left;
	Tree_node *right;
};

void free_tree(Tree_node *node);
int find_tree_height(Tree_node *node);
void print_level(Tree_node *node, int height_now);
Tree_node *add_node(Tree_node *root, char *input);
Tree_node *node_initialize(char *word);
void level_order_traversal(Tree_node *node);

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

int find_tree_height(Tree_node *node){
	if(!node)
		return 0;   //可以看作，如果某節點的下一個節點是NULL, 則此節點的高度就是0(tree的高度由0開始算，因為是「根」)

	int left_height = find_tree_height(node->left);
	int right_height = find_tree_height(node->right);
	 
		//回傳比較大的sub_tree
	if(left_height > right_height)
		return left_height + 1;  		//記得+1，因為傳回去的值是往上一層的高度
	else
		return right_height + 1;
	
}
void print_level(Tree_node *node, int height_now){
			/*第一次進來時的height_now就是最終要print的高度
			  因為tree的高度是從0開始計的，假如要print第10層
			  則需要從root(第0層)往下10次，也剛好會把傳進來的10減到0(代表要輸出了)
			  */
	if(!node)	 //這個check 很重要，因為樹兩邊的高度不同，可能有意邊會先到NULL
		return;

	if(height_now == 0){	//等於0代表這是要print出來的節點
		printf("%s\n", node->word);
	}
	else{
		print_level(node->left, height_now-1);	//一直減到等於0, 需要print 的高度跟需要減的次數一樣
		print_level(node->right, height_now-1);	
	}

}
void level_order_traversal(Tree_node *node){
	int tree_height = find_tree_height(node);
	
	for(int i=0; i<=tree_height; i++){
		print_level(node, i);   //從第0層print到樹高, i代表要print的層數
	}

	free_tree(node);
}
void free_tree(Tree_node *node){
	if(!node)
		return;

	free_tree(node->left);
	free_tree(node->right);

	free(node);
}
