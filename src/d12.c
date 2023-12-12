#include "utils.h"


int d12_1_impl(Lines* file) {
    return 0;
}


int d12_2_impl(Lines* file) {
    return 0;
}


void d12() {
    Lines file = get_file_lines("res/d12.txt");
    printf("result day 12 - part 1: %d",   d12_1_impl(&file));
    lines_reset(&file);
    printf(              ", part 2: %d\n", d12_2_impl(&file));
    free_file_lines(&file);
}
