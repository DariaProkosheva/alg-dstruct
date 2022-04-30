#pragma once

typedef struct tree_t {
    int s;
    int key[3];
    struct tree_t* one;
    struct tree_t* two;
    struct tree_t* three;
    struct tree_t* four;
    struct tree_t* parent;

} tree_t;

char Find(int value, int* key, int s);
void Swap(int* x, int* y);
void Sort2(int* x, int* y);
void Sort3(int* x, int* y, int* z);
void SortKeys(int s, int* key);
tree_t* CreateNode(int value);
tree_t* CreateNode2(int value, tree_t* one, tree_t* two, tree_t* three, tree_t* four, tree_t* parent);
void AddKey(int value, tree_t* treeNode);
void RemoveKeyFromNode(int value, tree_t* treeNode);
void BecomeNode2(int value, int* key, tree_t* treeNode, tree_t* one, tree_t* two);
char isLeaf(tree_t* tree);
tree_t* Split(tree_t* item);
tree_t* AddNode(tree_t* tree, int value);
tree_t* Search(tree_t* tree, int value);
tree_t* FindMinimum(tree_t* tree);
tree_t* Merge(tree_t* leaf);
tree_t* Redistribute(tree_t* leaf);
tree_t* Fix(tree_t* leaf);
tree_t* RemoveNode(tree_t* tree, int value);
void DestroyTree(tree_t* t);
void PrintTree(tree_t* tree);