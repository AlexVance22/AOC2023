#include <string.h>
#include "utils.h"


static int first_digit(str val) {
    for (int i = 0; i < (int)val.len; i++) { if (is_digit(val.buf[i])) { return to_digit(val.buf[i]); } }
    return -1;
}

static int last_digit(str val) {
    for (int i = (int)val.len; i >= 0; i--) { if (is_digit(val.buf[i])) { return to_digit(val.buf[i]); } }
    return -1;
}

static int word_to_num(char* word) {
    char buf[8] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' };
    for (int i = 0; i < 7; i++) {
        buf[i] = word[i];
        if (i >= 2) {
            if (strncmp(buf, "one", 8) == 0) {
                return 1;
            } else if (strncmp(buf, "two", 8) == 0) {
                return 2;
            } else if (strncmp(buf, "three", 8) == 0) {
                return 3;
            } else if (strncmp(buf, "four", 8) == 0) {
                return 4;
            } else if (strncmp(buf, "five", 8) == 0) {
                return 5;
            } else if (strncmp(buf, "six", 8) == 0) {
                return 6;
            } else if (strncmp(buf, "seven", 8) == 0) {
                return 7;
            } else if (strncmp(buf, "eight", 8) == 0) {
                return 8;
            } else if (strncmp(buf, "nine", 8) == 0) {
                return 9;
            } else if (strncmp(buf, "zero", 8) == 0) {
                return 0;
            }
        }
    }
    return -1;
}


int d1_1_impl(Lines* file) {
    int sum = 0;
    for (str line; lines_next(file, &line);) {
        sum += first_digit(line) * 10;
        sum += last_digit(line);
    }

    return sum;
}


int d1_2_impl(Lines* file) {
    int sum = 0;
    for (str line; lines_next(file, &line);) {
        for (int i = 0; i < (int)line.len; i++) {
            int c = to_digit(line.buf[i]);
            if (c == -1) {
                c = word_to_num(line.buf + i);
                if (c == -1) {
                    continue;
                }
            }
            sum += c * 10;
            break;
        }
        for (int i = (int)line.len; i >= 0; i--) {
            int c = to_digit(line.buf[i]);
            if (c == -1) {
                c = word_to_num(line.buf + i);
                if (c == -1) {
                    continue;
                }
            }
            sum += c;
            break;
        }
    }

    return sum;
}


void d1() {
    Lines file = get_file_lines("res/d1.txt");
    printf("result day 1 - part 1: %d",   d1_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d1_2_impl(&file));
    free_file_lines(&file);
}

