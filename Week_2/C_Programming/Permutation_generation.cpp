#include <stdio.h>
#include <stdbool.h>

void printArray(int arr[], int n){
	for(int i=0; i<n; i++) printf("%d ", arr[i]);
	printf("\n");
}
void swap(int arr[], int i, int j){
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void permutation(int arr[], int n){
	while(true){
		printArray(arr, n);
		int i = n-2;
		while(i>=0 && arr[i] >= arr[i+1]) i--;
		if(i == -1) break;
		
		int j = n-1;
		while(arr[j] <= arr[i]) j--;
		
		swap(arr, i, j);
		
		//Dao chuoi tu arr[i+1] den het
		int left = i+1;
		int right = n-1;
		while(left < right){
			swap(arr, left, right);
			left++;
			right--;
		}
	}
}

int main(){
	int n; 
	scanf("%d", &n);
	int arr[n];
	for(int i=0; i<n; i++){
		arr[i] = i+1;	
	}
	permutation(arr, n); 
}
