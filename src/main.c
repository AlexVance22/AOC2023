#define UTILS_IMPL
#include "utils.h"

#include "d1.h"
#include "d2.h"
#include "d3.h"
#include "d4.h"
#include "d5.h"
#include "d6.h"
#include "d7.h"
#include "d8.h"
#include "d9.h"
#include "d10.h"
#include "d11.h"
#include "d12.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "please provide the day you want the answer to\n");
        return 1;
    }

    switch (str_to_int(&(str){ argv[1], strlen(argv[1]) }))
    {
    case 1:  d1();  break;
    case 2:  d2();  break;
    case 3:  d3();  break;
    case 4:  d4();  break;
    case 5:  d5();  break;
    case 6: case 7: case 8: case 9: case 10: case 11: case 12:
        fprintf(stderr, "i havent solved this problem yet\n");
        return 1;
    // case 6:  d6();  break;
    // case 7:  d7();  break;
    // case 8:  d8();  break;
    // case 9:  d9();  break;
    // case 10: d10(); break;
    // case 11: d11(); break;
    // case 12: d12(); break;
    default:
        fprintf(stderr, "its too early for this problem yet\n");
        return 1;
    }
}

