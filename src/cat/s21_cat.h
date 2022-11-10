#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE

int ge;
int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;
char lastSim = '\n';
char lastLastSim = '0';
char c = '0';
char flag_t = '0';
int flag_v = 0;
int flag_n = 1;
int flag_b = 1;
static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                       {"number", 0, 0, 'n'},
                                       {"squeeze-blank", 0, 0, 's'}

};

void flags(char **argv);
void file_open(int argc, char **argv, int optind);
void big(FILE *file);

#endif  // SRC_CAT_S21_CAT_H_