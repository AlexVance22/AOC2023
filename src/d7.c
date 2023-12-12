#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


int d7_1_impl(Lines* file) {
    return 0;
}


int d7_2_impl(Lines* file) {
    return 0;
}


void d7() {
    Lines file = get_file_lines("res/d7.txt");
    printf("result day 7 - part 1: %d",   d7_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d7_2_impl(&file));
}
