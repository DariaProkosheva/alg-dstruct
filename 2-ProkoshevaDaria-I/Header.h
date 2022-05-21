#pragma once

typedef struct chains {
    char* value;
    struct chains* next;
} chains;

chains* ChainSearch(chains* chain, char* str);
chains* ChainRemove(chains* chain, char* str);
chains* ChainAdd(chains* chain, char* str);
void ChainPrint(chains* chain);
void ChainDestroy(chains* chain);
int ChainCount(chains* chain);

typedef struct hash_map_items {
    char is_filled;
    chains* chain;
}hash_map_items;

typedef struct hash_map {
    hash_map_items* items;
    uint32_t size;
}hash_map;

hash_map* MapInit(hash_map* map);
void MapAdd(hash_map* map, char* str);
void MapRemove(hash_map* map, char* str);
char MapSearch(hash_map* map, char* str);
void MapDestroy(hash_map* map);
void MapPrint(hash_map* map);
char CheckCollision(hash_map* map, char* str);
void CreateCRCtable(void);
unsigned int GetCRC32(void* buffer, unsigned int length);
int BufferLength(char* buffer);
unsigned int CRC32_table[256];