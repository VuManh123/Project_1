#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long sum = 0; 
    
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        sum += tmp;
    }
    
    printf("%lld\n", sum);
    
    return 0;
}
