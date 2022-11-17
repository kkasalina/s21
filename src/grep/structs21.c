#include "s21_grep.h"

int main(int argc, char* argv[]) {
  char gr;
  char shablon[SIZE] = {0};
  all_flags unit = {0};
  count inv; // = {0, 0};
  
  while (((gr = getopt_long(argc, argv, short_options, long_options, NULL)) !=
          -1)) {
    flags(gr, argv, &unit, shablon);
  }
  shablon_str(argv, &unit, shablon);
  input_file_open(argv, optind, argc, &unit, &inv, shablon);
  return 0;
}

// чтение флагов
void flags(char gr, char** argv, all_flags *unit, char* shablon) {
  
  switch (gr) {
    case 'e':
      unit->e = 1;
      shablon_str(argv, unit, shablon);
      break;
    case 'i':
      unit->i = 1;
      break;
    case 'v':
      unit->v = 1;
      break;
    case 'c':
      unit->c = 1;
      break;
    case 'l':
      unit->l = 1;
      break;
    case 'n':
      unit->n = 1;
      break;
    case 'h':
      unit->h = 1;
      break;
    case 's':
      unit->s = 1;
      break;
    case 'f':
      unit->f = 1;
      shablon_str(argv, unit, shablon);
      break;
    case 'o':
      unit->o = 1;
      break;
    case '?':
    default:
      fprintf(stderr, "Флаг не найден\n");  // оставить так?
      exit(1);
  }
}
// чтение шаблона из потока ввода
void shablon_str(char** argv, all_flags *unit, char* shablon) {
  char str[SIZE] = {0};
  if (unit->e == 0 && unit->f == 0) {
    snprintf(shablon, sizeof(shablon), "%s", argv[optind]);
    optind++;
  }
  if (unit->e != 0 && unit->f == 0) {
    if (shablon[0] == 0)
      snprintf(shablon, sizeof(shablon), "%s", optarg);
    else {
      snprintf(str, sizeof(shablon), "|%s", optarg);
      strcat(shablon, str);
    }
  }
  if (unit->f) {
    Flag_F(str, unit, shablon);
  }
}

// открытие и проверка файла, доработать
void input_file_open(char** argv, int optind, int argc, all_flags *unit, count *inv, char* shablon) {
  FILE* file;
  int filename = optind;
  char* str_f;
  while ((str_f = argv[filename]) != NULL) {
    if (strcmp(str_f, "-") != 0 || str_f != 0) {
      if ((file = fopen(argv[filename], "r"))) {
        reg_func(file, str_f, argc, unit, inv, shablon);
      } else {
        if (unit->s == 0) {
          perror("Файл не найден");
          exit(1);
        }
      }
    }
    filename++;
  }
}

// функция взаимодействия флагов и печать
void reg_func(FILE* file, char* str_f, int argc, all_flags *unit, count *inv, char* shablon) {
  int line = 0;
  int done = 0;
  inv->count = 0;
  inv->mom = 0;
  char* pattern = NULL;
  Reg_start(unit, shablon);
  pattern = (char*)malloc(
      leght + 1);  // динамическое выделение памяти под символьную строку
  if (pattern == NULL) exit(1);

  while ((line = getline(&pattern, &leght, file) != EOF)) {
    inv->count++;
    if ((inv->mom = regexec(&rege, pattern, match_n, match_p, 0)) == 0) {
      done++;
    }
    if (pattern[strlen(pattern) - 1] == 10) {
      pattern[strlen(pattern) - 1] = 0;
    }

    if (!unit->c) {
      if (inv->mom == 0 && !unit->v && !unit->l && !unit->o) {
        Flag_No_H(argc, str_f, unit);
        if (unit->n) {
          printf("%d:", inv->count);
        }
        printf("%s\n", pattern);
      }
      if (inv->mom != 0 && unit->v && !unit->l) {  // нужно ли добавить флаг О?
        Flag_No_H(argc, str_f, unit);
        if (unit->n) {
          printf("%d:", inv->count);
        }
        printf("%s\n", pattern);
      }
      if (inv->mom == 0 && !unit->v && !unit->l && unit->o) {
        Flag_No_H(argc, str_f, unit);
        if (unit->n) {
          printf("%d:", inv->count);
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

  if (unit->c) {
    if (!unit->v && !unit->l) {
      Flag_No_H(argc, str_f, unit);
      printf("%d\n", done);
    }
    if (unit->v && !unit->l) {
      Flag_No_H(argc, str_f, unit);
      printf("%d\n", (inv->count - done));
    }
    if (unit->v && unit->l) {
      Flag_No_H(argc, str_f, unit);
      if ((inv->count - done) > 0) {
        printf("%d\n", 1);  // зачем?
      } else {
        printf("%d\n", 0);
      }
    }
    if (!unit->v && unit->l) {
      Flag_No_H(argc, str_f, unit);
      if (done > 0) {
        printf("%d\n", 1);
      } else {
        printf("%d\n", 0);
      }
    }

  }

  if (unit->l != 0 && done > 0) {
    printf("%s\n", str_f);
  }
  if (unit->v != 0 && unit->l && done == 0) {
    printf("%s\n", str_f);
  }

  if (pattern) {
    free(pattern);
  }
  regfree(&rege);
}

void Flag_F(char* str, all_flags *unit, char* shablon) {
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
      if (unit->s == 0) {
        perror("Файл не найден");
        exit(1);
      }
      fclose(f_file);  // нужно ли закрывать?
    }
  }
}

void Reg_start(all_flags *unit, char* shablon) {
  int a;
  if (unit->i) {
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

void Flag_No_H(int argc, char* str_f, all_flags *unit) {
  if ((argc - optind) > 1 && !unit->h) {
    printf("%s:", str_f);
  }
}