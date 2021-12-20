#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MEMMORY_ERROR 0
#define FILE_ERROR -1
typedef struct node {
    unsigned wag;
    struct node* next;
} node;

unsigned* wag_time;
unsigned W;
unsigned D;
unsigned K;
unsigned N;
node** wag_list;

unsigned curr_time;
unsigned minim_time;
unsigned max_wag_use;
unsigned* wags_left;
unsigned* wags_use;
unsigned* curr_res;
unsigned* curr_best_res;

int ListPush(node** list, unsigned wag);
void ListDestroy(node* list);
void WagListDestroy();
int ReadInputFile(const char* filename);
void WagOne(unsigned wag);
void WagZero(unsigned wag);
void FindBestSolution(unsigned m);
int FindBestSolutionErr();
unsigned WagComposition(const char* fileinput, const char* fileoutput);