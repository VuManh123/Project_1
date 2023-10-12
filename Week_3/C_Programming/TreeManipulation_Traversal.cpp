#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int data;
    struct TreeNode* children[10]; 
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    for (int i = 0; i < 10; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

struct TreeNode* findNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        return root;
    }
    for (int i = 0; i < 10; i++) {
        struct TreeNode* found = findNode(root->children[i], data);
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

void insertNode(struct TreeNode* root, int u, int v) {
    struct TreeNode* parent = findNode(root, v);
    if (parent == NULL || findNode(root, u) != NULL) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (parent->children[i] == NULL) {
            parent->children[i] = createNode(u);
            break;
        }
    }
}

void preOrder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        for (int i = 0; i < 10; i++) {
            preOrder(root->children[i]);
        }
    }
}
 
void inOrder(struct TreeNode* root) {
    if (root != NULL) {
        inOrder(root->children[0]);
		printf("%d ",root->data);
		for(int i=1; i<10; i++){
			inOrder(root->children[i]);
		}       
    }
}

void postOrder(struct TreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < 10; i++) {
            postOrder(root->children[i]);
        }
        printf("%d ", root->data);
    }
}

int main() {
    struct TreeNode* root = NULL;
    char cmd[20];
    int u, v;

    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "MakeRoot") == 0) {
            scanf("%d", &u);
            root = createNode(u);
        } else if (strcmp(cmd, "Insert") == 0) {
            scanf("%d %d", &u, &v);
            insertNode(root, u, v);
        } else if (strcmp(cmd, "PreOrder") == 0) {
            preOrder(root);
            printf("\n");
        } else if (strcmp(cmd, "InOrder") == 0) {
            inOrder(root);
            printf("\n");
        } else if (strcmp(cmd, "PostOrder") == 0) {
            postOrder(root);
            printf("\n");
        } else if (strcmp(cmd, "*") == 0) {
            break;
        }
    }

    return 0;
}

