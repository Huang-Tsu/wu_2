#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100001

typedef struct Hash Hash;
struct Hash{
	char *word;
	int cnt;
	Hash *next;
};

void InsertHashNode(char *input);
int Hash65(char *input);
unsigned int my_pow(int num, int n);
Hash *NewHashNode(char *input);
int compare(const void *a, const void *b);
char *getword(char *ptr, char *word);
void RmNewLine(char *input);

Hash *g_hash_table[MAX_LEN];
int g_hash_idx[MAX_LEN];
int g_hash_idx_cnt = 0;
Hash *g_arr[MAX_LEN];
int g_arr_cnt = 0;
char g_delim[] = {".,’ \"'?)("};

int main(){
	char input[MAX_LEN];
	char word[MAX_LEN];
	char *ptr;
	Hash *hash_ptr;
	int i;
	Hash *next_hash;

	while(fgets(input, MAX_LEN, stdin)){
		RmNewLine(input);
		ptr = input;

		while((ptr=getword(ptr, word))){
			InsertHashNode(word);
		}
		
	}

		//put to arr
	for(i=0; i<g_hash_idx_cnt; i++){
		hash_ptr = g_hash_table[g_hash_idx[i]];

		for(hash_ptr; hash_ptr; hash_ptr=hash_ptr->next){
			g_arr[g_arr_cnt++] = hash_ptr;
		}
	}

	qsort(g_arr, g_arr_cnt, sizeof(Hash*), compare);

		//output result
	for(i=0; i<300; i++){
		printf("%s\t%d\n", g_arr[i]->word, g_arr[i]->cnt);
	}

		//free()
	for(i=0; i<g_hash_idx_cnt; i++){
		hash_ptr = g_hash_table[g_hash_idx[i]];

		for(hash_ptr; hash_ptr; hash_ptr=next_hash){
			next_hash = hash_ptr->next;
			free(hash_ptr->word);
			free(hash_ptr);
		}
	}
}
void InsertHashNode(char *input){
	int idx = Hash65(input);
	if(!g_hash_table[idx]){
		g_hash_table[idx] = NewHashNode(input);
		g_hash_idx[g_hash_idx_cnt++] = idx;
	}
	else{
		Hash *ptr = g_hash_table[idx];
		Hash *pre = ptr;

		for(ptr; ptr; ptr=ptr->next){
			pre = ptr;
			if(strcmp(ptr->word, input) == 0){
				ptr->cnt ++;
				return;
			}
		}

		pre->next = NewHashNode(input);
	}
}
int Hash65(char *input){
	unsigned int sum = 0;
	int len = strlen(input);

	for(int i=0; i<len; i++){
		sum += input[i]*my_pow(65, i);
	}

	return sum%MAX_LEN;
}
unsigned int my_pow(int num, int n){
	if(n == 0)
		return 1;

	unsigned int sum = 1;

	for(int i=0; i<n; i++)
		sum *= num;

	return sum;
}
Hash *NewHashNode(char *input){
	Hash *new = (Hash*)calloc(1, sizeof(Hash));
	new->word = strdup(input);
	new->cnt = 1;
	new->next = NULL;

	return new;
}
int compare(const void *a, const void *b){
	Hash *input1 = *(Hash**)a;
	Hash *input2 = *(Hash**)b;
	if(input1->cnt != input2->cnt)
		return input2->cnt - input1->cnt;
	else
		return strcmp(input1->word, input2->word);
}
char *getword(char *ptr, char *word){
	char *qtr = word;

	while(*ptr && (isspace(*ptr) || strchr(g_delim, *ptr)))
		ptr ++;
	
	while(*ptr && (!isspace(*ptr) && !strchr(g_delim, *ptr)))
		*qtr++ = tolower(*ptr++);

	*qtr = '\0';

	if(qtr == word)
		return NULL;

	return ptr;
}
void RmNewLine(char *input){
	int len = strlen(input);
	if(input[len-1] == '\n')
		input[len-1] = '\0';
}
