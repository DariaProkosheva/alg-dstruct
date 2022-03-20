#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

Node* CreateNode(int key, Node* parent, char col) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		printf("Memmory error");
		exit(1);
	}
	node->key = key;
	node->color = col;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}

void RightRotate(Node* tree, Node* node) {
	Node* left = node->left;
	node->left = left->right;
	if (node->left != NULL)
		node->left->parent = node;
	left->parent = node->parent;
	if (node->parent == NULL)
		tree = left;
	else if (node == node->parent->left)
		node->parent->left = left;
	else
		node->parent->right = left;
	left->right = node;
	node->parent = left;
}

void LeftRotate(Node* tree, Node* node) {
	Node* right = node->right;
	node->right = right->left;
	if (node->right == NULL)
		node->right->parent = node;
	right->parent = node->parent;
	if (node->parent != NULL)
		tree = right;
	else if (node == node->parent->left)
		node->parent->left = right;
	else
		node->parent->right = right;
	right->left = node;
	node->parent = right;
}

Node* FixUp(Node* tree, Node* x) {
	while (x != tree && x->parent->color == RED) {
		if (x->parent == x->parent->parent->left) {
			Node* y = x->parent->parent->right;
			if (y != NULL && y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					LeftRotate(tree, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				RightRotate(tree, x->parent->parent);
			}
		}
		else {
			Node* y = x->parent->parent->left;
			if (y != NULL && y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					RightRotate(tree, x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				LeftRotate(tree, x->parent->parent);
			}
		}
	}
	tree->color = BLACK;
	return tree;
}

Node* Insert(Node* tree, int key) {
	if (tree == NULL)
		tree = CreateNode(key, NULL, BLACK);
	else {
		Node* cur = tree;
		Node* par = NULL;
		while (cur != NULL) {
			if (cur->key == key)
				return tree;
			par = cur;
			if (key < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}
		Node* node = (Node*)malloc(sizeof(Node));
		if (node == NULL) {
			printf("Memmory error");
			exit(1);
		}
		node = CreateNode(key, par, RED);
		if (par == NULL)
			tree = node;
		else {
			if (key < par->key)
				par->left = node;
			else
				par->right = node;
		}
		tree = FixUp(tree, node);
		}
	return tree;
};

Node* DeleteFixup(Node* tree, Node* x) {
	while (x != tree && x->color == BLACK) {
		if (x->parent->right != NULL && x == x->parent->left) {
			Node* y = x->parent->right;
			if (y->color == RED) {
				y->color = BLACK;
				x->parent->color = RED;
				LeftRotate(tree, x->parent);
				y = x->parent->right;
			}
			if (y->left != NULL && y->right != NULL && y->left->color == BLACK && y->right->color == BLACK) {
				y->color = RED;
				x = x->parent;
			}
			else {
				if (y->left != NULL && y->right != NULL && y->right->color == BLACK) {
					y->left->color = BLACK;
					y->color = RED;
					RightRotate(tree, y);
					y = x->parent->right;
				}

				if (y->right != NULL) {
					y->color = x->parent->color;
					x->parent->color = BLACK;
					y->right->color = BLACK;
					LeftRotate(tree, x->parent);
				}
				x = tree;
			}
		}
		else if (x->parent->left) {
			Node* y = x->parent->left;
			if (y->color == RED) {
				y->color = BLACK;
				x->parent->color = RED;
				RightRotate(tree, x->parent);
				y = x->parent->left;
			}

			if (y->left != NULL && y->right != NULL && y->right->color == BLACK && y->left->color == BLACK) {
				y->color = RED;
				x = x->parent;
			}
			else {

				if (y->left != NULL && y->right != NULL && y->left->color == BLACK) {
					y->right->color = BLACK;
					y->color = RED;
					LeftRotate(tree, y);
					y = x->parent->left;
				}

				if (y->left) {
					y->color = x->parent->color;
					x->parent->color = BLACK;
					y->left->color = BLACK;
					RightRotate(tree, x->parent);
				}
				x = tree;
			}
		}
	}
	x->color = BLACK;
	return tree;
}

Node* Delete(Node* tree, int key) {
	Node* cur = tree;
	Node* x = NULL;
	while (cur != NULL) {
		if (key == cur->key) {
			x = cur;
			break;
		}
		else 
			if (key < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
	}
	if (x == NULL) 
		return tree;
	Node* y = NULL;
	if (x->left == NULL || x->right == NULL) {
		y = x;
	}
	else {
		y = x->right;
		while (y->left)
			y = y->left;
	}
	Node* y_child = NULL;
	if (y->left) 
		y_child = y->left;

	else 
		y_child = y->right;

	if (y_child) 
		y_child->parent = y->parent;

	if (y->parent) {
		if (y == y->parent->left)
			y->parent->left = y_child;
		else 
			y->parent->right = y_child;
	}
	else
		tree = y_child;
	if (y != x)
		x->key = y->key;
	if (y->color == BLACK && y_child != NULL) 
		tree = DeleteFixup(tree, y_child);
	if (y != NULL) 
		free(y);
	return tree;
}

//0.000005700000095 - Insert RB tree
//0.000014800000031- Insert Binary tree 
//0.000001200000014 - Search RB tree
//0.000001100000013 - Search Binary

//Добавление в красно-черное дерево происходит быстрее, чем в бинарное, однако поиск в последнем 
//занимает чуть меньше времени, поиск по времени в этих деревьях примерно одинаков

void Search(Node* root, int key) {
	Node* cur = root;
	while (cur != NULL) {
		if (cur->key == key) {
			//printf("in");
			return;
		}
		else {
			if (key < cur->key)
				cur = cur->left;
			else
				cur = cur->right;
		}

	}
    //printf("out");
}