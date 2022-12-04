 #include <stdio.h>
 #include <stdarg.h>
 #include <string.h>
 #include <stdlib.h>

static char *tokenstring = "sgggp 5 ";
/*static*/ char s[81];
char* res = NULL;
char p[81];
size_t i = 0;
size_t j = 0;


int formatFlags(const char *format) {
  int flagSpec = 0;
  for (size_t i = 0; i < strlen(format); i++) {
    if(format[i] == '%') {
      flagSpec++;
    }
  }
  return flagSpec;
}

char *s21_sscanf(const char *str, const char *format, ...) {
  // printf("%s", format);
  // printf(" %d 2-", p);
  int leght = strlen(str);
      if(formatFlags(format) != 0) { 
        while (leght != 0) {
          va_list arg;
          va_start(arg, *format);
          // char *f = (char*)format;
          // printf("3- %d", p);
          for ( ; i < (strlen(format)); i++) {
            if (format[i] == '%') {
              i++;
              if (format[i] == 's') {
                for(; str[j] != ' '; j++) {
                  s[j] = str[j];
                }
              res = s;
                continue; 
            }
            }
          if (format[i] == 'd') {
                for( ; str[j] != '\0'; j++) {
                  // if (str[j] != ' ')
                  // printf("%c\n", str[j]);
                        *p = va_arg(arg, int);  
                        p[j] = str[j];
                }
              // res = (char)f;
                continue; 
            } else {
              putchar(format[i]);
            } 
            // i--;
            format++;
          }
          va_end(arg);      
          leght--;
        } 
      } else {
        printf("ERROR"); // поменять на функцию
        exit(1);
      }

  return res;
}

int main() {

// printf("1- %d", p);
  res = s21_sscanf(tokenstring, "%s %d", s, p);
  if (res != NULL) printf("%s %s", s, p);
  return 0;
}
               

// #include <stdarg.h>
// #include <stdio.h>
// #include <string.h>

// #include "s21_string.h"

// void display(char *format, ...) {
//   int d;
//   double f;
//   char ch;

//   va_list factor;
//   va_start(factor, format);

//   for (char *c = format; *c; c++) {
//     if (*c != '%') {
//       printf("%c", *c);
//       continue;
//     }
//     switch (*++c) {
//       case 'd':
//         d = va_arg(factor, int);
//         printf("%d", d);
//         break;
//       case 'f':
//         f = va_arg(factor, double);
//         printf("%.2lf", f);
//         break;
//       case 's':
//         printf("%s", ch);
//         ch = va_arg(factor, int);
//       default:
//         printf("%c", *c);
//     }
//   }
//   va_end(factor);
// }

// void testit(int i, ...) {
//   va_list argptr;
//   va_start(argptr, i);

//   if (i == 0) {
//     int n = va_arg(argptr, int);
//     printf("%d\n", n);
//   } else {
//     char *s = va_arg(argptr, char *);
//     printf("%s\n", s);
//   }

//   va_end(argptr);
// }

// void my_printf(char *str, const char *format, ...) {
//   va_list agr;
//   va_start(agr, *format);
//   while (*format != '\0') {
//     if (*format == '%') {
//       // printf("d1111");
//       format++;
//       if (*format == '%') {
//         putchar('%');
//         continue;
//       }
//       if (*format == 's') {
//         format++;
//         // printf("d");
//         char *lolipop = va_arg(agr, char*);
//         // strcat(str, lolipop);
//         printf("%s", lolipop);
//         continue;
//       }
//       if (*format == 'd') {
//         format++;
//         // printf("d3333");
//         int doc = va_arg(agr, int);
//         // strcat(str, doc);
//         printf("%d", doc);
//         continue;
//       } 
//       // else {
//       //   fputs("Not implemented", stdout);
//       // }
//     }  else {
//       // printf("d5555");
//       putchar(*format);
//     }
//     format++;
//   }
//   // printf(str);
//   va_end(agr);
// }

// int main() {
//   char kol[100];
//   my_printf(kol, "%s %s %% %d", "dasdasd ", " popopopo ", 3);

//   // sprintf(kol,"%s%s", "kkkkkk ", " ddddd");
//   printf(kol);



//   // testit(0, 3);  // 1st problem: 0xffffffff is not an int
//   // testit(1, "fafafafaf\n");        // 2nd problem: NULL is not a char

//   char result[100] = "";
//   char result_s21[100] = "";
//   char format_str[100] = "%.16f";
//   float f = 7.891235551512512321;
//   sprintf(result, format_str, f);
//   // printf("%s", result);

//   return 0;
// }
