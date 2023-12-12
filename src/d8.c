#include "utils.h"


int d8_1_impl(Lines* file) {
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
