#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


int d6_1_impl(Lines* file) {
    return 0;
}


int d6_2_impl(Lines* file) {
    return 0;
}


void d6() {
    Lines file = get_file_lines("res/d6.txt");
    printf("result day 6 - part 1: %d",   d6_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d6_2_impl(&file));
}
