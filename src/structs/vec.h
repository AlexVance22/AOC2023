#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>


typedef struct Vec {
    void* buf;
    size_t len;
    size_t cap;
    size_t size;
} Vec;

Vec vec_new(size_t size);
Vec vec_with_capacity(size_t cap, size_t size);
Vec vec_copy(const Vec* src);
Vec vec_move(Vec* src);
void vec_clear(Vec* self);
void vec_free(Vec* self);

void vec_push(Vec* self, const void* e);
// void vec_remove(Vec* self, size_t idx);

void* vec_as_raw(Vec* self);
size_t vec_len(const Vec* self);
bool vec_eq(const Vec* self, const Vec* other);

#define vec(T) vec_new(sizeof(T))
#define vec_cap(n, T) vec_with_capacity(n, sizeof(T))
#define vec_get(v, i) ((char*)v.buf + i * v.size)


#endif
