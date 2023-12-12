#include "utils.h"


typedef struct Map {
    i64 to;
    i64 from;
    i64 width;
} Map;


static i64 map_category(i64 val, Map map) {
    const i64 diff = val - map.from;
    if (diff >= 0 && diff < map.width) {
        return map.to + diff;
    }
    return val;
}

static i64 map_reverse(i64 val, Map map) {
    const i64 diff = val - map.to;
    if (diff >= 0 && diff < map.width) {
        return map.from + diff;
    }
    return val;
}


i64 d5_1_impl(Lines* file) {
    i64 seeds[64];
    i64 seeds_len = 0;
    i64 next[64];

    str line;
    lines_next(file, &line);
    StrSplit split = str_split(&line);
    str token;
    split_next(&split, &token); // "seeds:"
    while (split_next(&split, &token)) {
        seeds[seeds_len  ] = str_to_int(&token);
        next [seeds_len++] = str_to_int(&token);
    }

    while (lines_next(file, &line)) {
        if (str_eq(&line, &STR(""))) {
            lines_next(file, &line);
            for (int i = 0; i < seeds_len; i++) {
                seeds[i] = next[i];
            }
        } else {
            split = str_split(&line);
            Map map;
            split_next(&split, &token);
            map.to = str_to_int(&token);
            split_next(&split, &token);
            map.from = str_to_int(&token);
            split_next(&split, &token);
            map.width = str_to_int(&token);
            for (int i = 0; i < seeds_len; i++) {
                const i64 mapped = map_category(seeds[i], map);
                if (mapped != seeds[i]) {
                    next[i] = mapped;
                }
            }
        }
    }

    i64 min = next[0];
    for (int i = 0; i < seeds_len; i++) {
        if (next[i] < min) {
            min = next[i];
        }
    }
    return min;
}


i64 d5_2_impl(Lines* file) {
    i64 seeds[64];
    i64 seeds_len = 0;

    str line;
    lines_next(file, &line);
    StrSplit split = str_split(&line);
    str token;
    split_next(&split, &token); // "seeds:"
    while (split_next(&split, &token)) {
        seeds[seeds_len++] = str_to_int(&token);
    }

    int map_i = -1;
    int map_len[7] = { 0, 0, 0, 0, 0, 0, 0 };
    Map map[7][64];

    while (lines_next(file, &line)) {
        if (str_eq(&line, &STR(""))) {
            lines_next(file, &line);
            map_i++;
        } else {
            Map* m = &map[map_i][map_len[map_i]++];
            split = str_split(&line);
            split_next(&split, &token);
            m->to = str_to_int(&token);
            split_next(&split, &token);
            m->from = str_to_int(&token);
            split_next(&split, &token);
            m->width = str_to_int(&token);
        }
    }

    i64 min = INT64_MAX;

    for (int i = 0; i < seeds_len; i += 2) {
        i64 seed_base = seeds[i];
        i64 seed_end = seed_base + seeds[i + 1];

        for (i64 j = seed_base; j < seed_end; j++) {
            i64 seed = j;
            i64 next = j;

            for (int k = 0; k < 7; k++) {
                for (int l = 0; l < map_len[k]; l++) {
                    const i64 mapped = map_category(seed, map[k][l]);
                    if (mapped != seed) {
                        next = mapped;
                    }
                }
                seed = next;
            }

            if (next < min) {
                min = next;
            }
        }
    }

    return min;
}


i64 d5_2_impl_rev(Lines* file) { // ca 50x faster
    i64 seeds[64];
    i64 seeds_len = 0;

    str line;
    lines_next(file, &line);
    StrSplit split = str_split(&line);
    str token;
    split_next(&split, &token); // "seeds:"
    while (split_next(&split, &token)) {
        seeds[seeds_len++] = str_to_int(&token);
    }

    int map_i = -1;
    int map_len[7] = { 0, 0, 0, 0, 0, 0, 0 };
    Map map[7][64];

    while (lines_next(file, &line)) {
        if (str_eq(&line, &STR(""))) {
            lines_next(file, &line);
            map_i++;
        } else {
            Map* m = &map[map_i][map_len[map_i]++];
            split = str_split(&line);
            split_next(&split, &token);
            m->to = str_to_int(&token);
            split_next(&split, &token);
            m->from = str_to_int(&token);
            split_next(&split, &token);
            m->width = str_to_int(&token);
        }
    }

    for (i64 j = 0; j < INT64_MAX; j++) {
        i64 loc  = j;
        i64 prev = j;

        for (int k = 6; k >= 0; k--) {
            for (int l = 0; l < map_len[k]; l++) {
                const i64 mapped = map_reverse(loc, map[k][l]);
                if (mapped != loc) {
                    prev = mapped;
                }
            }
            loc = prev;
        }

        for (int k = 0; k < seeds_len; k += 2) {
            const i64 s_begin = seeds[k];
            const i64 s_end   = seeds[k] + seeds[k + 1];
            if (prev >= s_begin && prev < s_end) {
                return j;
            }
        }
    }

    return 0;
}


void d5() {
    Lines file = get_file_lines("res/d5.txt");
    printf("result day 5 - part 1: %lld",   d5_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %lld\n", d5_2_impl_rev(&file));
    free_file_lines(&file);
}

