
#ifndef SRC_CAT_S21_GREP_H_
#define SRC_CAT_S21_GREP_H_
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> 
#include <string.h> 
#include <pcre.h>
// #include <regex.h>
#include <unistd.h>
#define  _GNU_SOURCE
#define SIZE 10000

int gr, e = 0, i = 0, v = 0, c = 0, l = 0, n = 0, h = 0, s = 0, f = 0, o = 0;
char shablon[10000];
static struct option long_options[] =
    {
      {0, 0, 0, 0},
    };

void flags (int gr, char** argv);
void input_file_open (int argc, char** argv, int optind);
void shablon_str(char** argv);
void reg_func ();



#endif // SRC_CAT_S21_GREP_H_