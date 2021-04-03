#include <stdio.h>
#include <stdlib.h>
#define SUM	5
int compare(const void *a, const void *b);

struct student{
	char name[1024];
	int score[6];
}students[1024];
int main(){
	
	int stu_cnt = 0;
	char input_str[1024];
	while(scanf("%s", students[stu_cnt].name) != EOF){
		students[stu_cnt].score[SUM] = 0;
		for(int i=0; i<5; i++){
			scanf("%d", &students[stu_cnt].score[i]);	
			students[stu_cnt].score[SUM] += students[stu_cnt].score[i];
		}
		stu_cnt ++;
	}
	
	qsort(students, stu_cnt, sizeof(struct student), compare); 	

	for(int i=0; i<stu_cnt; i++){
		printf("%s\t", students[i].name);
		for(int j=0; j<4; j++){
			printf("%d\t", students[i].score[j]);
		}
		printf("%d\n", students[i].score[4]);
	}

	return 0;
}
int compare(const void *a, const void *b){
	struct student *input1 = (struct student*)a;	
	struct student *input2 = (struct student*)b;	
	return input2->score[SUM] - input1->score[SUM];
}
