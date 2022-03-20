#pragma once
enum Color {
	BLACK,
	RED
};

typedef struct Node {
	int key;
	enum Color color;
    struct Node* parent;
	struct Node* left;
	struct Node* right;
} Node;

Node* CreateNode(int key, Node* parent, char col);
void RightRotate(Node* tree, Node* node);
void LeftRotate(Node* tree, Node* node);
Node* FixUp(Node* tree, Node* x);
Node* Insert(Node* tree, int key);
Node* DeleteFixup(Node* tree, Node* x);
Node* Delete(Node* tree, int key);
void Search(Node* root, int key);
