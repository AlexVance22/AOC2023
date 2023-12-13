#include "vec.h"
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

void vec_push(Vec* self, const void* e) {
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

