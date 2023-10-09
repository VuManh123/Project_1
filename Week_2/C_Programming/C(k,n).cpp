#include <stdio.h>
#include<math.h>

int modulo = pow(10,9) + 7; 

long int  memo[501][1000]; 

long int ToHop(int k, int n) {
    if (k == 0 || k == n) return 1;
    if (k == 1 || k == n-1) return n; 
    if (memo[k][n] != 0) {
        return memo[k][n] % modulo; 
    }
    memo[k][n] = ToHop(k - 1, n - 1) + ToHop(k, n - 1);
    return memo[k][n] % modulo; 
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);
    printf("%d", ToHop(k, n));
    return 0;
}
