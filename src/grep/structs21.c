#include "s21_grep.h"

int main(int argc, char* argv[]) {
  
  flagsA all = {0};
  int gr;
  while (((gr = getopt_long(argc, argv, short_options, long_options, NULL)) !=
          -1)) {
    flags(gr, argv, &all);
    
  }
  
  shablon_str(argv, &all);
  input_file_open(argv, optind, argc, &all);
  return 0;
}

// чтение флагов
void flags(int gr, char** argv, flagsA *all) {
  switch (gr) {
    case 'e':
      all->e = 1;
      shablon_str(argv, all);
      break;
    case 'i':
      all->i = 1;
      break;
    case 'v':
      all->v = 1;
      break;
    case 'c':
      all->c = 1;
      break;
    case 'l':
      all->l = 1;
      break;
    case 'n':
      all->n = 1;
      break;
    case 'h':
      all->h = 1;
      break;
    case 's':
      all->s = 1;
      break;
    case 'f':
      all->f = 1;
      shablon_str(argv, all);
      break;
    case 'o':
      all->o = 1;
      break;
    case '?':
    default:
      fprintf(stderr, "Флаг не найден\n");  // оставить так?
      exit(1);
  }
}
// чтение шаблона из потока ввода
void shablon_str(char** argv, flagsA *all) {
  
  char shablon[SIZE];
  char str[SIZE] = {0};
  if (all->e == 0 && all->f == 0) {
    snprintf(shablon, sizeof(shablon), "%s", argv[optind]);
    optind++;
  }
  if (all->e != 0 && all->f == 0) {
    if (shablon[0] == 0)
      snprintf(shablon, sizeof(shablon), "%s", optarg);
    else {
      snprintf(str, sizeof(shablon), "|%s", optarg);
      strcat(shablon, str);
    }
  }
  if (all->f) {
    Flag_F(str, all);
  }
}

// открытие и проверка файла, доработать
void input_file_open(char** argv, int optind, int argc, flagsA *all) {
  
  FILE* file;
  int filename = optind;
  char* str_f;
  while ((str_f = argv[filename]) != NULL) {
    if (strcmp(str_f, "-") != 0 || str_f != 0) {
      if ((file = fopen(argv[filename], "r"))) {
        reg_func(file, str_f, argc, all);
        fclose(file);
      } else {
        if ((all->s) == 0) {
          perror("Файл не найден");
          exit(1);
        }
      }
    }
    filename++;
  }
}

// функция взаимодействия флагов и печать
void reg_func(FILE* file, char* str_f, int argc, flagsA *all) {
  // printf("%d %d %d %d %d %d %d %d %d %d\n", all->e, all->i, all->v, all->c, all->l, all->n, all->h, all->s, all->f, all->o);
  int line, mom;
  int done = 0, count = 0;
  char* pattern = NULL;
  Reg_start(all);
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

    // if (!all->c) {
      if (mom == 0 && !all->v && !all->l && !all->o && !all->c) {
        Flag_No_H(argc, str_f, all);
        if (all->n) {
          printf("%d:", count);
        }
        printf("%s\n", pattern);
      }
      if (mom != 0 && all->v && !all->l && !all->c) {
        Flag_No_H(argc, str_f, all);
        if (all->n) {
          printf("%d:", count);
        }
        printf("%s\n", pattern);
      }
      if (mom == 0 && !all->v && !all->l && all->o && !all->c) {
        Flag_No_H(argc, str_f, all);
        if (all->n) {
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
    // }
  }

  // if (all->c) {
    if (!all->v && !all->l && all->c) {
      Flag_No_H(argc, str_f, all);
      printf("%d\n", done);
    }
    if (all->v && !all->l && all->c) {
      Flag_No_H(argc, str_f, all);
      printf("%d\n", (count - done));
    }
    if (!all->v && all->l && all->c) {
      Flag_No_H(argc, str_f, all);
      if (done > 0) {  // зачем?
        printf("%d\n", 1);
      } else {
        printf("%d\n", 0);
      }
    }
    if (all->v && all->l && all->c) {
      Flag_No_H(argc, str_f, all);
      if ((count - done) > 0) {
        printf("%d\n", 1);  // зачем?
      } else {
        printf("%d\n", 0);
      }
    // }
  }

  if (all->l != 0 && done > 0) {
    printf("%s\n", str_f);
  }
  if (all->v != 0 && all->l && done == 0) {
    printf("%s\n", str_f);
  }
  if (pattern) {
    free(pattern);
  }
  regfree(&rege);
}

void Flag_F(char* str, flagsA *all) {
  char f_pattern[9000] = {0};
  FILE* f_file;
  char* f_str;
  f_str = optarg;
  if (f_str != NULL) {
    if ((f_file = fopen(f_str, "r"))) {
      while ((fgets(f_pattern, 9000, f_file)) != NULL) {
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
      if (all->s == 0) {
        perror("Файл не найден");
        exit(1);
      }
      fclose(f_file);  // нужно ли закрывать?
    }
  }
}

void Reg_start(flagsA *all) {
  int a;
  if (all->i) {
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
}

void Flag_No_H(int argc, char* str_f, flagsA *all) {
  if ((argc - optind) > 1 && !(all->h)) {
    printf("%s:", str_f);
  }
}
