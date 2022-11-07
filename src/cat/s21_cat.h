#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int ge;
int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;

static struct option long_options[] =
    {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank" , 0, 0, 's'}
        
    };


// int voidline (char c, int voidLine);
// int count (char *str, int x);


#endif // SRC_CAT_S21_CAT_H_