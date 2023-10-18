#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, M;
    scanf("%d %d", &n, &M);
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
	
	// Quick sort voi ham compare 
    qsort(arr, n, sizeof(int), compare);
    int count = 0;
    int left = 0, right = n - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == M) {
            count++;
            left++;
            right--;
        } else if (sum < M) {
            left++;
        } else {
            right--;
        }
    }
    printf("%d", count);
    free(arr);
    return 0;
}

