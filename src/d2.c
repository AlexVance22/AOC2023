#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


int d2_1_impl(Lines* file) {
    int sum = 0;
    for (str line; lines_next(file, &line);) {
        StrSplit split = str_split(&line);
        str token;

        split_next(&split, &token); // "Game"
        split_next(&split, &token); // "n:"
        str id_str = str_remove_suffix(&token, &STR(":"));
        int id = str_to_int(&id_str);
        bool poss = true;

        while (split_next(&split, &token)) {
            int count = str_to_int(&token);
            split_next(&split, &token);
            str temp = str_remove_suffix(&token, &STR(";"));
            str color = str_remove_suffix(&temp, &STR(","));
            if (str_eq(&color, &STR("red")) && count > 12) {
                poss = false;
            } else if (str_eq(&color, &STR("green")) && count > 13) {
                poss = false;
            } else if (str_eq(&color, &STR("blue")) && count > 14) {
                poss = false;
            }
        }
        if (poss) {
            sum += id;
        }
    }

    return sum;
}


int d2_2_impl(Lines* file) {
    int sum = 0;
    for (str line; lines_next(file, &line);) {
        StrSplit split = str_split(&line);
        str token;

        split_next(&split, &token); // "Game"
        split_next(&split, &token); // "n:"
        int max_red = 0;
        int max_green = 0;
        int max_blue = 0;

        while (split_next(&split, &token)) {
            int count = str_to_int(&token);
            split_next(&split, &token);
            str temp = str_remove_suffix(&token, &STR(";"));
            str color = str_remove_suffix(&temp, &STR(","));
            if (str_eq(&color, &STR("red")) && count > max_red) {
                max_red = count;
            } else if (str_eq(&color, &STR("green")) && count > max_green) {
                max_green = count;
            } else if (str_eq(&color, &STR("blue")) && count > max_blue) {
                max_blue = count;
            }
        }
        sum += max_red * max_green * max_blue;
    }

    return sum;
}


void d2() {
    Lines file = get_file_lines("res/d2.txt");
    printf("result day 2 - part 1: %d",   d2_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d2_2_impl(&file));
}

