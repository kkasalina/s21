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
} flagsA;


#define SIZE 10000

static struct option long_options[] = {
    {0, 0, 0, 0},
};
const char* short_options = "e:ivclnhsf:o?";

void flags(int gr, char** argv, flagsA *all);
void input_file_open(char** argv, int optind, int argc, flagsA *all);
void shablon_str(char** argv, flagsA *all);
void reg_func(FILE* file, char* str_f, int argc, flagsA *all);
void Flag_F(char* str, flagsA *all);
void Reg_start(flagsA *all);
void Flag_No_H(int argc, char* str_f, flagsA *all);


char shablon[SIZE];
regex_t rege;  // хранениe скомпилированного регулярного выражения
regmatch_t match_p[4];
size_t match_n = 4, leght = 1000;  // длина массива структуры regmatch_t
int line, mom;
int done = 0, count = 0;
char* pattern = NULL;

#endif  // S21_GREP_H_
