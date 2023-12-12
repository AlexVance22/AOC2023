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

void vec_push(Vec* self, const void* src);
// void vec_remove(Vec* self, size_t idx);

void* vec_as_raw(Vec* self);
size_t vec_len(const Vec* self);
bool vec_eq(const Vec* self, const Vec* other);

#define vec(T) vec_new(sizeof(T))
#define vec_cap(n, T) vec_with_capacity(n, sizeof(T))
#define vec_get(v, i) ((char*)v.buf + i * v.size)


#endif
#ifdef VECTOR_IMPL

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Vec vec_new(size_t size) {
    Vec res;
    res.cap = 4;
    res.buf = calloc(4, size);
    res.len = 0;
    res.size = size;
    return res;
}

Vec vec_with_capacity(size_t cap, size_t size) {
    Vec res;
    res.cap = 4;
    res.buf = calloc((cap), size);
    res.len = 0;
    res.size = size;
    return res;
}

Vec vec_copy(const Vec* src) {
    Vec res;
    res.cap = src->cap;
    res.buf = calloc(src->cap, src->size);
    memcpy(res.buf, src->buf, src->len * src->size);
    res.len = src->len;
    res.size = src->size;
    return res;
}

Vec vec_move(Vec* src) {
    Vec res;
    res.cap = src->cap;
    res.buf = src->buf;
    res.len = src->len;
    res.size = src->size;
    src->buf = NULL;
    return res;
}

void vec_clear(Vec* self) {
    free(self->buf);
    self->cap = 4;
    self->buf = calloc(4, self->size);
    self->len = 0;
}

void vec_free(Vec* self) {
    free(self->buf);
}

void _vec_grow(Vec* self) {
    self->cap *= 2;
    void* temp = calloc(self->cap, self->size);
    memcpy(temp, self->buf, self->len * self->size);
    free(self->buf);
    self->buf = temp;
}

void vec_push(Vec* self, void* e) {
    if (self->len + 1 >= self->cap) {
        _vec_grow(self);
    }
    memcpy((char*)self->buf + (self->len * self->size), e, self->size);
    self->len += 1;
}


void* vec_as_raw(Vec* self) {
    return self->buf;
}

size_t vec_len(const Vec* self) {
    return self->len;
}

bool vec_eq(const Vec* self, const Vec* other) {
    if (self->len != other->len) {
        return false;
    }
    if (self->size != other->size) {
        return false;
    }
    for (size_t i = 0; i < self->len * self->size; i++) {
        if (((char*)self->buf)[i] != ((char*)other->buf)[i]) {
            return false;
        }
    }
    return true;
}


#endif
