#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ДОБАВИТЬ ВЕЗДЕ S21_
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void *to_upper(const char *str) { 

  char *arr = NULL;
  int inerror = 0;
  if (str) {
    arr = (char*)calloc((strlen(str) + 1), sizeof(char));
    if (arr == NULL) {
      inerror = 1;
    }
    for (size_t i = 0; i <= strlen(arr); i++) {
      arr[i] = str[i];
    }
    if (arr) {
      for (char *f = arr; *f; f++) {
        if(*f >= 97 && *f <= 122) {
          *f -=  32;
        }
      }
    }
  } else {
    inerror = 1;
  }
  free(arr);
  return inerror? NULL : (void*)arr;
}

void *to_lower(const char *str) { 

  char *arr = NULL;
  int inerror = 0;
  if (str) {
    arr = (char*)calloc((strlen(str) + 1), sizeof(char));
    if (arr == NULL) {
      inerror = 1;
    }
    for (size_t i = 0; i <= strlen(arr); i++) {
      arr[i] = str[i];
    }
    if (arr) {
      for (char *f = arr; *f; f++) {
        if(*f >= 65 && *f <= 90) {
          *f +=  32;
        }
      }
    }
  }  else {
    inerror = 1;
  }
  free(arr);
  return inerror? NULL : (void*)arr;
}

void *insert(const char *src, const char *str, size_t start_index) {
                                                             
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

void *trim(const char *src, const char *trim_chars) {
  char *arr = NULL;
  char *chars = " \t\n\v\r\f\0";
  int inerror = 0;
  if (src) {
    arr = (char*) calloc((strlen(src) + 1), sizeof(char));
    if (arr == NULL) inerror++;

  strcat(arr, src);
  int inbreak = 0;
  if (trim_chars == NULL)  trim_chars = chars;
  for (size_t i = 0; i < strlen(src); i++) {
    for (size_t j = 0; j < strlen(trim_chars); j++) {
      if (src[i] == trim_chars[j]) {
        int h = 0;
        while (arr[h]) {
          arr[h] = arr[h + 1];
          h++; 
        }
        break;
      }
      if(j == strlen(trim_chars) - 1 && src[i] != trim_chars[strlen(trim_chars)]) { 
        inbreak++; 
      }
    } 
    if (inbreak) break;
  }

  for (size_t i = strlen(arr)-1; i > 0 ; i--) {  
    inbreak = 0;
    for (size_t j = 0; j < strlen(trim_chars); j++) {
      if (arr[i] == trim_chars[j]) {
        arr[i] = '\0';
        break;
      }
      if(j == strlen(trim_chars) - 1 && src[i] != trim_chars[strlen(trim_chars)]) { 
        inbreak++; 
      }
    } 
    if (inbreak) break;
  }  
  } else {
    inerror++;
  }
  free(arr);
  return inerror? NULL : (void*)arr;
}


int main() {
  const char src[] = "\t\tnfknkn\t\ngkbmlkgbjkld\t\t";
  const char *trim_chars = " \t\n\v\r\f\0";
  printf("%s", (char *)trim(src, trim_chars));
  return 0;
}
