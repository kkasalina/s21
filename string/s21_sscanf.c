#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static char *tokenstring = "hello 0";
char s[81];
char *res = NULL;
// char p[81] = {0};
int p;
size_t i = 0;
size_t j = 0;


int formatFlags(const char *format) {
  int flagSpec = 0;
  for (size_t i = 0; i < strlen(format); i++) {
    if (format[i] == '%') {
      flagSpec++;
    }
  }
  return flagSpec;
}

char *s21_sscanf(const char *str, const char *format, ...) {
  int leght = strlen(str);
  if (formatFlags(format) != 0) {
    while (leght != 0) {
      va_list arg;
      va_start(arg, format);
      for (; i < (strlen(format)); i++) {
        if (format[i] == '%') {
          i++;
          if (format[i] == 's') {
            for (; str[j] != ' '; j++) {
                s[j] = str[j];
              }
            res = s;
            continue;
            } else if (format[i] == 'd') {
              for (int k = 0, j = 0 ; str[j] != '\0'; j++) {
                //*p = va_arg(arg, int);
                if (str[j] > 47 && str[j] < 58) {
                  p = (int)str[j];
                  k++;
                }
              }
              // res = (char*)p;
              continue;
            }
        } else { 
          if (format[i] != ' ')
            putchar(format[i]);
          }
      }
      va_end(arg);
      leght--;
      format++;
    }
  } else {
      printf("ERROR"); // поменять на функцию
      exit(1);
  }
  return res;
}

int main() {
 res = s21_sscanf(tokenstring, "%s %d", s, &p);
 if (res != NULL) 
  printf("%s", res);
  return 0;
}
