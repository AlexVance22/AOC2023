#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "str.h"
#include "vec.h"


char* get_file(const char* file);


typedef struct Lines {
    char* src;
    char* last;
} Lines;

Lines lines(char* src);
Lines get_file_lines(const char* file);
void free_file_lines(Lines* file);
bool lines_next(Lines* lines, str* dest);
void lines_reset(Lines* lines);


bool is_digit(char val);
int to_digit(char val);


#ifdef UTILS_IMPL
#define STRING_IMPL
#define VECTOR_IMPL
#include "str.h"

char* get_file(const char* file) {
    FILE* f = NULL;
    fopen_s(&f, file, "r");

    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buf = (char*)calloc(size + 1, sizeof(char));
    fread(buf, size, sizeof(char), f);
    fclose(f);

    return buf;
}


Lines lines(char* src) {
    Lines result;
    result.src = src;
    result.last = src;
    return result;
}

Lines get_file_lines(const char* file) {
    return lines(get_file(file));
}

void free_file_lines(Lines* file) {
    free(file->src);
}

bool lines_next(Lines* lines, str* dest) {
    if (*lines->last == '\0') { return false; }

    char* begin = lines->last;
    for (size_t len = 0;; len++) {
        if (begin[len] == '\n' || begin[len] == '\0') {
            dest->buf = begin;
            dest->len = len;
            lines->last = begin + len + (int)(begin[len] == '\n');
            return true;
        }
    }

    return false;
}

void lines_reset(Lines* lines) {
    lines->last = lines->src;
}


bool is_digit(char val) {
    return (val >= '0' && val <= '9');
}

int to_digit(char val) {
    int res = (int)(val - '0');
    if (res < 0 || res > 9) {
        return -1;
    }
    return res;
}


#endif
#endif
