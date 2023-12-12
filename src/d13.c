#include "utils.h"


int d13_1_impl(Lines* file) {
    return 0;
}


int d13_2_impl(Lines* file) {
    return 0;
}


void d13() {
    Lines file = get_file_lines("res/d13.txt");
    printf("result day 13 - part 1: %d",   d13_1_impl(&file));
    lines_reset(&file);
    printf(              ", part 2: %d\n", d13_2_impl(&file));
    free_file_lines(&file);
}
