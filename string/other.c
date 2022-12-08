#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ДОБАВИТЬ ВЕЗДЕ S21_
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// void *to_upper(const char *str) { // Возвращает копию (str), преобразованной
// в верхний регистр. В случае ошибки вернуть NULL
//   char *arr = NULL;
//   int inerror = 0;
//   if (str) {
//     arr = (char*)calloc((strlen(str) + 1), sizeof(char));
//     if (arr == NULL) {
//       inerror = 1;
//     }
//     for (size_t i = 0; i <= strlen(arr); i++) {
//       arr[i] = str[i];
//     }
//     if (arr) {
//       for (char *f = arr; *f; f++) {
//         if(*f >= 97 && *f <= 122) {
//           *f -=  32;
//         }
//       }
//     }
//   } else {
//     inerror = 1;
//   }
//   free(arr);
//   return inerror? NULL : (void*)arr;
// }

// void *to_lower(const char *str) { // Возвращает копию (str), преоб-ной в
// нижний регистр. В случае ошибки вернуть NULL
//   char *arr = NULL;
//   int inerror = 0;
//   if (str) {
//     arr = (char*)calloc((strlen(str) + 1), sizeof(char));
//     if (arr == NULL) {
//       inerror = 1;
//     }
//     for (size_t i = 0; i <= strlen(arr); i++) {
//       arr[i] = str[i];
//     }
//     if (arr) {
//       for (char *f = arr; *f; f++) {
//         if(*f >= 65 && *f <= 90) {
//           *f +=  32;
//         }
//       }
//     }
//   }  else {
//     inerror = 1;
//   }
//   free(arr);
//   return inerror? NULL : (void*)arr;
// }

// void *insert(const char *src, const char *str, size_t start_index) { //
// Возвращает новую строку, в которой указанная строка (str) вставлена
//                                                                      //в
//                                                                      указанную
//                                                                      позицию
//                                                                      (start_index)
//                                                                      в данной
//                                                                      строке
//                                                                      (src).
//                                                                      //В
//                                                                      случае
//                                                                      ошибки
//                                                                      вернуть
//                                                                      NULL
//   char *arr = NULL;
//   int inerror = 0;
//   size_t i = 0;
//   size_t j = 0;
//   if ((src && str) && (start_index <= (strlen(src)))) {
//     arr = (char*)calloc((strlen(str) + strlen(src) + 1), sizeof(char));
//     if (arr == NULL) {
//       inerror = 1;
//     }
//       if (arr) {
//         for(; i < start_index ; i++) {
//           arr[i] = src[i];
//         }
//         for(; j <= strlen(str); i++, j++) {
//           arr[i] = str[j];
//         }
//         char buf[strlen(src) - strlen(arr)];
//         for(i=0, j = start_index ; i <= strlen(buf); i++, j++) {
//           buf[i] = src[j];
//         }
//         strcat(arr, buf);
//       }
//     } else {
//       inerror = 1;
//     }
//     free(arr);
//     return inerror? NULL : (void*)arr;
//   }

void *trim(
    const char *src,
    const char *trim_chars) {  // Возвращает новую строку, в которой удаляются
                               // все начальные и конечные вхождения набора
                               // заданных символов (trim_chars) из данной
                               // строки (src). В случае ошибки вернуть NULL
  char *arr = NULL;
  int inerror = 0;
  // int flag = 0;
  int flagS = 0;
  int flagE = 0;
  // if (src) {
    arr = (char *)calloc((strlen(src) + 1), sizeof(char));
    if (arr == NULL) {
      inerror = 1;
    }
      for (size_t i = 0; i <= strlen(arr); i++) {
        for (size_t j = 0; j <= strlen(trim_chars); j++) {
          if (src[i] == trim_chars[j]) {
            flagS++;
          } 
          if (src[i] != trim_chars[j]) break;
        }printf("%d %d\n", flagS, flagE);
      }  
      for (size_t i = strlen(arr); i > 0 ; i--) {
        for (size_t j = 0; j <= strlen(trim_chars); j++) {
          if (src[i] == trim_chars[j]) {
            flagE++;
          } 
          if (src[i] != trim_chars[j]) continue;
        }
      }
    
        size_t i = 0;
        size_t j = strlen(src) - 1;
        if (flagS) i = flagS;
        if (flagE) j -= flagE;
        for (size_t l = 0; l < j; l++, i++) {
          arr[l] += src[i];
          // printf("%c", buf[i]);
        }
  free(arr);
  return inerror ? NULL : (void *)arr;
}

int main() {
  const char src[] = "\t\thello\t\t\ttimmy\t\t";
  //  const char str[] = "AAA";
  const char *trim_chars = " \t\n\v\r\f\0";
  printf("%s", (char *)trim(src, trim_chars));
  // printf("%s", arr);
  return 0;
}
