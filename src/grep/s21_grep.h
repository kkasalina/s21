
#ifndef SRC_CAT_S21_GREP_H_
#define SRC_CAT_S21_GREP_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#define  _GNU_SOURCE
#define SIZE 10000

const char* short_options = "e:ivclnhsf:o?";
int gr, e = 0, i = 0, v = 0, c = 0, l = 0, n = 0, h = 0, s = 0, f = 0, o = 0;
char shablon[SIZE];
static struct option long_options[] = {
    {0, 0, 0, 0},
};
regex_t rege;  // хранениe скомпилированного регулярного выражения
regmatch_t match_p[4];
size_t match_n = 4, leght = 1000;  // длина массива структуры regmatch_t
int line, mom;
int done = 0, count = 0;
char* pattern = NULL;

void flags(int gr, char** argv);
void input_file_open(char** argv, int optind, int argc);  // int argc,
void shablon_str(char** argv);
void reg_func(FILE* file, char* str_f, int argc);
void Flag_F(char* str);
void Reg_start();
void Flag_No_H(int argc, char* str_f);
// void Flag_O();

#endif  // SRC_CAT_S21_GREP_H_