#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int stepsToGet_Clitres(int a, int b, int c) {
    int gcd_ab = gcd(a, b);
    
    if (c > a && c > b) {
        return -1;
    }
    if (c % gcd_ab != 0) {
        return -1;
    }

    int steps = 0;
    int x = 0, y = 0;

    while (x != c && y != c) {
        if (x == 0) {
            x = a;
            steps++;
        } else if (y == b) {
            y = 0;
            steps++;
        } else {
            int pour = (x < (b - y)) ? x : (b - y);
            x -= pour;
            y += pour;
            steps++;
        }
    }

    return steps;
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    int steps;
    if(a<b) steps = stepsToGet_Clitres(a, b, c);
    else steps = stepsToGet_Clitres(b, a, c);
    printf("%d", steps);
}
