#include "utils.h"
#include <string.h>


typedef struct Hand {
    int cards[5];
    i64 score;
    i64 bid;
} Hand;


static int eval(Hand* val) {
    int counts[13] = { 0 };
    for (int i = 0; i < 5; i++) {
        counts[val->cards[i] - 2]++;
    }

    int pairs = 0;
    int threes = 0;

    for (int i = 0; i < 13; i++) {
        if (counts[i] == 5) {
            return 6;
        } else if (counts[i] == 4) {
            return 5;
        } else if (counts[i] == 3) {
            threes++;
        } else if (counts[i] == 2) {
            pairs++;
        }
    }

    if (threes == 1) {
        if (pairs == 1) {
            return 4;
        } else {
            return 3;
        }
    } else if (pairs == 2) {
        return 2;
    } else if (pairs == 1) {
        return 1;
    }

    return 0;
}

static int eval2(Hand* val) {
    int counts[13] = { 0 };
    for (int i = 0; i < 5; i++) {
        counts[val->cards[i] - 1]++;
    }

    int j = counts[0];
    int pairs = 0;
    int threes = 0;

    for (int i = 1; i < 13; i++) {
        if (counts[i] + j == 5) { return 6; }
    }
    for (int i = 1; i < 13; i++) {
        if (counts[i] + j == 4) { return 5; }
    }
    for (int i = 1; i < 13; i++) {
        if (counts[i] + j == 3) { threes++; j -= 3 - counts[i]; counts[i] = 0; }
    }
    for (int i = 1; i < 13; i++) {
        if (counts[i] + j == 2) { pairs++;  j -= 2 - counts[i]; counts[i] = 0; }
    }

    if (threes == 1) {
        if (pairs == 1) {
            return 4;
        } else {
            return 3;
        }
    } else if (pairs == 2) {
        return 2;
    } else if (pairs == 1) {
        return 1;
    }

    return 0;
}


static i64 cmp(Hand* left, Hand* right) {
    i64 base = left->score - right->score;
    if (base != 0) {
        return base;
    } else {
        for (size_t i = 0; i < 5; i++) {
            if (left->cards[i] != right->cards[i]) {
                return left->cards[i] - right->cards[i];
            }
        }
        return 0;
    }
}


static void bubblesort(Hand* array, int len) {
    bool swapped = false;

    for (int i = 0; i < len - 1; i++) {
        if (cmp(&array[i], &array[i + 1]) > 0) {
            Hand temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
            swapped = true;
        }
    }
    if (swapped) {
        bubblesort(array, len);
    }
}


i64 d7_1_impl(Lines* file) {
    Hand hands[1024];
    int hands_len = 0;

    for (str line; lines_next(file, &line);) {
        Hand h;
        StrSplit split = str_split(&line);
        str token;
        split_next(&split, &token);
        for (int i = 0; i < 5; i++) {
            switch (token.buf[i])
            {
            case 'A': h.cards[i] = 14; break;
            case 'K': h.cards[i] = 13; break;
            case 'Q': h.cards[i] = 12; break;
            case 'J': h.cards[i] = 11; break;
            case 'T': h.cards[i] = 10; break;
            default:  h.cards[i] = to_digit(token.buf[i]);
            }
        }
        split_next(&split, &token);
        h.score = eval(&h);
        h.bid = str_to_int(&token);
        hands[hands_len++] = h;
    }

    bubblesort(hands, hands_len);

    i64 sum = 0;
    for (int i = 0; i < hands_len; i++) {
        sum += hands[i].bid * (i + 1);
    }
    return sum;
}


i64 d7_2_impl(Lines* file) {
    Hand hands[1024];
    int hands_len = 0;

    for (str line; lines_next(file, &line);) {
        Hand h;
        StrSplit split = str_split(&line);
        str token;
        split_next(&split, &token);
        for (int i = 0; i < 5; i++) {
            switch (token.buf[i])
            {
            case 'A': h.cards[i] = 13; break;
            case 'K': h.cards[i] = 12; break;
            case 'Q': h.cards[i] = 11; break;
            case 'T': h.cards[i] = 10; break;
            case 'J': h.cards[i] = 1; break;
            default:  h.cards[i] = to_digit(token.buf[i]);
            }
        }
        split_next(&split, &token);
        h.score = eval2(&h);
        h.bid = str_to_int(&token);
        hands[hands_len++] = h;
    }

    bubblesort(hands, hands_len);

    i64 sum = 0;
    for (int i = 0; i < hands_len; i++) {
        sum += hands[i].bid * (i + 1);
    }
    return sum;
}


void d7() {
    Lines file = get_file_lines("res/d7.txt");
    printf("result day 7 - part 1: %lld",   d7_1_impl(&file));
    lines_reset(&file);
    printf(             ", part 2: %lld\n", d7_2_impl(&file));
    free_file_lines(&file);
}
