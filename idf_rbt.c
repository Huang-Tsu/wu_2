//一次讀一行
    //把一行當中讀到的字放入hash table
    //一樣的字只放一次
    	//如此可以保證一行只會得到一個字一次

    //把這行新得到的所有字放入RBT中
    //如果有一樣的字就cnt++
    //不一樣就建新的node

    //全部讀取完後
    //把RBT的字全部放到用struct 建立的arr中
    //用qsort排序
    //接著把前十個輸出就是答案
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLACK 1
#define RED 0
#define NEW_TABLE_NODE 1
#define HASH_SIZE 100000
#define MAX_ARR_LEN 100000

typedef struct RBTNode RBTNode;
typedef struct HashTable HashTable;
typedef struct List List;

struct List{
	char *word;
	int cnt;
};
struct HashTable{
	char *word;
	HashTable *next;
};
struct RBTNode{
	char *word;
	int color;
	int cnt;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
};


	//for qsort()
int compare(const void *a, const void *b);
	//for hash structure
int hash65(char *input);
unsigned int my_pow(int input, int times);
int PushToHashTable(char *input);
HashTable *InitializeHashNode(char *input);
	//for Red-Black Tree
void BuildRBT();
void InsertRBTNode(char *input);
void FixUpInsert(RBTNode *now);
RBTNode *InitializeRBTNode(char *input);
void FreeRBT(RBTNode *node);
void RBTRightRotation(RBTNode *node);
void RBTLeftRotation(RBTNode *node);
int IsLeftNode(RBTNode *node);
	//general function
void Output();
char *getword(char *ptr, char *word);
void PutWordsToArrayFromTree(RBTNode *node);

		//hash
	HashTable **g_table;	//table 是用來篩選掉同樣的字的
	int g_hash_node_idx[HASH_SIZE]; //紀錄有用到hash table的那些index, free時要用
	int g_hash_node_idx_cnt;
		//Red-Black Tree
	static RBTNode *nil;
	static RBTNode *root;
		//final result
	List arr[MAX_ARR_LEN];
	int g_word_cnt = 0;		//紀錄總共有幾個字, for qsort

int main(){
		//preparation for Red-Black Tree
	nil = (RBTNode*)calloc(1, sizeof(RBTNode));
	nil->color = BLACK;
	nil->parent = nil->left = nil->right = NULL;
	root = nil;

	char input_line[100001];
	char word[100001];
	char *ptr;
	char *new_word[100000];	//紀錄這一行新增的字,插入tree時要用
	int new_word_cnt;
	int i;
	HashTable *next_hash;	//free 時用的
	
	while(fgets(input_line, 100001 ,stdin)){
		g_hash_node_idx_cnt = 0;
		new_word_cnt = 0;
		ptr = input_line;
		g_table = (HashTable**)calloc(HASH_SIZE, sizeof(HashTable));

			//push words get from line into the hash table
			//same words will only be push once
		while((ptr = getword(ptr, word)) != NULL){
				//把get到的字放到hash table 如果已經存在就不放
				//這一步可以篩選掉一行當中同樣的字
			if(PushToHashTable(word)){		//push success:word did not exist in the hash table
				new_word[new_word_cnt++] = strdup(word);
			}
		}
			//push words in the hash table to Red-Black Tree 
		for(i=0; i<new_word_cnt; i++){
			InsertRBTNode(new_word[i]);
			free(new_word[i]);
		}
			//free table and words
		for(i=0; i<g_hash_node_idx_cnt; i++){
			while(g_table[g_hash_node_idx[i]]){	//走訪hash table的idx
				next_hash = g_table[g_hash_node_idx[i]]->next;
				free(g_table[g_hash_node_idx[i]]->word);
				free(g_table[g_hash_node_idx[i]]);
				g_table[g_hash_node_idx[i]] = next_hash;
			}
		}

		free(g_table);
	}

	PutWordsToArrayFromTree(root);

	qsort(arr, g_word_cnt, sizeof(List), compare);

	Output();

	for(i=0; i<g_word_cnt; i++){
		free(arr[i].word);
	}
	FreeRBT(root);
	free(nil);

	return 0;
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
			current->cnt ++;
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
		//printf("node_cnt:%d\n", g_node_cnt);
	static RBTNode *new_node;
	new_node = (RBTNode*)calloc(1, sizeof(RBTNode));
		if(!new_node){
			puts("Memory allocation failed.");
			exit(1);
		}

	new_node->word = strdup(input);
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
void Output(){

	for(int i=0; i<10; i++){
		printf("%s\n", arr[i].word);
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
void PutWordsToArrayFromTree(RBTNode *node){
	if(node == nil)
		return;

	PutWordsToArrayFromTree(node->left);
	arr[g_word_cnt].word = strdup(node->word);  
	arr[g_word_cnt].cnt = node->cnt;  
	g_word_cnt ++;
	PutWordsToArrayFromTree(node->right);
}
int PushToHashTable(char *input){
	int idx = hash65(input);
	if(!g_table[idx]){
		g_table[idx] = InitializeHashNode(input);
		g_hash_node_idx[g_hash_node_idx_cnt++] = idx;
	}
	else{
		HashTable *ptr = g_table[idx];
		HashTable *pre = ptr;
		for(ptr; ptr; ptr=ptr->next){
			if(strcmp(ptr->word, input) == 0)
				return 0;
		
			pre = ptr;
		}
		pre->next = InitializeHashNode(input);
	}

	return NEW_TABLE_NODE;
}
HashTable *InitializeHashNode(char *input){
	HashTable *new_node = (HashTable*)calloc(1, sizeof(HashTable));
	new_node->word = strdup(input);
	new_node->next = NULL;
	
	 return new_node;
}
int hash65(char *input){
	unsigned int sum = 0;
	int len = strlen(input);

	for(int i=0; i<len; i++){
		sum += input[i] * my_pow(65, len-1-i);
	}

	return sum%HASH_SIZE;
}
unsigned int my_pow(int input, int times){
	if(times == 0){
		return 1;
	}
	unsigned int result = 1;

	for(int i=1; i<=times; i++){
		result *= input;
	}
	return result;
}
int compare(const void *a, const void *b){
	List *input1 = (List*)a;
	List *input2 = (List*)b;
	if(input1->cnt != input2->cnt)
		return input2->cnt - input1->cnt;
	else
		return strcmp(input1->word, input2->word);

}
