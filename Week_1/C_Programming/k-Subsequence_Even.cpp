#include<stdio.h>

//Su dung mang tinh tong de cai thien thuat toan 
int main(){
	int k, n;
    scanf("%d", &n);
    scanf("%d", &k);
    int A[n];
    int prefixSum[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        if (i == 0) {
            prefixSum[i] = A[i];
        } else {
            prefixSum[i] = prefixSum[i - 1] + A[i];
        }
    }  
    int count = 0;
    for (int i = 0; i < n - k + 1; i++) {
        long long sum;
        if (i == 0) {
            sum = prefixSum[i + k - 1];
        } else {
            sum = prefixSum[i + k - 1] - prefixSum[i - 1];
        }
        if (sum % 2 == 0) {
            count++;
        }
    } 
    printf("%d", count);
    
    return 0;
}
