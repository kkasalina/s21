
#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#define  _GNU_SOURCE

#include <unistd.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *short_options = "e:ivclnhsf:o";
static struct option longopts[] = {
    {NULL, 0, NULL, 0},
};

void readfile(char *argv[], int argc, int optind);
void usage(void);
void opt(char c, char *argv[]);
void get_pattern(char *argv[]);
void get_varriable(FILE *file_name, int argc, char *path);

char pattern[9000] = {0};
int eflag;
int iflag;
int vflag;
int cflag;
int lflag;
int nflag;
int hflag;
int sflag;
int fflag;
int oflag;

#endif // SRC_MYLIB_H_