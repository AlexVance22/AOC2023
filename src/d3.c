#include "utils.h"


static bool is_symbol(char val) {
    return val != '.' && !is_digit(val);
}


typedef struct Grid {
    str grid[256];
    size_t width;
    size_t height;
} Grid;

static char grid_get(const Grid* self, int x, int y) {
    if (x < 0 || x >= (int)self->width || y < 0 || y >= (int)self->height) {
        return '.';
    }
    return self->grid[y].buf[x];
}

typedef struct Vec2 {
    int x;
    int y;
} Vec2;


static int find_max_3_digit_num(const int digits[5]) {
    if (digits[2] == -1) { return -1; }
    const int begin = (digits[1] == -1) ? 2 : ((digits[0] == -1) ? 1 : 0);
    const int end   = (digits[3] == -1) ? 3 : ((digits[4] == -1) ? 4 : 5);
    int num = 0;
    for (int i = begin; i < end; i++) {
        num *= 10;
        num += digits[i];
    }
    return num;
}



int d3_1_impl(Lines* file) {
    Grid grid;
    size_t height = 0;
    for (str line; lines_next(file, &line); height++) {
        grid.grid[height] = line;
    }
    grid.width = grid.grid[0].len;
    grid.height = height;

    int sum = 0;
    for (size_t y = 0; y < grid.height; y++) {
        for (size_t x = 0; x < grid.width; x++) {
            const char c = grid_get(&grid, (int)x, (int)y);
            if (is_digit(c)) {
                // fetch number
                int num = to_digit(c);
                size_t i = x + 1;
                for (; i < grid.width; i++) {
                    const char d = grid_get(&grid, (int)i, (int)y);
                    if (is_digit(d)) {
                        num *= 10;
                        num += to_digit(d);
                    } else {
                        break;
                    }
                }

                // check adjacency
                bool part = false;
                const int begin = (int)x;
                const int end = (int)i;
                for (int j = begin; j < end; j++) {
                    if (is_symbol(grid_get(&grid, j - 1, (int)y - 1)) ||
                        is_symbol(grid_get(&grid, j - 1, (int)y    )) ||
                        is_symbol(grid_get(&grid, j - 1, (int)y + 1)) ||
                        is_symbol(grid_get(&grid, j,     (int)y - 1)) ||
                        is_symbol(grid_get(&grid, j,     (int)y + 1)) ||
                        is_symbol(grid_get(&grid, j + 1, (int)y - 1)) ||
                        is_symbol(grid_get(&grid, j + 1, (int)y    )) ||
                        is_symbol(grid_get(&grid, j + 1, (int)y + 1))) {
                        part = true;
                    }
                }

                if (part) {
                    sum += num;
                }
                x = i - 1;
            }
        }
    }

    return sum;
}


int d3_2_impl(Lines* file) {
    Grid grid;
    size_t height = 0;
    for (str line; lines_next(file, &line); height++) {
        grid.grid[height] = line;
    }
    grid.width = grid.grid[0].len;
    grid.height = height;

    int sum = 0;
    for (size_t y = 0; y < grid.height; y++) {
        for (size_t x = 0; x < grid.width; x++) {
            const char c = grid_get(&grid, (int)x, (int)y);
            if (c == '*') {
                // check adjacency
                int vals[2] = { -1, -1 };
                const Vec2 checks[8] = { { (int)x - 1, (int)y - 1 },
                                         { (int)x - 1, (int)y     },
                                         { (int)x - 1, (int)y + 1 },
                                         { (int)x,     (int)y - 1 },
                                         { (int)x,     (int)y + 1 },
                                         { (int)x + 1, (int)y - 1 },
                                         { (int)x + 1, (int)y     },
                                         { (int)x + 1, (int)y + 1 } };

                for (int j = 0; j < 8; j++) {
                    const Vec2 p = checks[j];
                    const int digits[5] = { to_digit(grid_get(&grid, p.x - 2, p.y)),
                                            to_digit(grid_get(&grid, p.x - 1, p.y)),
                                            to_digit(grid_get(&grid, p.x,     p.y)),
                                            to_digit(grid_get(&grid, p.x + 1, p.y)),
                                            to_digit(grid_get(&grid, p.x + 2, p.y)) };
                    vals[0] = find_max_3_digit_num(digits);
                    if (vals[0] != -1) {
                        break;
                    }
                }
                for (int j = 0; j < 8; j++) {
                    const Vec2 p = checks[j];
                    const int digits[5] = { to_digit(grid_get(&grid, p.x - 2, p.y)),
                                            to_digit(grid_get(&grid, p.x - 1, p.y)),
                                            to_digit(grid_get(&grid, p.x,     p.y)),
                                            to_digit(grid_get(&grid, p.x + 1, p.y)),
                                            to_digit(grid_get(&grid, p.x + 2, p.y)) };
                    const int num = find_max_3_digit_num(digits);
                    if (num != -1 && num != vals[0]) {
                        vals[1] = num;
                        break;
                    }
                }

                if (vals[0] != -1 && vals[1] != -1) {
                    sum += vals[0] * vals[1];
                }
            }
        }
    }

    return sum;
}


void d3() {
    Lines file = get_file_lines("res/d3.txt");
    printf("result day 3 - part 1: %d",   d3_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %d\n", d3_2_impl(&file));
    free_file_lines(&file);
}

