#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static char *tokenstring = "kifyui 12356789 ";
char s[81];
char *res = NULL;
int arr[50] = {0};
int p = 0;
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

int s21_atoi(const char *str, int *arr) { 
  int leght = 0;
  for (int k = 0; str[j] != '\0'; j++, k++) {
    if (str[j] > 47 && str[j] < 58) {
      arr[k] = str[j] - 48 ;
      leght++;
    } 
  }
  if (leght > 1) {
    for (int k = 0; k <= leght; k++) {
      p += arr[k];
      p *= 10;
    }
      p /= 10;
  } else {
     p += arr[1];
  }
 j -= leght;
  return p;
}

char *s21_sscanf(const char *str, const char *format, ...) {
  int leght = strlen(str);
  // char* h =
  if (formatFlags(format) != 0) {
    while (leght != 0) {
      va_list arg;
      va_start(arg, format);
      for (; i < (strlen(format)); i++) {
        if (format[i] == '%') {
          i++;
          if (format[i] == 's') {
            for (j--; str[j] != ' '; j++) {
                 s[j] = str[j];
              }
            res = "s";
            continue;
            } else if (format[i] == 'd') {                  
              p = s21_atoi(str, arr);
              res = "p";
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
 printf("%s %d", s, p);
  return 0;
}
