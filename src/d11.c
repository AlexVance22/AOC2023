#include "utils.h"


int d11_1_impl(Lines* file) {
    return 0;
}


int d11_2_impl(Lines* file) {
    return 0;
}


void d11() {
    Lines file = get_file_lines("res/d11.txt");
    printf("result day 11 - part 1: %d",  d11_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d11_2_impl(&file));
    free_file_lines(&file);
}
