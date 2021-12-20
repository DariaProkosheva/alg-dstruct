#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "D.h"
/*
 * CPU: Intel(R) Core(TM) i5-1035G1 CPU 1.00 GHz
 * RAM: 8 GB
 * SSD: 119 GB
 * Stress Test
*  Time 28.085625
*/

int ListPush(node** list, unsigned wag) {
    node* newnode = (node*)malloc(sizeof(node));
    if (newnode == NULL) {
        printf("MEMMORY ERROR");
        return MEMMORY_ERROR;
    }
    newnode->wag = wag;
    newnode->next = *list;
    *list = newnode;
    return 1;
}

void ListPrint(node* list) {
    while (list != NULL) {
        printf("%i ", list->wag + 1);
        list = list->next;
    }
}

void ListDestroy(node* list) {
    while (list != NULL) {
        node* f = list;
        list = list->next;
        free(f);
    }
}

void WagListDestroy() {
    for (int i = 0; i < W; i++)
        ListDestroy(wag_list[i]);
    free(wag_list);
}

int ReadInputFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Opening file error");
        return FILE_ERROR;
    }
    fscanf(file, "%d %d %d", &W, &D, &K);

    wag_time = (unsigned*)malloc(W * sizeof(unsigned));
    if (wag_time == NULL) {
        fclose(file);
        printf("MEMMORY ERROR");
        return MEMMORY_ERROR;
    }

    wag_list = (node**)calloc(W, sizeof(node*));
    if (wag_list == NULL) {
        free(wag_time);
        fclose(file);
        printf("MEMMORY ERROR");
        return MEMMORY_ERROR;
    }

    for (int i = 0; i < W; i++)
        fscanf(file, "%i ", &wag_time[i]);

    unsigned pair_num = 0;
    fscanf(file, "%i", &pair_num);
    for (unsigned i = 0; i < pair_num; i++) {
        unsigned before = 0, after = 0;
        fscanf(file, "%d %d", &before, &after);
        if (ListPush(&wag_list[after - 1], before - 1) == 0) {
            free(wag_time);
            fclose(file);
            WagListDestroy();
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void WagOne(unsigned wag) {
    wags_use[wag] = 1;
    node* i = wag_list[wag];
    while (i != NULL) {
        wags_left[i->wag] = 1;
        i = i->next;
    }
}

void WagZero(unsigned wag) {
    wags_use[wag] = 0;
    node* i = wag_list[wag];
    while (i != NULL) {
        wags_left[i->wag] = 0;
        i = i->next;
    }
}

void FindBestSolution(unsigned m) {
    if (m >= W - K)
        if (m == max_wag_use && curr_time < minim_time) {
            minim_time = curr_time;
            memcpy(curr_best_res, curr_res, W * sizeof(unsigned));
        }
        else if (m > max_wag_use) {
            max_wag_use = m;
            minim_time = curr_time;
            memcpy(curr_best_res, curr_res, W * sizeof(unsigned));
        }
    if (m < W)
        for (unsigned i = 0; i < W; i++) {
            if (!wags_left[i] && !wags_use[i] && curr_time + wag_time[i] <= D) {
                curr_res[m] = i;
                curr_time += wag_time[i];
                WagOne(i);
                FindBestSolution(m + 1);
                WagZero(i);
                curr_time -= wag_time[i];
            }
        }
}

int FindBestSolutionErr() {
    curr_time = 0;
    minim_time = D + 1;
    max_wag_use = 0;
    curr_res = (unsigned*)malloc(W * sizeof(unsigned));
    if (curr_res == NULL)
        return 0;
    curr_best_res = (unsigned*)malloc(W * sizeof(unsigned));
    if (curr_best_res == NULL) {
        free(curr_res);
        return 0;
    }
    wags_left = (unsigned*)calloc(W, sizeof(unsigned));
    if (wags_left == NULL) {
        free(curr_res);
        free(curr_best_res);
        return 0;
    }
    wags_use = (unsigned*)calloc(W, sizeof(unsigned));
    if (wags_use == NULL) {
        free(curr_res);
        free(curr_best_res);
        free(wags_left);
        return 0;
    }
    FindBestSolution(0);
    free(curr_res);
    free(wags_left);
    free(wags_use);
    return 1;
}

unsigned WagComposition(const char* fileinput, const char* fileoutput) {
    if (ReadInputFile(fileinput) == 0)
        return -2;

    FILE* fileOut = fopen(fileoutput, "w");
    if (fileOut == NULL) {
        printf("Opening file error");
        return FILE_ERROR;
    }

    if (FindBestSolutionErr() == 1) {
        if (max_wag_use > 0) {
            for (int i = 0; i < max_wag_use; i++)
                fprintf(fileOut, "%d ", curr_best_res[i] + 1);
        }
        else
            fprintf(fileOut, "0");
        free(curr_best_res);
        free(wag_time);
        WagListDestroy();
        fclose(fileOut);
        return 0;
    }
    free(wag_time);
    WagListDestroy();
    fclose(fileOut);
    return 1;
}
void StressTest() {
    unsigned WW = 11;
    unsigned DD = 110;
    unsigned KK = 2;
    unsigned NN = 8;
    FILE* fileinput = fopen("stresstest.txt", "w");
    fprintf(fileinput, "%d %d %d\n", WW, DD, KK);
    for (int i = 0; i < WW; i++)
        fprintf(fileinput, "%d ", (rand() % (DD / WW - 1) + 1));
    fprintf(fileinput, "\n");
    int pairs = NN;
    int beforeDelta = pairs > 0 ? WW / NN : 0;
    int before = 1;
    fprintf(fileinput, "%d\n", pairs);
    for (int i = 0; i < pairs; i++) {
        before += beforeDelta;
        int after = rand() % (WW - 1) + 1;
        fprintf(fileinput, "%d %d\n", before, after != before ? after : (after > 1 ? after - 1 : after + 1));
    }
    fclose(fileinput);
}
/*int main(void) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER start, end;
    srand(time(NULL));
    StressTest();
    QueryPerformanceCounter(&start);
    WagComposition("stresstest.txt", "outputtt.txt");
    QueryPerformanceCounter(&end);
    printf("Working time %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
    return 0;
}*/