#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
	//int g_node_cnt;
	//int g_free_cnt;
	//int g_traversal_cnt;

#define BLACK 1
#define RED 0

typedef struct RBTNode RBTNode;

struct RBTNode{
	char *word;
	int color;
	int visited;
	int cnt;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
};

	static RBTNode *nil;
	static RBTNode *root;
void BuildRBT();
void InsertRBTNode(char *input);
void FixUpInsert(RBTNode *now);
RBTNode *InitializeRBTNode(char *input);
void FreeRBT(RBTNode *node);
void FindLargest(RBTNode *node, RBTNode **largest, int *largest_cnt);
void RBTRightRotation(RBTNode *node);
void RBTLeftRotation(RBTNode *node);
int IsLeftNode(RBTNode *node);
void BackVisitedToZero(RBTNode *node);
void Output();
char *getword(char *ptr, char *word);
	//void Traversal(RBTNode *node);

int main(){
	nil = (RBTNode*)calloc(1, sizeof(RBTNode));
	nil->color = BLACK;
	nil->parent = nil->left = nil->right = NULL;
	root = nil;

	BuildRBT();
	
	Output();

		//Traversal(root);	
	FreeRBT(root);
	free(nil);
	//free(root);


	return 0;
}
void BuildRBT(){
	char input[100001];
	char word[100001];
	char *ptr;

	while(fgets(input, 100001 ,stdin)){
		BackVisitedToZero(root);
		ptr = input;

		while((ptr = getword(ptr, word)) != NULL){
			InsertRBTNode(word);
		}
	}
}
void InsertRBTNode(char *input){
	static RBTNode *new_node;
	static RBTNode *current;
	static RBTNode *pre;
	static int return_value;
	if(root == nil){
		root = InitializeRBTNode(input);
		root->color = BLACK;

		return;
	}
	current = root;

	while(current != nil){
		pre = current;
		return_value =strcmp(input, current->word);

		if(return_value == 0){
			if(current->visited == 0){
				current->visited ++;
				current->cnt ++;
			}
			return;
		}
		if(return_value < 0)
			current = current->left;
		else
			current = current->right;
	}

	new_node = InitializeRBTNode(input);
	new_node->parent = pre;

	if(strcmp(input, pre->word) < 0){
		pre->left = new_node;
	}else{
		pre->right = new_node;
	}

	FixUpInsert(new_node);
}
void FixUpInsert(RBTNode *now){
	RBTNode *grandpa = now->parent->parent;
	RBTNode *uncle;

	while(now->parent->color == RED){
		grandpa = now->parent->parent;

		if(IsLeftNode(now->parent)){ //parent is left
			uncle = grandpa->right;

			if(uncle->color == RED){
				now->parent->color = uncle->color = BLACK;
				grandpa->color = RED;

				now = grandpa;
			}else{	//uncle is black
				if(!IsLeftNode(now)){ //left right case
					now = now->parent;
					RBTLeftRotation(now);	//turn to left left case
				}

				grandpa->color = RED;
				now->parent->color = BLACK;
				RBTRightRotation(grandpa);
			}
		}else{ //parent is right
			uncle = grandpa->left;

			if(uncle->color == RED){
				now->parent->color = uncle->color = BLACK;
				grandpa->color = RED;

				now = grandpa;
			} else{	//uncle is black
				if(IsLeftNode(now)){ //right left case
					now = now->parent;
					RBTRightRotation(now);	//turn to right right case
				}

				grandpa->color = RED;
				now->parent->color = BLACK;
				RBTLeftRotation(grandpa);
			}

		}
	}

	root->color = BLACK;
}
RBTNode *InitializeRBTNode(char *input){
		//g_node_cnt++;
		//printf("node_cnt:%d\n", g_node_cnt);
	static RBTNode *new_node;
	new_node = (RBTNode*)calloc(1, sizeof(RBTNode));
		if(!new_node){
			puts("Memory allocation failed.");
			exit(1);
		}

	new_node->word = strdup(input);
	new_node->visited = 1;
	new_node->cnt = 1;
	new_node->left = new_node->right = new_node->parent = nil;
	new_node->color = RED;

	return new_node;
}
void FreeRBT(RBTNode *node){
	if(node == nil)
		return;

	FreeRBT(node->left);
	FreeRBT(node->right);

	free(node->word);
	free(node);
		//g_free_cnt ++;
		//printf("free cnt:%d\n", g_free_cnt);
	return;
}
void FindLargest(RBTNode *node, RBTNode **largest, int *largest_cnt){
	if(node == nil)
		return;

	FindLargest(node->left, largest, largest_cnt);
	if(node->cnt > *largest_cnt){
		*largest = node;
		*largest_cnt = node->cnt;
	}
	FindLargest(node->right, largest, largest_cnt);
}
void RBTRightRotation(RBTNode *node){
	static RBTNode *old;
	static RBTNode *new;
	old = node;
	new = node->left;

	old->left = new->right;
	if(new->right != nil)
		new->right->parent = old;

	new->right = old;
	new->parent = old->parent;
	if(old != root){
		if(IsLeftNode(old))
			new->parent->left = new;
		else
			new->parent->right = new;
	}else{
		root = new;
	}
	old->parent = new;
}
void RBTLeftRotation(RBTNode *node){
	static RBTNode *old;
	static RBTNode *new;
	old = node;
	new = node->right;

	old->right = new->left;
	if(new->left != nil)
		new->left->parent = old;

	new->left = old;
	new->parent = old->parent;
	if(old != root){
		if(IsLeftNode(old))
			new->parent->left = new;
		else
			new->parent->right = new;
	}else{
		root = new;
	}
	old->parent = new;
}
int IsLeftNode(RBTNode *node){
	if(!node)
		return 0;

	return (node->parent->left == node)? 1 : 0;
}
void BackVisitedToZero(RBTNode *node){
	if(node == nil)
		return;

	node->visited = 0;
	BackVisitedToZero(node->left);
	BackVisitedToZero(node->right);
}
void Output(){
	RBTNode *largest_node;
	int largest_cnt;

	for(int i=0; i<10; i++){
		largest_cnt = 0;
		
		FindLargest(root, &largest_node, &largest_cnt);

		largest_node->cnt = -1;
		printf("%s\n", largest_node->word);
	}

}
char *getword(char *ptr, char *word){
	char *qtr = word;

	while(*ptr && isspace(*ptr))
			ptr ++;

	while(*ptr && !isspace(*ptr))
		*qtr++ = *ptr++;

	*qtr = '\0';

	if(qtr == word)
		return NULL;
	
	return ptr;
}
	/*
	void Traversal(RBTNode *node){
		if(node == nil)
			return;

		Traversal(node->left);
				printf("In traversal:%s\n", node->word);
		Traversal(node->right);
			//g_traversal_cnt ++;
			//printf("traversal_cnt:%d\n", g_traversal_cnt);

			
	}
	*/
