#include "s21_grep.h"

int main(int argc, char* argv[]) {
  //if (argc != 1) {
   
    while (((gr = getopt_long(argc, argv, short_options, long_options, NULL)) !=
                 -1)) {
                   //  printf("000");
      flags(gr, argv);
      //printf("111");
    }    
    //printf("999");
    shablon_str(argv);
    input_file_open(argc, argv, optind);
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
      //printf("%d", e);
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
   // printf("333");
  char str[SIZE];
  // char buf[SIZE];
  if (e == 0 && f == 0) {
    snprintf(shablon, SIZE, "%s", argv[optind]);  // можно optarg?
   // printf("444");
   optind++;
  }
  if (e != 0 && f == 0) {
    if (shablon[0] == 0)
      snprintf(shablon, SIZE, "%s", optarg);  // нужно optarg
    else {
      snprintf(str, SIZE, " %s", optarg);  // нужно optarg and | ?
      strcat(shablon, str);
    }
 
  }
  if (f) {
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
   // printf("555");
  FILE* file;
  int filename = optind;
  char* str;
    while ((str =argv[filename]) != NULL) {
        if (str) {
            file = fopen(argv[filename], "r");
            if (file == NULL) {
                if (s == 0) {
                //  printf("666");
                perror("Файл не найден");
                exit(1);
                }
            }
            //printf("777");
            reg_func(argc, file, str);
        }
        filename++;
        fclose(file);
    }
}
// функция взаимодействия флагов и печать
void reg_func(int argc, FILE* file, char* str) {
//printf("888");
  int a;
  regex_t rege; // хранениe скомпилированного регулярного выражения
  size_t match_n = 4, leght = 1000; // длина массива структуры regmatch_t
  regmatch_t match_p[4]; 
  int out, mom;
  int done = 0;

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

  char* pattern = NULL;
  pattern = (char*) malloc(leght + 1); // динамическое выделение памяти под символьную строку
  if (pattern == NULL) exit (1);
  //printf("111222333");
  
  // if (e && !i) {
  //   if (a = regcomp(&rege, shablon, REG_EXTENDED) == 0)  
  //     printf("%s", rege);
  //   }  

    while ((out = getline(&pattern, &leght, file) != EOF)) 
    {
        if (mom = regexec(&rege, pattern, match_n, match_p, 0) != 0) { 
          done++;
        }

    } 
    // if (tmp_line[strlen(tmp_line) - 1] == 10) {
    //   tmp_line[strlen(tmp_line) - 1] = 0;
    // } - зачем это?


// перенести сообщение об ошибке из-за e или i
  

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