#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree {
	char* word;
	int size;
	struct tree* left;
	struct tree* right;
} tree;

tree* CreateTree(void) {
	tree* Tree = (tree*)malloc(sizeof(tree));
	if (Tree == NULL) {
		printf("MEMMORY_ERROR");
		return NULL;
	}
	Tree->left = NULL;
	Tree->right = NULL;
	return Tree;
}

void DestroyTree(tree* root) {
	if (root == NULL)
		return;
	else {
		DestroyTree(root->left);
		DestroyTree(root->right);
	}
	free(root);
	return;
}

int FindWidth(tree* root) {
	int width = 0;
	if (root == NULL)
		return width;
	else {
		int left = FindWidth(root->left);
		//printf("%d ", left);
		width += left;
		int right = FindWidth(root->right);
		//printf("%d", right);
		width += right;
		width += strlen(root->word);
		root->size = width;
		//printf("%d", width);
	}
	return width;
}

void TreePrint(tree* tree, int n) {
	if (tree != NULL)
	{
		TreePrint(tree->right, n + 2);
		for (int i = 0; i < n; i++)
			printf(" ");
		printf("%s\n", tree->word);
		for (int i = 0; i < n; i++)
			printf(" ");
		printf("%i\n", tree->size);
		TreePrint(tree->left, n + 2);
	}
	else
		return;
}

int main(void) {
	tree* Node1 = CreateTree();
	tree* Node2 = CreateTree();
	tree* Node3 = CreateTree();
	Node1->word = "hello";
	Node2->word = "hi";
	Node3->word = "privet";
	Node1->left = Node2;
	Node1->right = Node3;
	FindWidth(Node1);
	TreePrint(Node1, 0);
	return 0;
}