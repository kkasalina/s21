#include "s21_grep.h"

int main(int argc, char* argv[]) {
  // if (argc != 1) {

  while (((gr = getopt_long(argc, argv, short_options, long_options, NULL)) !=
          -1)) {
    //  printf("000");
    flags(gr, argv);
    // printf("111");
  }
  // printf("999");
  shablon_str(argv);
  input_file_open(argv, optind, argc);  // argc,
  // reg_func();
  // }
  return 0;
}

// чтение флагов
void flags(int gr, char** argv) {
  // printf("222");
  switch (gr) {
    case 'e':
      e++;
      // printf("%d", e);
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
  // printf("333");  // char buf[SIZE];

  char str[SIZE];
  if (e == 0 && f == 0) {
    snprintf(shablon, sizeof(shablon), "%s", argv[optind]);
    // printf("444");
    optind++;
  }
  if (e != 0 && f == 0) {
    if (shablon[0] == 0)
      snprintf(shablon, sizeof(shablon), "%s", optarg);  // нужно optarg
    else {
      snprintf(str, sizeof(shablon), "|%s", optarg);
      strcat(shablon, str);
    }
  }
  if (f) {
    char f_pattern[SIZE] = {0};
    FILE* f_file;
    char* f_str = optarg;
    if (f_file != NULL) {
      if (f_file) {
        f_file = fopen(f_str, "r");
        while ((fgets(f_pattern, SIZE, f_file)) != NULL)
        {
          if (f_pattern[strlen(f_pattern) - 1] == 10) {
            f_pattern[strlen(f_pattern) - 1] = 0;
          }
          if (optarg == 0 || !shablon[0])
            snprintf(shablon, sizeof(shablon), "%s", optarg);  
          else {
            snprintf(str, sizeof(shablon), "|%s",
                     optarg);
            strcat(shablon, str);
          }
          // счетчик i++ ?
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
  // printf("555");
  FILE* file;
  int filename = optind;
  char* str_f;
  while ((str_f = argv[filename]) != NULL) {
    if (strcmp(str_f, "-") != 0 || str_f != 0) {
      if ((file = fopen(argv[filename], "r"))) {
        reg_func(file, str_f, argc);  // str argc,
        fclose(file);
      } else {
        if (s == 0) {
          perror("Файл не найден");
          exit(1);
        }
      }
      // printf("777");
    }
    filename++;
  }
}

// функция взаимодействия флагов и печать
void reg_func(FILE* file, char* str_f, int argc) {  //,
                                                    //  printf("888");
  int a;
  regex_t rege;  // хранениe скомпилированного регулярного выражения
  size_t match_n = 4, leght = 1000;  // длина массива структуры regmatch_t
  regmatch_t match_p[4];
  int line, mom;
  int done = 0, count = 0;
  char* pattern = NULL;

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
  // pattern = (char *)calloc(leght, sizeof(char));
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
    if (!mom && !v && !c && !l) {
      if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
      if (n) {
        printf("%d:", count);
      }
      printf("%s\n", pattern);
    }
    if (mom && v) {
      if ((argc - optind) > 1 && !h) {
        printf("%s:", str_f);
      }
      printf("%s\n", pattern);
    }
    if (f) {
      printf("%s\n", pattern);
    }
  }
  if (l) {
    printf("%s\n", str_f);
  }
  if (c) {
    printf("%d", done);
  }

  if (pattern) {
    free(pattern);
  }

  regfree(&rege);
}
