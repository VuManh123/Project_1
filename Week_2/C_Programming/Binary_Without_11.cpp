#include <stdio.h>
#include <string.h>
#include <math.h>

void convertBinary(int n, int N) {
    char str[N + 1];
    str[0] = '\0';
    while (n > 0) {
        char digit1 = n % 2 + '0';
        char digit2 = n/2 % 2 + '0';
        if(digit1 == '1' && digit2 == '1') return;
        char temp[2] = {digit1, '\0'};
        strcat(temp,str);
        strcpy(str,temp);
        n = n / 2;
    }
    char tmp[N];
    while (strlen(str) < N) {
        strcpy(tmp, "0"); 
    	strcat(tmp, str); 
    	strcpy(str, tmp);
    }
    printf("%s\n", str);
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < pow(2, N); i++) {
        convertBinary(i, N);
    }
    return 0;
}
