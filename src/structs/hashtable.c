#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "str.h"


size_t string_hash(str s) {
    uint64_t hash = 5381;
    for (size_t i = 0; i < s.len; i++) {
        hash = ((hash << 5) + hash) + s.buf[i];
    }
    return hash;
}


typedef struct TableEntry {
    bool has;
    str  key;
} TableEntry;

typedef struct HashTable {
    size_t cap;
    size_t size;
    void* data;
    TableEntry* track;
} HashTable;

const size_t HASHTABLE_INIT_CAP = 20;


HashTable hashtable_new(size_t size) {
    HashTable result;
    result.cap = HASHTABLE_INIT_CAP;
    result.size = size;
    result.data =               calloc(HASHTABLE_INIT_CAP, size);
    result.track = (TableEntry*)calloc(HASHTABLE_INIT_CAP, sizeof(TableEntry));
    for (size_t i = 0; i < HASHTABLE_INIT_CAP; i++) {
        result.track[i].has = false;
    }
    return result;
}

void hashtable_free(HashTable* self) {
    free(self->data);
    free(self->track);
}

void _hashtable_grow(HashTable* self) {
    self->cap *= 2;
    self->data =               realloc(self->data,  self->size         * self->cap);
    self->track = (TableEntry*)realloc(self->track, sizeof(TableEntry) * self->cap);
}

bool _hashtable_set_if_matches(HashTable* self, const str* key, void* val, size_t index) {
    if (self->track[index].has) {
        if (str_eq(&self->track[index].key, key)) {
            self->track[index].has = true;
            self->track[index].key = *key;
            memcpy(self->data + index * self->size, val, self->size);
            return true;
        }
        return false;
    } else  {
        self->track[index].has = true;
        self->track[index].key = *key;
        memcpy(self->data + index * self->size, val, self->size);
        return true;
    }
}

void hashtable_set(HashTable* self, const str* key, void* val) {
    const size_t index = string_hash(*key) % self->cap;

    if (_hashtable_set_if_matches(self, key, val, index)) {
        return;
    }
    for (size_t i = index + 1; i < self->cap; i++) {
        if (_hashtable_set_if_matches(self, key, val, i)) {
            return;
        }
    }
    for (size_t i = 0; i < index; i++) {
        if (_hashtable_set_if_matches(self, key, val, i)) {
            return;
        }
    }

    _hashtable_grow(self);
    hashtable_set(self, key, val);
}

void* hashtable_get(HashTable* self, const str* key) {
    const size_t index = string_hash(*key) % self->cap;

    if (self->track[index].has && str_eq(&self->track[index].key, key)) {
        return (char*)self->data + index * self->size;
    } else {
        for (size_t i = index; i < self->cap; i++) {
            if (self->track[i].has && str_eq(&self->track[i].key, key)) {
                return (char*)self->data + i * self->size;
            }
        }
        for (size_t i = 0; i < index; i++) {
            if (self->track[i].has && str_eq(&self->track[i].key, key)) {
                return (char*)self->data + i * self->size;
            }
        }
    }

    return NULL;
}

