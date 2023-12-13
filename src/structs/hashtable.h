#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct str str;
typedef struct TableEntry TableEntry;
typedef struct HashTable {
    size_t cap;
    size_t size;
    void* data;
    TableEntry* track;
} HashTable;


HashTable hashtable_new(size_t size);
void hashtable_free(HashTable* self);
void hashtable_set(HashTable* self, const str* key, void* val);
void* hashtable_get(HashTable* self, const str* key);

#define hashtable(T) hashtable_new(sizeof(T))


#endif
