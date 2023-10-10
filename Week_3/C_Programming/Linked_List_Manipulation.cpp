#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Su dung danh sach lien ket don
struct Node{
	int data;
	struct Node* next;
}; 
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// Tim phan tu 
int contains(struct Node* head, int data) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}
// 1. Them k vao cuoi danh sach
struct Node* addLast(struct Node* head, int data) {
    if (contains(head, data)) {
        return head;
    }
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    struct Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = newNode;
    return head;
}
// 2. Them k vao dau danh sach
struct Node* addFirst(struct Node* head, int data) {
    if (contains(head, data)) {
        return head;
    }
    struct Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}
// 3. Them u sau v
struct Node* addAfter(struct Node* head, int u, int v) {
    if (contains(head, u)) {
        return head;
    }
    struct Node* newNode = createNode(u);
    struct Node* current = head;
    while (current != NULL && current->data != v) {
        current = current->next;
    }
    if (current == NULL) {
        return head;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}
// 4. Them u truoc v
struct Node* addBefore(struct Node* head, int u, int v) {
    if (contains(head, u)) {
        return head;
    }
    struct Node* newNode = createNode(u);
    if (head == NULL) {
        return newNode;
    }
    if (head->data == v) {
        newNode->next = head;
        return newNode;
    }
    struct Node* current = head;
    while (current->next != NULL && current->next->data != v) {
        current = current->next;
    }
    if (current->next == NULL) {
        return head;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}
// 5. Xoa k khoi danh sach
struct Node* remove(struct Node* head, int data) {
    if (head == NULL) {
        return NULL;
    }
    if (head->data == data) {
        struct Node* newHead = head->next;
        free(head);
        return newHead;
    }
    struct Node* current = head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    if (current->next == NULL) {
        return head;
    }
    struct Node* nodeRemove = current->next;
    current->next = current->next->next;
    free(nodeRemove);
    return head;
}
// 6. Dao nguoc chuoi
struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
// 7. In chuoi
void printList(struct Node* head){
	struct Node* current = head;
	while(current != NULL){
		printf("%d ", current->data);
		current = current->next;
	}
}

int main(){
	int n;
    scanf("%d", &n);
    struct Node* head = NULL;

    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        head = addLast(head, data);
    }

    char cmd[10];
    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "addlast") == 0) {
            int k;
            scanf("%d", &k);
            head = addLast(head, k);
        } else if (strcmp(cmd, "addfirst") == 0) {
            int k;
            scanf("%d", &k);
            head = addFirst(head, k);
        } else if (strcmp(cmd, "addafter") == 0) {
            int u, v;
            scanf("%d %d", &u, &v);
            head = addAfter(head, u, v);
        } else if (strcmp(cmd, "addbefore") == 0) {
            int u, v;
            scanf("%d %d", &u, &v);
            head = addBefore(head, u, v);
        } else if (strcmp(cmd, "remove") == 0) {
            int k;
            scanf("%d", &k);
            head = remove(head, k);
        } else if (strcmp(cmd, "reverse") == 0) {
            head = reverse(head);
        } else if (strcmp(cmd, "#") == 0) {
            break;
        }
    }
    printList(head);

    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
