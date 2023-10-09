#include <stdio.h>
#include <string.h>

int main() {
    int n;
    int sum = 0; 
    int max = -1000;
    int min = 1000;
    scanf("%d", &n);
    int a[n];
    for (int i = 1; i <= n; i++){
    	scanf("%d", &a[i]);
    	if(max<a[i]) max = a[i];
    	if(min>a[i]) min =a[i];
    	sum = sum+a[i];
	}
    char s[15];
    while (1) {
        scanf("%s", s);
        if (strcmp(s, "find-max") == 0)
            printf("%d\n", max);
        else if (strcmp(s, "find-min") == 0) 
            printf("%d\n", min);
        else if (strcmp(s, "find-max-segment") == 0) {
            int x, y;
            int ans = -1000;
            scanf("%d %d", &x, &y);
            for (int i = x; i <= y; i++)
                if(ans<a[i]) ans=a[i];
            printf("%d\n", ans);
        }
        else if (strcmp(s, "sum") == 0) 
            printf("%d\n", sum);
        else if(strcmp(s, "***") == 0) break;
        else continue;
    }
    return 0;
}
