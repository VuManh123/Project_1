#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//Use binary search tree with string
struct Node{
	char data[50];
	struct Node* left;
	struct Node* right;
};

struct Node* createNode(char data[]){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(newNode->data, data);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode; 
}

struct Node* insert(struct Node* root, char data[]){
	if(root == NULL){
		return createNode(data);
	}
	if(strcmp(data, root->data) < 0){
		root->left = insert(root->left, data);
	}else{
		root->right = insert(root->right, data);
	}
	return root;
}

struct Node* search(struct Node* root, char data[]){
	if(root == NULL || strcmp(data, root->data) == 0){
		return root;
	}
	if(strcmp(data, root->data) < 0){
		return search(root->left, data);
	}else{
		return search(root->right, data);
	}
}

int main(){
	struct Node* root = NULL;
	char data[50];
	while(strcmp(data, "*") != 0){
		scanf("%s", data);
		root = insert(root, data);
	}
	char cmd[10];
	while(strcmp(data, "***") != 0){
		scanf("%s", cmd);
		if(strcmp(cmd, "insert") == 0){
			scanf("%s", data);
			if(search(root, data) != NULL){
				printf("0\n");
			}else{
				root = insert(root, data);
				printf("1\n");
			}
		}
		else if(strcmp(cmd, "find") == 0){
			scanf("%s", data);
			if(search(root, data) == NULL){
				printf("0\n");
			}else{
				printf("1\n");
			}
		}
		else break;
	}
}
