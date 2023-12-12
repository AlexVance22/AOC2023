#ifndef ALLOC_STRING_H
#define ALLOC_STRING_H


#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;


typedef struct str {
    char* buf;
    size_t len;
} str;
typedef struct String {
    str inner;
    size_t cap;
} String;
typedef struct StrSplit {
    str src;
    size_t idx;
    bool end;
} StrSplit;

bool split_next(StrSplit* self, str* next);


String string_new();
String string_with_capacity(size_t cap);
String string_from(char* src);
String string_from_str(const str* src);
String string_copy(const String* src);
String string_move(String* src);
void string_clear(String* self);
void string_free(String* self);

void string_push_char(String* self, char c);
void string_push_chars(String* self, const char* src);
void string_push_str(String* self, str src);
void string_push_string(String* self, const String* src);
void string_remove(String* self, size_t idx);

str string_remove_prefix(const String* self, const str* prefix);
str string_remove_suffix(const String* self, const str* suffix);
int string_find(const String* self, const str* val);
bool string_contains(const String* self, const str* val);
String string_replace(const String* self, const str* before, const str* after);
StrSplit string_split(String* self);

str string_as_str(String* self);
char* string_as_raw(String* self);
size_t string_len(const String* self);
bool string_eq(const String* self, const String* other);
void string_print(const String* self);
int string_to_int(const String* self);


#define STR(s) (str){ .buf = s, .len = sizeof(s) - 1 }

str str_remove_prefix(const str* self, const str* prefix);
str str_remove_suffix(const str* self, const str* suffix);
int str_find(const str* self, const str* val);
bool str_contains(const str* self, const str* val);
String str_replace(const str* self, const str* before, const str* after);
StrSplit str_split(const str* self);

bool str_eq(const str* self, const str* other);
void str_print(const str* self);
int64_t str_to_int(const str* self);


#endif
#ifdef STRING_IMPL

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


bool split_next(StrSplit* self, str* next) {
    if (self->end) { return false; }
    const size_t begin = self->idx;
    bool await = false;

    for (; self->idx < self->src.len; self->idx++) {
        const char c = self->src.buf[self->idx];
        if (!await) {
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                next->buf = self->src.buf + begin;
                next->len = self->idx - begin;
                await = true;
            }
        } else {
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                return true;
            }
        }
    }

    next->buf = self->src.buf + begin;
    next->len = self->idx - begin;
    self->end = true;
    return true;
}


String string_new() {
    String res;
    res.cap = 4;
    res.inner.buf = (char*)calloc((4 + 1), sizeof(char));
    res.inner.len = 0;
    return res;
}

String string_with_capacity(size_t cap) {
    String res;
    res.cap = cap;
    res.inner.buf = (char*)calloc(cap, sizeof(char));
    res.inner.len = 0;
    return res;
}

String string_from(char* src) {
    String res;
    res.inner.buf = strdup(src);
    res.inner.len = strlen(src);
    res.cap = res.inner.len;
    return res;
}

String string_from_str(const str* src) {
    String res;
    res.cap = src->len;
    res.inner.buf = (char*)malloc(src->len * sizeof(char));
    res.inner.len = src->len;
    memcpy(res.inner.buf, src->buf, src->len * sizeof(char));
    return res;
}

String string_copy(const String* src) {
    String res;
    res.cap = src->cap;
    res.inner.buf = strdup(src->inner.buf);
    res.inner.len = src->inner.len;
    return res;
}

String string_move(String* src) {
    String res;
    res.cap = src->cap;
    res.inner.buf = src->inner.buf;
    res.inner.len = src->inner.len;
    src->inner.buf = NULL;
    return res;
}

void string_clear(String* self) {
    free(self->inner.buf);
    self->cap = 4;
    self->inner.buf = (char*)calloc((4 + 1), sizeof(char));
    self->inner.len = 0;
}

void string_free(String* self) {
    free(self->inner.buf);
}

void _string_grow(String* self) {
    self->cap *= 2;
    char* temp = (char*)calloc(self->cap, sizeof(char));
    strncpy(temp, self->inner.buf, self->inner.len);
    free(self->inner.buf);
    self->inner.buf = temp;
}

void string_push_char(String* self, char c) {
    if (self->inner.len + 1 >= self->cap) {
        _string_grow(self);
    }
    self->inner.buf[self->inner.len] = c;
    self->inner.len += 1;
}

void string_push_chars(String* self, const char* src) {
    const size_t len = strlen(src);
    if (self->inner.len + len >= self->cap) {
        _string_grow(self);
    }
    strncpy(self->inner.buf + self->inner.len, src, len);
    self->inner.len += len;
}

void string_push_str(String* self, str src) {
    if (self->inner.len + src.len >= self->cap) {
        _string_grow(self);
    }
    strncpy(self->inner.buf + self->inner.len, src.buf, src.len);
    self->inner.len += src.len;
}

void string_push_string(String* self, const String* src) {
    string_push_str(self, src->inner);
}

str string_remove_prefix(const String* self, const str* prefix) {
    return str_remove_prefix(&self->inner, prefix);
}

str string_remove_suffix(const String* self, const str* suffix) {
    return str_remove_suffix(&self->inner, suffix);
}

int string_find(const String* self, const str* pat) {
    return str_find(&self->inner, pat);
}

bool string_contains(const String* self, const str* pat) {
    return str_contains(&self->inner, pat);
}

String string_replace(const String* self, const str* pat, const str* to) {
    return str_replace(&self->inner, pat, to);
}

StrSplit string_split(String* self) {
    return str_split(&self->inner);
}


str string_as_str(String* self) {
    return self->inner;
}

char* string_as_raw(String* self) {
    return self->inner.buf;
}

size_t string_len(const String* self) {
    return self->inner.len;
}

bool string_eq(const String* self, const String* other) {
    return str_eq(&self->inner, &other->inner);
}

void string_print(const String* self) {
    str_print(&self->inner);
}

int string_to_int(const String* self) {
    return str_to_int(&self->inner);
}


str str_remove_prefix(const str* self, const str* prefix) {
    if (str_find(self, prefix) != 0) {
        return *self;
    } else {
        return (str){ self->buf + prefix->len, self->len - prefix->len };
    }
}

str str_remove_suffix(const str* self, const str* suffix) {
    if (str_find(self, suffix) != self->len - suffix->len) {
        return *self;
    } else {
        return (str){ self->buf, self->len - suffix->len };
    }
}

int str_find(const str* self, const str* pat) {
    for (size_t i = 0; i < (self->len - pat->len + 1); i++) {
        if (str_eq(&(str){ self->buf + i, pat->len }, pat )) {
            return i;
        }
    }
    return -1;
}

bool str_contains(const str* self, const str* val) {
    return str_find(self, val) != -1;
}

String str_replace(const str* self, const str* pat, const str* to) {
    String res = string_from_str(self);

    int idx = string_find(&res, pat);
    while (idx != -1) {
        String temp = string_with_capacity(self->len - pat->len + to->len);
        for (size_t i = 0; i < idx; i++) {
            string_push_char(&temp, res.inner.buf[i]);
        }
        for (size_t i = 0; i < to->len; i++) {
            string_push_char(&temp, to->buf[i]);
        }
        for (size_t i = 0; i < (res.inner.len - pat->len - idx); i++) {
            string_push_char(&temp, res.inner.buf[idx + pat->len + i]);
        }
        res = string_move(&temp);
        idx = string_find(&res, pat);
    }

    return res;
}

StrSplit str_split(const str* self) {
    return (StrSplit){ *self, 0, false };
}


bool str_eq(const str* self, const str* other) {
    if (self->len != other->len) {
        return false;
    }
    for (size_t i = 0; i < self->len; i++) {
        if (self->buf[i] != other->buf[i]) {
            return false;
        }
    }
    return true;
}

void str_print(const str* self) {
    fwrite(self->buf, sizeof(char), self->len, stdout);
}

int64_t str_to_int(const str* self) {
    int64_t sum = 0;
    for (size_t i = 0; i < self->len; i++) {
        sum *= 10;
        sum += (int64_t)(self->buf[i] - '0');
    }
    return sum;
}


#endif
