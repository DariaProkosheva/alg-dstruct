#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#pragma warning (disable:4996)
/*
 * CPU: Intel(R) Core(TM) i5-1035G1 CPU 1.00 GHz
 * RAM: 8 GB
 * SSD: 119 GB
 *
 * Вершины: 15000
 * Stress Test
 * Память: 2,18
 * BFS: 3.363129 sec
 */
int** CreateMatrix(int size) {
    char sym;
    int curr;
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == NULL) {
        printf("Memmory error");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        sym = ' ';
        while (sym == ' ') {
            scanf("%i%c", &curr, &sym);
            if (curr != i) {
                matrix[i][curr] = 1;
                matrix[curr][i] = 1;
            }
        }
    }
    return matrix;
}
void BFS(int** matrix, int* vis, int size) {
    vis[0] = 0;
    for (int k = 0; k < size; k++)
        matrix[k][0] = 0;
    int* tail, *curr;
    tail = vis + 1;
    curr = vis;
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < size && tail < vis + size; j++) {
            if (matrix[*curr][j] == 1) {
                *tail = j;
                tail += 1;
                for (int k = 0; k < size; k++)
                    matrix[k][j] = 0;
            }
        }
        curr++;
    }
    int* cur = vis;
    while (vis != tail) {
        printf("%i ", *vis);
        vis++;
    }
}
void Test() {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER start, end;
    srand(time(NULL));
    int size = 15000;
    int* vis = (int*)malloc(sizeof(int) * size * size);
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 2;
        }
    }
    QueryPerformanceCounter(&start);
    BFS(matrix, vis, size);
    QueryPerformanceCounter(&end);
    printf("Working time %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
}
int main() {
  int size;
  scanf("%i", &size);
  int* vis = (int*)malloc(sizeof(int) * size * size);
  int** matrix = CreateMatrix(size);
    /*for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%i ", matrix[i][j]);
        }
        printf("\n"); 
    }*/
  BFS(matrix, vis, size);
   //Test();
}