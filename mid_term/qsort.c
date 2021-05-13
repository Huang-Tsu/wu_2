#include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void *b){
	return *(int*)a - *(int*)b;
}

int main(){
	int num[3000];
	int cnt=0;

	while(cnt<3000 && scanf("%d", &num[cnt]) != EOF){
		cnt++;
	}

	qsort(num, cnt, sizeof(int), compare);

	for(int i=0; i<cnt; i++){
		printf("%d\n", num[i]);
	}
}
