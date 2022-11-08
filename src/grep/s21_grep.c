#include "s21_grep.h"

int main(int argc, char* argv[]) {
  if (argc != 1) {
    while ((gr = getopt_long(argc, argv, "+e:f:ivclnhso?", long_options, NULL) !=
                 -1)) {
      flags(gr, argv);
    }
    shablon_str(argv);
    input_file_open(argc, argv, optind);
    // big_func();
  }
  return 0;
}
// чтение флагов
void flags(int gr, char** argv) {
  switch (gr) {
    case 'e':
      e++;
      shablon_str(argv);
      break;
    case 'i':
      i++;
      break;
    case 'v':
      v++;
      break;
    case 'c':
      c++;
      break;
    case 'l':
      l++;
      break;
    case 'n':
      n++;
      break;
    case 'h':
      h++;
      break;
    case 's':
      s++;
      break;
    case 'f':
      f++;
      shablon_str(argv);
      break;
    case 'o':
      o++;
      break;
    case '?':
    default:
      printf("Флаг не распознан!\n");
      exit(1);
  }
}
// чтение шаблона из потока ввода
void shablon_str(char** argv) {
  char str[SIZE];
  // char buf[SIZE];
  if (e == 0 && f == 0) {
    snprintf(shablon, SIZE, "%s", argv[optind++]);  // можно optarg?
  }
  if (e != 0 && f == 0) {
    if (optarg == 0 || !shablon[0])
      snprintf(shablon, SIZE, "%s", argv[optind]);  // нужно optarg
    else {
      snprintf(str, SIZE, " %s", argv[optind]);  // нужно optarg and | ?
      strcat(shablon, str);
    }
  }
  if (f && !e) {
    char f_pattern[SIZE] = {0};
    FILE* f_file;
    char* f_str = optarg;
    if (f_file == NULL) {
      if (s == 0) {
        perror("Файл не найден");
        exit(1);
      }
    } else if (f_file) {
      f_file = fopen(f_str, "r");
      while ((fgets(f_pattern, SIZE, f_file)) != NULL)  // NULL?
      {
        // if (f_pattern[strlen(f_pattern) - 1] == 10) {
        // f_pattern[strlen(f_pattern) - 1] = 0;
        // }
        if (optarg == 0 || !shablon[0])
          snprintf(shablon, SIZE, "%s", f_pattern);  // нужно optarg
        else {
          snprintf(str, SIZE, " %s", f_pattern);  // нужно optarg and | ?
          strcat(shablon, str);
        }
        // счетчик i++ ?
      }
    }
    fclose(f_file);  // нужно ли закрывать?
  }
}
// открытие и проверка файла, доработать
void input_file_open(int argc, char** argv, int optind) {
  FILE* file;
  int filename = optind;
  char* str;

  for (str = argv[filename]; str != NULL; filename++) {
    if (str) {
      file = fopen(argv[filename], "r");
      if (file == NULL) {
        if (s == 0) {
          perror("Файл не найден");
          exit(1);
        }
      }
      void big_func();
    }
    fclose(file);
  }
}
// функция взаимодействия флагов и печать
void big_func(int argc, FILE* file, char** str) {
   if (e) {

   }
}