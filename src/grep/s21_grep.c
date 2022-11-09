#include "s21_grep.h"

int main(int argc, char* argv[]) {
  if (argc != 1) {
    while ((gr = getopt_long(argc, argv, "+e:f:ivclnhso?", long_options, NULL) !=
                 -1)) {
      flags(gr, argv);
    }
    shablon_str(argv);
    input_file_open(argc, argv, optind);
    // reg_func();
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
      void reg_func();
    }
    fclose(file);
  }
}
// функция взаимодействия флагов и печать
void reg_func(int argc, FILE* file, char** str) {

  int a;
  regex_t rege; // хранениe скомпилированного регулярного выражения
  size_t match_n = 4; // длина массива структуры regmatch_t
  regmatch_t match_p[4];
  int leght = 1000;
  int out;
  int gone = 0;

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


  char * pattern = (char*) malloc(leght + 1); // динамическое выделение памяти под символьную строку
  if (pattern == NULL) exit (1);
    while ((out = getc(file) != EOF))
    {
        if (regexec(&rege, pattern, match_n, match_p, 0) == 0) gone++;
    }



// перенести сообщение об ошибке из-за e или i
// if (e && !i) {
//     a = regcomp(&rege, shablon, REG_EXTENDED) 
// }    

//output_flags(file, pattern, rege, match_n, match_p);
    //regexec
    free(pattern);
    regfree(&rege);
}



// void output_flags (FILE* file, char *pattern, regex_t rege, size_t match_n,
//                     regmatch_t match_p[4])
// {
//     int out;
//     while ((out = getc(file)) != EOF)
//     {
//     }
// }