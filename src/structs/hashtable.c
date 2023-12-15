#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "hashtable.h"


static size_t string_hash(str s) {
    uint64_t hash = 5381;
    for (size_t i = 0; i < s.len; i++) {
        hash = ((hash << 5) + hash) + s.buf[i];
    }
    return hash;
}

const size_t HASHTABLE_INIT_CAP = 20;


HashTable hashtable_new(size_t size) {
    HashTable result = (HashTable){
        .data =               calloc(HASHTABLE_INIT_CAP, size),
        .track = (TableEntry*)calloc(HASHTABLE_INIT_CAP, sizeof(TableEntry)),
        .cap = HASHTABLE_INIT_CAP,
        .size = size
    };
    for (size_t i = 0; i < HASHTABLE_INIT_CAP; i++) {
        result.track[i].has = false;
    }
    return result;
}

HashTable hashtable_with_hasher(size_t size, size_t(*hasher)(void*)) {
    HashTable result = (HashTable){
        .data =               calloc(HASHTABLE_INIT_CAP, size),
        .track = (TableEntry*)calloc(HASHTABLE_INIT_CAP, sizeof(TableEntry)),
        .cap = HASHTABLE_INIT_CAP,
        .size = size
    };
    for (size_t i = 0; i < HASHTABLE_INIT_CAP; i++) {
        result.track[i].has = false;
    }
    return result;
}

void hashtable_free(HashTable* self) {
    free(self->data);
    free(self->track);
}


static void _hashtable_grow(HashTable* self) {
    size_t cap = self->cap;
    self->cap *= 2;
    self->data =               realloc(self->data,  self->size         * self->cap);
    self->track = (TableEntry*)realloc(self->track, sizeof(TableEntry) * self->cap);
    for (size_t i = cap; i < self->cap; i++) {
        self->track[i].has = false;
    }
}

static size_t _hashtable_index_of(HashTable* self, const str* key) {
    const size_t index = string_hash(*key) % self->cap;

    for (size_t i = 0; i < self->cap; i++) {
        const size_t j = (index + i) % self->cap;
        if (self->track[j].has && str_eq(&self->track[j].key, key)) {
            return j;
        }
    }

    return self->cap;
}

static size_t _hashtable_index_of_or_empty(HashTable* self, const str* key) {
    const size_t index = string_hash(*key) % self->cap;

    for (size_t i = 0; i < self->cap; i++) {
        const size_t j = (index + i) % self->cap;
        if ((self->track[j].has && str_eq(&self->track[j].key, key)) || !self->track[j].has) {
            return j;
        }
    }

    return self->cap;
}


void hashtable_set(HashTable* self, const str* key, void* val) {
    size_t index = _hashtable_index_of_or_empty(self, key);
    if (index == self->cap) {
        _hashtable_grow(self);
        index = _hashtable_index_of_or_empty(self, key);
    }
    self->track[index].has = true;
    self->track[index].key = *key;
    memcpy((char*)self->data + (index * self->size), val, self->size);
}

void* hashtable_get(HashTable* self, const str* key) {
    const size_t index = _hashtable_index_of(self, key);
    if (index == self->cap) {
        return NULL;
    }
    return (char*)self->data + index * self->size;
}

void hashtable_remove(HashTable* self, const str* key) {
    const size_t index = _hashtable_index_of(self, key);
    if (index == self->cap) {
        return;
    }
    self->track[index].has = false;
}


HashTableIter hashtable_iter(HashTable* self) {
    return (HashTableIter){
        .inner = self,
        .index = 0,
    };
}

bool hashtable_next(HashTableIter* self, TablePair* output) {
    for (size_t i = self->index; i < self->inner->cap; i++) {
        if (self->inner->track[i].has) {
            self->index = i + 1;
            output->key = self->inner->track[i].key;
            output->val  = (char*)self->inner->data + i * self->inner->size;
            return true;
        }
    }

    return false;
}

