#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h> 

#define MAX_SIZE 1000000

// �?nh ngh?a c?u tr�c cho c�c n�t trong danh s�ch li�n k?t
struct Node {
    int value;
    struct Node* next;
};

// H�m b�m ��n gi?n �? chuy?n gi� tr? th�nh ch? m?c m?ng
int hash(int value) {
    return value % MAX_SIZE;
}

int main() {
    int n;
    scanf("%d", &n);

    // Kh?i t?o m?ng b�m, m?i ph?n t? l� m?t con tr? �?n danh s�ch li�n k?t
    struct Node* hashTable[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        int index = hash(arr[i]);
        struct Node* current = hashTable[index];
        bool found = false;

        // Ki?m tra gi� tr? trong danh s�ch li�n k?t
        while (current != NULL) {
            if (current->value == arr[i]) {
                found = true;
                break;
            }
            current = current->next;
        }

        if (found) {
            printf("1\n");
        } else {
            printf("0\n");
            // Th�m gi� tr? v�o danh s�ch li�n k?t t?i ch? m?c t��ng ?ng
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->value = arr[i];
            newNode->next = hashTable[index];
            hashTable[index] = newNode;
        }
    }

    return 0;
}
