#ifndef SRC_CAT_S21_GREP_H_
#define SRC_CAT_S21_GREP_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} all_flags;

#define SIZE 10000

const char* short_options = "e:ivclnhsf:o?";
char gr;
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

void flags(char gr, char** argv, all_flags *unit);
void input_file_open(char** argv, int optind, int argc, all_flags *unit);  // int argc,
void shablon_str(char** argv, all_flags *unit);
void reg_func(FILE* file, char* str_f, int argc, all_flags *unit);
void Flag_F(char* str, all_flags *unit);
void Reg_start(all_flags *unit);
void Flag_No_H(int argc, char* str_f, all_flags *unit);
// void Flag_O();

#endif  // SRC_CAT_S21_GREP_H_