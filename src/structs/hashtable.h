#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "str.h"


typedef struct TableEntry {
    bool has;
    str  key;
} TableEntry;

typedef struct HashTable {
    void* data;
    TableEntry* track;
    size_t cap;
    size_t size;
} HashTable;


typedef struct HashTableIter {
    HashTable* inner;
    size_t index;
} HashTableIter;

typedef struct TablePair {
    str key;
    void* val;
} TablePair;


HashTable hashtable_new(size_t size);
HashTable hashtable_with_hasher(size_t size, size_t(*hasher)(void*));
void hashtable_free(HashTable* self);
void hashtable_set(HashTable* self, const str* key, void* val);
void* hashtable_get(HashTable* self, const str* key);
void hashtable_remove(HashTable* self, const str* key);

HashTableIter hashtable_iter(HashTable* self);
bool hashtable_next(HashTableIter* self, TablePair* output);


#define hashtable(T) hashtable_new(sizeof(T))


#endif
