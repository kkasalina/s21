#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE

#define STR_SIZE 10000

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} unit;

typedef struct {
  char lastSim;
  char lastLastSim;
  char c;
  char flag_t;
  int flag_v;
  int flag_n;
  int flag_b;
} arr;

static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                       {"number", 0, 0, 'n'},
                                       {"squeeze-blank", 0, 0, 's'}

};

void flags(int ge, unit *flag);
void file_open(int argc, char **argv, int optind, unit *flag, arr *chars);
void big(FILE *file, unit *flag, arr *chars);

#endif  // SRC_CAT_S21_CAT_H_