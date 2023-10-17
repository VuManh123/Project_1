#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h> 

#define MAX_SIZE 1000000

// Ð?nh ngh?a c?u trúc cho các nút trong danh sách liên k?t
struct Node {
    int value;
    struct Node* next;
};

// Hàm bãm ðõn gi?n ð? chuy?n giá tr? thành ch? m?c m?ng
int hash(int value) {
    return value % MAX_SIZE;
}

int main() {
    int n;
    scanf("%d", &n);

    // Kh?i t?o m?ng bãm, m?i ph?n t? là m?t con tr? ð?n danh sách liên k?t
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

        // Ki?m tra giá tr? trong danh sách liên k?t
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
            // Thêm giá tr? vào danh sách liên k?t t?i ch? m?c týõng ?ng
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->value = arr[i];
            newNode->next = hashTable[index];
            hashTable[index] = newNode;
        }
    }

    return 0;
}
