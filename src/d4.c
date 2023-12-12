#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


int d4_1_impl(Lines* file) {
    int sum = 0;
    for (str line; lines_next(file, &line);) {
        StrSplit split = str_split(&line);
        str token;

        split_next(&split, &token); // "Card"
        split_next(&split, &token); // "n:"

        int winning[64];
        int winning_len = 0;
        int gotten [64];
        int gotten_len = -1;
        while (split_next(&split, &token)) {
            if (str_eq(&token, &STR("|"))) {
                gotten_len = 0;
                continue;
            }
            if (gotten_len == -1) {
                winning[winning_len++] = str_to_int(&token);
            } else {
                gotten [gotten_len++]  = str_to_int(&token);
            }
        }

        int count = 0;
        for (int i = 0; i < gotten_len; i++) {
            for (int j = 0; j < winning_len; j++) {
                if (gotten[i] == winning[j]) {
                    count++;
                    break;
                }
            }
        }

        int points = count > 0 ? 1 : 0;
        for (int i = 1; i < count; i++) {
            points *= 2;
        }
        sum += points;
    }

    return sum;
}


int d4_2_impl(Lines* file) {
    int copy_count[256];
    for (int i = 0; i < 256; i++) {
        copy_count[i] = 1;
    }

    int sum = 0;
    for (str line; lines_next(file, &line);) {
        StrSplit split = str_split(&line);
        str token;

        split_next(&split, &token); // "Card"
        split_next(&split, &token); // "n:"
        const str id_str = str_remove_suffix(&token, &STR(":"));
        const int id = str_to_int(&id_str) - 1;
        const int copies = copy_count[id];
        sum += copies;

        int winning[64];
        int winning_len = 0;
        int gotten [64];
        int gotten_len = -1;
        while (split_next(&split, &token)) {
            if (str_eq(&token, &STR("|"))) {
                gotten_len = 0;
                continue;
            }
            if (gotten_len == -1) {
                winning[winning_len++] = str_to_int(&token);
            } else {
                gotten [gotten_len++]  = str_to_int(&token);
            }
        }

        int count = 0;
        for (int i = 0; i < gotten_len; i++) {
            for (int j = 0; j < winning_len; j++) {
                if (gotten[i] == winning[j]) {
                    count++;
                    break;
                }
            }
        }
        for (int j = 0; j < count; j++) {
            copy_count[id + j + 1] += copies;
        }
    }

    return sum;
}


void d4() {
    Lines file = get_file_lines("res/d4.txt");
    printf("result day 4 - part 1: %d",   d4_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d4_2_impl(&file));
}

