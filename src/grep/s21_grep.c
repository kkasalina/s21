#include "s21_grep.h"

int main(int argc, char* argv[]) {
  while (((gr = getopt_long(argc, argv, short_options, long_options, NULL)) !=
          -1)) {
    flags(gr, argv);
  }
  shablon_str(argv);
  input_file_open(argv, optind, argc);  // argc,
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
      fprintf(stderr, "Флаг не найден\n");  // оставить так?
      exit(1);
  }
}
// чтение шаблона из потока ввода
void shablon_str(char** argv) {
  char str[SIZE] = {0};
  if (e == 0 && f == 0) {
    snprintf(shablon, sizeof(shablon), "%s", argv[optind]);
    optind++;
  }
  if (e != 0 && f == 0) {
    if (shablon[0] == 0)
      snprintf(shablon, sizeof(shablon), "%s", optarg);
    else {
      snprintf(str, sizeof(shablon), "|%s", optarg);
      strcat(shablon, str);
    }
  }
  if (f) {
    char f_pattern[9000] = {0};
    FILE* f_file;
    char* f_str;
    f_str = optarg;
    if (f_str != NULL) {
      if ((f_file = fopen(f_str, "r"))) {
        while ((fgets(f_pattern, SIZE, f_file)) != NULL) {
          if (f_pattern[strlen(f_pattern) - 1] == 10) {
            f_pattern[strlen(f_pattern) - 1] = 0;
          }
          if (shablon[0] == 0)
            snprintf(shablon, sizeof(shablon), "%s", f_pattern);
          else {
            snprintf(str, sizeof(shablon), "|%s", f_pattern);
            strcat(shablon, str);
          }
        }
      } else {
        if (s == 0) {
          perror("Файл не найден");
          exit(1);
        }
        fclose(f_file);  // нужно ли закрывать?
      }
    }
  }
}

// открытие и проверка файла, доработать
void input_file_open(char** argv, int optind, int argc) {
  FILE* file;
  int filename = optind;
  char* str_f;
  while ((str_f = argv[filename]) != NULL) {
    if (strcmp(str_f, "-") != 0 || str_f != 0) {
      if ((file = fopen(argv[filename], "r"))) {
        reg_func(file, str_f, argc);
      } else {
        if (s == 0) {
          perror("Файл не найден");
          exit(1);
        }
      }
    }
    filename++;
  }
}

// функция взаимодействия флагов и печать
void reg_func(FILE* file, char* str_f, int argc) {
  int a;
  regex_t rege;  // хранениe скомпилированного регулярного выражения
  int line, mom;
  char* pattern = NULL;
  regmatch_t match_p[4];
  int done = 0, count = 0;
  size_t match_n = 4, leght = 1000;  // длина массива структуры regmatch_t
  /*____________________________________________________________________
   regmatch_t - это тип данных структуры, который определен
   в regex.h ::
   typedef struct
   {
      regoff_t rm_so;
      regoff_t rm_eo;
   } regmatch_t;
   Элемент rm_so сохраняет начальную позицию соответствующей
   текстовой строки в целевой строке, а rm_eo сохраняет
   конечную позицию
  ____________________________________________________________________*/

  if (i) {
    if ((a = regcomp(&rege, shablon, REG_ICASE)) != 0) {
      printf("failed - %d", a);
      exit(1);
    }
  } else {
    if ((a = regcomp(&rege, shablon, REG_EXTENDED)) != 0) {
      printf("failed - %d", a);
      exit(1);
    }
  }
  pattern = (char*)malloc(
      leght + 1);  // динамическое выделение памяти под символьную строку
  if (pattern == NULL) exit(1);

  while ((line = getline(&pattern, &leght, file) != EOF)) {
    count++;
    if ((mom = regexec(&rege, pattern, match_n, match_p, 0)) == 0) {
      done++;
    }
    if (pattern[strlen(pattern) - 1] == 10) {
      pattern[strlen(pattern) - 1] = 0;
    }

    if (!c) {

      if (mom == 0 && !v && !l && !o) {
      if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
      if (n) {
        printf("%d:", count);
      }
      printf("%s\n", pattern);
    }
    if (mom != 0 && v && !l) {  // нужно ли добавить флаг О?
      if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
      if (n) {
        printf("%d:", count);
      }
      printf("%s\n", pattern);
    }
    if (mom == 0 && !v && !l && o) {
      if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
      if (n) {
        printf("%d:", count);
      }
      char* o_str = pattern;
      for (unsigned int l = 0; l < strlen(o_str); l++) {
        if (regexec(&rege, o_str, match_n, match_p, 0)) {
          break;
        }
        unsigned int end = 0;
        for (size_t g = 0; g <= match_n; g++) {
          if (match_p[g].rm_so == -1) {
            break;
          }
          if (g == 0) {
            end = match_p[g].rm_eo;
          }
          char buffer[strlen(o_str) + 1];
          strcpy(buffer, o_str);
          buffer[match_p[g].rm_eo] = 0;
          printf("%s\n", (buffer + match_p[g].rm_so));
        }
        o_str += end;
      }
    }
    }    
  }
  
if (c) {
  if (!v && !l ) {
    if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
    printf("%d\n", done);
  }
  if (v && !l) {
      if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
    printf("%d\n", (count - done));
  }
  if (!v && l) {
          if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
    if (done > 0) { // зачем?
      printf("%d\n", 1);
    } else {
      printf("%d\n", 0);
    }
   }
  if (v && l) {
    if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
    if ((count - done) > 0) { 
      printf("%d\n", 1); // зачем?
    } else {
      printf("%d\n", 0);
    }
  }
}


  if (l != 0 && done > 0) {
    printf("%s\n", str_f);
  }
  if (v != 0 && l && done == 0) {
    printf("%s\n", str_f);
  }

  if (pattern) {
    free(pattern);
  }
  regfree(&rege);
}