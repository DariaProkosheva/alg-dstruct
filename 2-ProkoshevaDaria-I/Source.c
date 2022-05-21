#define _CRT_SECURE_NO_WARNINGS

#include <inttypes.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

#define SIZE 500000
#define TRUE 1
#define FALSE 0

hash_map* MapInit(hash_map* map) {

    if (map == NULL) {
        map = (hash_map*)malloc(sizeof(hash_map));

        if (map == NULL)
            return NULL;

        map->size = SIZE;
        hash_map_items* tmp_items = (hash_map_items*)malloc(map->size * sizeof(hash_map_items));

        if (tmp_items == NULL)
            return NULL;

        map->items = tmp_items;

        for (int i = 0; i < map->size; i++) {
            map->items[i].is_filled = FALSE;
            map->items[i].chain = NULL;
        }

        CreateCRCtable();

        return map;
    }

    return NULL;
}

int BufferLength(char* buffer) {
    int len = 0;

    if (buffer == NULL)
        return 0;

    while (buffer[len] != '\0')
        len++;

    return len;
}

void MapAdd(hash_map* map, char* string) {

    if (map != NULL && map->items != NULL && string != NULL) {
        if (MapSearch(map, string)) {
            return;
        }

        uint32_t hash = GetCRC32(string, BufferLength(string));
        uint32_t index = hash % SIZE;

        map->items[index].chain = ChainAdd(map->items[index].chain, string);
        map->items[index].is_filled = TRUE;
    }
}

int ChainCount(chains* chain) {
    int count = 0;

    if (chain == NULL)
        return count;

    while (chain != NULL) {
        count++;
        chain = chain->next;
    }

    return count;
}

void MapRemove(hash_map* map, char* str) {
    if (map != NULL && map->items != NULL && str != NULL) {
        if (!MapSearch(map, str))
            return;

        uint32_t hash = GetCRC32(str, BufferLength(str));
        uint32_t index = hash % SIZE;

        map->items[index].chain = ChainRemove(map->items[index].chain, str);

        if (ChainCount(map->items[index].chain) == 0)
            map->items[index].is_filled = FALSE;
    }
}

char CheckCollision(hash_map* map, char* str) {
    if (map != NULL && map->items != NULL && str != NULL) {
        uint32_t hash = GetCRC32(str, BufferLength(str));
        uint32_t index = hash % SIZE;

        if (map->items[index].is_filled == FALSE)
            return FALSE;

        if (map->items[index].is_filled && strcmp(map->items[index].chain->value, str) != 0)
            return TRUE;
    }

    return FALSE;
}

char MapSearch(hash_map* map, char* str) {
    if (map != NULL && map->items != NULL && str != NULL) {
        uint32_t hash = GetCRC32(str, BufferLength(str));
        uint32_t index = hash % SIZE;

        if (map->items[index].is_filled == FALSE)
            return FALSE;

        if (ChainSearch(map->items[index].chain, str) != NULL)
            return TRUE;
    }

    return FALSE;
}

void MapDestroy(hash_map* map) {
    if (map == NULL) {
        return;
    }
    else {
        for (int i = 0; i < map->size; i++)
            if (map->items[i].is_filled)
                ChainDestroy(map->items[i].chain);

        free(map->items);
    }

    free(map);
}

void MapPrint(hash_map* map) {
    if (map != NULL)
        for (int i = 0; i < map->size; i++)
            if (map->items[i].is_filled)
                ChainPrint(map->items[i].chain);
}

void CreateCRCtable(void) {
    uint32_t CRC_32;
    unsigned int index = 0;
    unsigned int bit = 0;

    for (index = 0; index < 256; index++) {
        CRC_32 = index;

        for (bit = 0; bit < 8; bit++)
            if (CRC_32 & 1)
                CRC_32 = (CRC_32 >> 1) ^ (0xEDB88320);
            else
                CRC_32 = CRC_32 >> 1;

        CRC32_table[index] = CRC_32;
    }
}

unsigned int GetCRC32(void* buffer, unsigned int buffer_length) {
    uint32_t CRC32_value = 0xffffffff;
    unsigned char* tmp_buffer = (unsigned char*)buffer;

    while (buffer_length--)
        CRC32_value = CRC32_table[(CRC32_value ^ *tmp_buffer++) & 0xff] ^ (CRC32_value >> 8);

    return (CRC32_value ^ 0xffffffff);
}

chains* ChainSearch(chains* chain, char* str) {
    if (chain == NULL)
        return NULL;

    while (chain != NULL) {
        if (strcmp(chain->value, str) == 0)
            return chain;

        chain = chain->next;
    }

    return NULL;
}

chains* ChainAdd(chains* chain, char* str) {
    if (chain == NULL) {
        chains* newSlot = (chains*)malloc(sizeof(chains));

        if (newSlot != NULL)
            chain = newSlot;

        chain->value = (char*)malloc(sizeof(char) * BufferLength(str));

        if (chain->value != NULL)
            strcpy(chain->value, str);

        chain->next = NULL;

        return chain;
    }
    else {
        chains* tmp = chain;

        while (tmp->next != NULL)
            tmp = tmp->next;

        chains* newSlot = (chains*)malloc(sizeof(chains));
        newSlot->value = (char*)malloc(sizeof(char) * BufferLength(str));

        if (newSlot != NULL && newSlot->value != NULL) {
            tmp->next = newSlot;
            newSlot->next = NULL;
            strcpy(newSlot->value, str);
        }

        return chain;
    }
}

chains* ChainRemove(chains* chain, char* str) {
    if (chain == NULL)
        return NULL;

    chains* removeSlot = ChainSearch(chain, str);

    if (chain == removeSlot) {
        chain = chain->next;
        free(removeSlot);

        return chain;
    }
    else {
        chains* tmp = chain;

        while (tmp->next != removeSlot)
            tmp = tmp->next;

        tmp->next = removeSlot->next;
        free(removeSlot->value);
        free(removeSlot);
    }

    return chain;
}

void ChainDestroy(chains* chain) {
    chains* remove = chain;

    while (chain != NULL) {
        chain = remove->next;
        free(remove);
        remove = chain;
    }
}

void ChainPrint(chains* chain) {
    if (chain == NULL)
        return;

    while (chain != NULL) {
        printf("%s ", chain->value);
        chain = chain->next;
    }
}

int main(void) {

    char command;
    hash_map* map = NULL;
    map = MapInit(map);
    char value[100] = { '\0' };

    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q')
            getchar();

        fgets(value, sizeof(value), stdin);

        switch (command) {
        case 'a':
            MapAdd(map, value);
            break;

        case 'r':
            MapRemove(map, value);
            break;

        case 'f':
            if (MapSearch(map, value))
                puts("yes");
            else
                puts("no");

            break;

        case 'p':
            MapPrint(map);
            putchar('\n');
            break;

        case 'q':
            MapDestroy(map);
            return 0;
        }
    }
}