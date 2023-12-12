#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


int d5_1_impl(Lines* file) {
    return 0;
}


int d5_2_impl(Lines* file) {
    return 0;
}


void d5() {
    Lines file = get_file_lines("res/d5.txt");
    printf("result day 5 - part 1: %d",   d5_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d5_2_impl(&file));
}
