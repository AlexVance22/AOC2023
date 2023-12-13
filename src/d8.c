#include "utils.h"
#include "structs/hashtable.h"


typedef struct Routes {
    str left;
    str right;
} Routes;


int d8_1_impl(Lines* file) {
    HashTable table = hashtable(Routes);

    str dirs;
    lines_next(file, &dirs);
    lines_next(file, &STR(""));

    for (str line; lines_next(file, &line);) {
        StrSplit split = str_split(&line);
        str key;
        split_next(&split, &key);
        Routes routes;
        str token;
        split_next(&split, &token); // "="
        split_next(&split, &token);
        str left     = str_remove_prefix(&token, &STR("("));
        routes.left  = str_remove_suffix(&left,  &STR(","));
        split_next(&split, &token);
        routes.right = str_remove_suffix(&token, &STR(")"));
        hashtable_set(&table, &key, &routes);
    }

    return 0;
}


int d8_2_impl(Lines* file) {
    return 0;
}


void d8() {
    Lines file = get_file_lines("res/d8.txt");
    printf("result day 8 - part 1: %d",   d8_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d8_2_impl(&file));
    free_file_lines(&file);
}
