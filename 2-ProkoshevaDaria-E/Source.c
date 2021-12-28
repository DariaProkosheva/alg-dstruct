#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct tree {
	char* word;
	int size;
	struct tree* left;
	struct tree* right;
} tree;

tree* CreateTree(char* word) {
	tree* Tree = (tree*)malloc(sizeof(tree));
	if (Tree == NULL) {
		printf("MEMMORY_ERROR");
		return NULL;
	}
	Tree->word = word; 
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
	free(root->word);
	free(root);
	return;
}
void AddElement(tree** Tree, char* word) {
	tree* node = CreateTree(word);
	if (node == NULL) {
		printf("MEMMORY_ERROR");
		return NULL;
	}
	if (*Tree == NULL) {
		*Tree = node;
		return;
	}
	tree* t = *Tree;
	int num = 0;
	while (t != NULL) {
		if ((num = strcmp((node->word), (t->word))) < 0) {
			if (t->right != NULL)
				t = t->right;
			else {
				t->right = node;
				return;
			}
		}
		else
			if (num == 0) {
				DestroyTree(node);
				return;
			}
			else
				if (t->left != NULL)
					t = t->left;
				else {
					t->left = node;
					return;
				}
	}

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
		TreePrint(tree->left, n + 2);
		for (int i = 0; i < n; i++)
			printf(" ");
		printf("%s\n", tree->word);
		for (int i = 0; i < n; i++)
			printf(" ");
		printf("%i\n", tree->size);
		TreePrint(tree->right, n+2);
	}
	else
		return;
}

int main(void) {
	tree* Tree = NULL;
	AddElement(&Tree, "hello");
	AddElement(&Tree, "hi");
	AddElement(&Tree, "privet");
	FindWidth(Tree);
	TreePrint(Tree, 0);
	return 0;
}