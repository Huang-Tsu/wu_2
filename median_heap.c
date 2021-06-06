#include <stdio.h>
#include <stdlib.h>

void InsertToHeap(int input);
void InsertToMaxHeap(int input);
void InsertToMinHeap(int input);
void PopMinHeap();
void PopMaxHeap();
void MaxHeapifyUp(int idx);
void MinHeapifyUp(int idx);
void MaxHeapifyDown(int idx);
void MinHeapifyDown(int idx);
void Swap(int *array, int idx1, int idx2);

int max_heap[1000000]; // less then median
int min_heap[1000000]; // more then median
int max_heap_cnt = 0;
int min_heap_cnt = 0;
int median = -1;

int main(){
	int input;
	
	while(scanf("%d", &input) != EOF){
		InsertToHeap(input);

		printf("%d\n", median);
	}

	return 0;
}
void InsertToHeap(int input){
	if(min_heap_cnt == max_heap_cnt){
		if(input >= median){
			InsertToMinHeap(input);
			median = min_heap[0];
		}
		else{
			InsertToMaxHeap(input);
			median = max_heap[0];
		}
		return;
	}
	else if(min_heap_cnt > max_heap_cnt){	//右邊的heap比左邊大1
		if(input >= median){		//往多的那邊插(右邊)，故要平衡
			InsertToMaxHeap(min_heap[0]);	//左邊+1
			PopMinHeap();					//右邊-1
			InsertToMinHeap(input);
		}
		else{					//插入比較少的那邊 故直接插入
			InsertToMaxHeap(input);			
		}
	}
	else{	//右邊的heap比左邊大1
		if(input >= median){	
			InsertToMinHeap(input);
		}
		else{				
			InsertToMinHeap(max_heap[0]);	
			PopMaxHeap();				
			InsertToMaxHeap(input);			
		}
	}
	median = (max_heap[0] + min_heap[0]) / 2;	//兩邊相等
}
void InsertToMaxHeap(int input){
	max_heap[max_heap_cnt++] = input;
	MaxHeapifyUp(max_heap_cnt-1);
}
void InsertToMinHeap(int input){
	min_heap[min_heap_cnt++] = input;
	MinHeapifyUp(min_heap_cnt-1);
}
void PopMinHeap(){
	Swap(min_heap, 0, --min_heap_cnt);
	MinHeapifyDown(0);
}
void PopMaxHeap(){
	Swap(max_heap, 0, --max_heap_cnt);
	MaxHeapifyDown(0);

}
void MaxHeapifyUp(int idx){
	if(idx == 0)
		return;

	int root_idx = (idx-1) / 2;
	int largest_idx = root_idx;
	int left = root_idx*2 + 1;
	int right = root_idx*2 + 2;

	if(max_heap[left] > max_heap[largest_idx])
		largest_idx = left;
	if(right < max_heap_cnt && max_heap[right] > max_heap[largest_idx])
		largest_idx = right;

	if(largest_idx == root_idx)
		return;
	else{
		Swap(max_heap, root_idx, largest_idx);
		MaxHeapifyUp(root_idx);
	}
}
void MinHeapifyUp(int idx){
	if(idx == 0)
		return;

	int root_idx = (idx-1) / 2;
	int smallest_idx = root_idx;
	int left = root_idx*2 + 1;
	int right = root_idx*2 + 2;

	if(min_heap[left] < min_heap[smallest_idx])
		smallest_idx = left;
	if(right < min_heap_cnt && min_heap[right] < min_heap[smallest_idx])
		smallest_idx = right;

	if(smallest_idx == root_idx)
		return;
	else{
		Swap(min_heap, root_idx, smallest_idx);
		MinHeapifyUp(root_idx);
	}
}
void MaxHeapifyDown(int idx){
	if(idx*2+1 >= max_heap_cnt)
		return;

	int root_idx = idx;
	int largest_idx = root_idx;
	int left = root_idx*2 + 1;
	int right = root_idx*2 + 2;

	if(max_heap[left] > max_heap[largest_idx])
		largest_idx = left;
	if(right < max_heap_cnt && max_heap[right] > max_heap[largest_idx])
		largest_idx = right;

	if(largest_idx == root_idx)
		return;
	else{
		Swap(max_heap, root_idx, largest_idx);
		MaxHeapifyDown(largest_idx);
	}
	
}
void MinHeapifyDown(int idx){
	if(idx*2+1 >= min_heap_cnt)
		return;

	int root_idx = idx;
	int smallest_idx = root_idx;
	int left = root_idx*2 + 1;
	int right = root_idx*2 + 2;

	if(min_heap[left] < min_heap[smallest_idx])
		smallest_idx = left;
	if(right < min_heap_cnt && min_heap[right] < min_heap[smallest_idx])
		smallest_idx = right;

	if(smallest_idx == root_idx)
		return;
	else{
		Swap(min_heap, root_idx, smallest_idx);
		MinHeapifyDown(smallest_idx);
	}
}
void Swap(int *array, int idx1, int idx2){
	int temp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = temp;
}
