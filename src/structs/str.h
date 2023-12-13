#ifndef ALLOC_STRING_H
#define ALLOC_STRING_H

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
int64_t string_to_int(const String* self);


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
