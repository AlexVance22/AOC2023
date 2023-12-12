#include "utils.h"


int d6_1_impl(Lines* file) {
    str line;
    lines_next(file, &line);
    StrSplit split = str_split(&line);
    str token;
    split_next(&split, &token); // "Time:"
    int time[8];
    int time_len = 0;
    while (split_next(&split, &token)) {
        time[time_len++] = str_to_int(&token);
    }
    lines_next(file, &line);
    split = str_split(&line);
    split_next(&split, &token); // "Distance:"
    int dist[8];
    int dist_len = 0;
    while (split_next(&split, &token)) {
        dist[dist_len++] = str_to_int(&token);
    }

    int prod = 1;
    for (int i = 0; i < time_len; i++) {
        for (int j = 0; j <= time[i]; j++) {
            const int d = time[i] * j - j * j;
            if (d > dist[i]) {
                prod *= time[i] - 2*j + 1;
                break;
            }
        }
    }

    return prod;
}


i64 d6_2_impl(Lines* file) {
    str line;
    lines_next(file, &line);
    StrSplit split = str_split(&line);
    str token;
    split_next(&split, &token); // "Time:"
    String time_str = string_new();
    while (split_next(&split, &token)) {
        string_push_str(&time_str, token);
    }
    i64 time = string_to_int(&time_str);

    lines_next(file, &line);
    split = str_split(&line);
    split_next(&split, &token); // "Distance:"
    String dist_str = string_new();
    while (split_next(&split, &token)) {
        string_push_str(&dist_str, token);
    }
    i64 dist = string_to_int(&dist_str);

    for (i64 i = 0; i <= time; i++) {
        const i64 d = i * (time  - i);
        if (d > dist) {
            const i64 min_t = i;
            const i64 max_t = (time - i + 1);
            return max_t - min_t;
        }
    }

    return 0;
}


void d6() {
    Lines file = get_file_lines("res/d6.txt");
    printf("result day 6 - part 1: %d",     d6_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %lld\n", d6_2_impl(&file));
    free_file_lines(&file);
}
