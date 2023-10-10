#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct TreeNode{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* createNode(int data){
	struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode; 
}

struct TreeNode* insertNodeToBST(struct TreeNode* root, int data){
	if(root == NULL)
		return createNode(data);
	if(data<root->data){
		root->left = insertNodeToBST(root->left, data);
	}
	else if(data>root->data){
		root->right = insertNodeToBST(root->right, data);
	}
	return root;
}

void preOrderTraversal(struct TreeNode* root){
	if(root==NULL){
		return;
	}
	printf("%d ", root->data);
	preOrderTraversal(root->left);
	preOrderTraversal(root->right);
}

int main(){
	struct TreeNode* root = NULL;
	int data;
	char s[15];
	while(1){
		scanf("%s", s);
		if(strcmp(s,"insert") == 0){
			scanf("%d", &data);
			root = insertNodeToBST(root, data);
		}else if(s[0] == '#') 
			break;
	}
	preOrderTraversal(root);
	return 0;
}
