#include "utils.h"


int d10_1_impl(Lines* file) {
    return 0;
}


int d10_2_impl(Lines* file) {
    return 0;
}


void d10() {
    Lines file = get_file_lines("res/d10.txt");
    printf("result day 10 - part 1: %d",  d10_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d10_2_impl(&file));
    free_file_lines(&file);
}
