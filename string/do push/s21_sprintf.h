#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <unistd.h>
#include <float.h>

#define CHAR_PATTERN 1000

typedef long unsigned s21_size_t;

typedef struct info {
  va_list args;
  int width;
  int precision;
  int hex_size;
  int zero_padding;
  int point;
  int dash;
  int total_length;
  int sign;
  int is_zero;
  int space;
  int hash;
  float numb_fl;
  int j_save_format;
  int flag_f_float;
  int flag_o;
  int flag_e;
  int flag_u;
  int flag_h;
  int flag_l;
  char full_buf[CHAR_PATTERN];
} s_info;

char *itoa(int value, char *result, int base);
char *itoa_u(unsigned int value, char *result, int base);
int s21_sprintf(char *str, const char *format, ...);
void wparg_help(s_info *ints);
char *s_strncat(char *dest, const char *src, s21_size_t n);
void print_res(s_info *ints, const char *str, int temp);
int print_format(s_info *ints, const char *format, int temp);
void print_unsigned(s_info *ints);
void point_o(s_info *ints, unsigned long long numb, char o);
void print_numb(s_info *ints);
void print_char(s_info *ints);
void print_str(s_info *ints);
void print_pointer(s_info *ints);
void print_hex(s_info *ints);
void print_hexup(s_info *ints);
void print_per(s_info *ints);
void print_float(s_info *ints);
int check_format(const char *format, int temp);
int check_format_letter(const char *format, int temp);
int check_format_letter_2(const char *format, int temp);
int check_percision(s_info *ints, const char *format, int temp);
int check_point(s_info *ints, const char *format, int temp);
int check_wp(s_info *ints, const char *format, int temp);
int check_wparg(s_info *ints, const char *format, int temp);
int n_len(int n);
void s21_sprintf_g(s_info *ints);

void flag_exp(s_info *ints);
void ftoa(long double n, char *res, s_info *ints);
void reverse(char *str, int len);
int intToStr(long long int x, char str[], int d);
unsigned int un_len(unsigned int n);
void width_full(s_info *ints, int flag);
void prec_ful(s_info *ints);
int put_str(s_info *ints, char *s);
void scanndase(s_info *ints, unsigned long long numb);
void point_b(s_info *ints, unsigned long long numb, char x);
void put(int n, s_info *ints);
void putnbr(unsigned n, s_info *ints);
void litle_if(s_info *ints, int *numb);
void else_if(s_info *ints, int *numb);
void scanndase_o(s_info *ints, unsigned long long numb);
int str_else(char *s, s_info *ints);
void hexup_help(s_info *ints, unsigned int hexup);
void hex_help(s_info *ints, unsigned int hexal);
void numb_if(int numb, s_info *ints);
char *s_strcat(char *dest, const char *src);
void unsint_if(unsigned int uns, s_info *ints);
int check_help(s_info *ints, const char *format, int temp);
size_t s21strlen(const char *str);

int main() {
  // char data[100];
  // char data1[100];
  // s21_sprintf(data, "%Ld\n", INT32_MAX);
  // sprintf(data1, "%Ld\n", INT32_MAX);
  // printf("%s\n", data);
  // printf("%s\n", data1);

int numbers[] = {5, 0, -1, INT32_MAX, INT32_MIN, -777};
  //    int oct [] = {17777777777, -17777777777, 5};
  short int short_int = 12367;
  long int long_int = 1234567890;
  int hex[] = {0x7FFFFFFF, -0x7FFFFFFF, 0x0, 0xffc, -0x25cbc};

  char str1[200][200] = {0};
  char str2[200][200] = {0};

  s21_sprintf(str1[95], "%+10.6f % -#10.0f %0*f % 10.0f % #-10.1f", 5000.0099,
              -5000.0099, 4, 500.09, 0., 0.);
  sprintf(str2[95], "%+10.6f % -#10.3f %0*f % 10.0f % #-10.1f", 5000.0099,
          -5000.0099, 4, 500.09, 0., 0.);

printf("%s\n", str1[95]);
printf("%s\n", str2[95]);
  return 0;
}

