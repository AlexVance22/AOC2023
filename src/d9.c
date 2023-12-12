#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


int d9_1_impl(Lines* file) {
    return 0;
}


int d9_2_impl(Lines* file) {
    return 0;
}


void d9() {
    Lines file = get_file_lines("res/d9.txt");
    printf("result day 9 - part 1: %d",   d9_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d9_2_impl(&file));
}
