#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h> 

// ДОБАВИТЬ ВЕЗДЕ S21_ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void *to_upper(const char *str) { // Возвращает копию (str), преобразованной в верхний регистр. В случае ошибки вернуть NULL
  char *src = NULL;
  if (str) {
    src = (char*)malloc((strlen(str) + 1));
    for (size_t i = 0; i <= strlen(src); i++) {
      src[i] = str[i];
    }
    if (src) {
      for (char *f = src; *f; *f++) {      
        if(*f >= 97 && *f <= 122) {
          *f -=  32;
        }
      }  
    }
    
  }
  free(src);
  return (void*)src;
}

void *to_lower(const char *str) { // Возвращает копию (str), преоб-ной в нижний регистр. В случае ошибки вернуть NULL
  char *arr = NULL;
  if (str) {
    arr = (char*)malloc((strlen(str) + 1));
    for (size_t i = 0; i <= strlen(arr); i++) {
      arr[i] = str[i];
    }
    if (arr) {
      for (char *f = arr; *f; *f++) {      
        if(*f >= 65 && *f <= 90) {
          *f +=  32;
        }
      }  
    } 
  }
  free(arr);
  return (void*)arr;
}

void *insert(const char *src, const char *str, size_t start_index) { // Возвращает новую строку, в которой указанная строка (str) вставлена 
                                                                     //в указанную позицию (start_index) в данной строке (src). 
                                                                     //В случае ошибки вернуть NULL
  char *arr = NULL;
  int inerror = 0;
  size_t i = 0;
  size_t j = 0;
  if ((src && str) && (start_index <= (strlen(src)))) {
    arr = (char*)calloc((strlen(str) + strlen(src) + 1), sizeof(char));
    if (arr == NULL) {
      inerror = 1;
    }
      if (arr) {  
        for(; i < start_index ; i++) {
          arr[i] = src[i];
        } 
        for(; j <= strlen(str); i++, j++) {      
          arr[i] = str[j];
        } 
        char buf[strlen(src) - strlen(arr)];
        for(i=0, j = start_index ; i <= strlen(buf); i++, j++) {
          buf[i] = src[j];
        }
        strcat(arr, buf);
      }
    } else {
      inerror = 1;
    }
    free(arr);
    return inerror? NULL : (void*)arr;
  }

// char *trim(const char *src) { // Возвращает новую строку, в которой удаляются все начальные и конечные вхождения набора заданных символов (trim_chars) из данной строки (src). В случае ошибки вернуть NULL
  

  // if (src) {
  //   arr = (char*)malloc((strlen(src) + 1));
  //   for (size_t i = 0; i <= strlen(arr); i++) {
  //     arr[i] = src[i];
  //   }
  // }
  // for (char *f = arr; *f; f++) {
  //   if (*f == trim_chars) {
  //    continue;
  //   }
  // }
 
//     return arr;
// }

int main() {
  const char src[] = "1234*56";
  const char str[] = "AAA";
  // const char trim_chars = '*';
  // trim(src, trim_chars);
  // char arr[666666] = {0};

  // for (int i = 0; i < 8; i++){
  //   // for(size_t j = 0; j < strlen(trim_chars); j++) {
  //     if (src[i] == '*') {
  //     // arr[i]=arr[i+1];
  //     continue;
  //     }  
  //     i++;
  //     arr[i] = src[i];
  // }
  
  // printf("%s", arr);
  return 0;
}


