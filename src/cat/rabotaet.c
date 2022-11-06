// //#include "s21_cat.h"
// //#ifndef SRC_CAT_S21_CAT_H_
// //#define SRC_CAT_S21_CAT_H_
// #include <stdio.h>
// #include <stdlib.h>
// #include <getopt.h> // ? нужен ли? 
// #include <string.h> // ? нужен ли?  
// #define STR_SIZE 10000

// int voidline (char *str, int line);
// int count (char *str, int x);

// int main(int argc, char *argv[])
// {
//     int ge;
//     int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;
//     int lineCount = 1;
//     int voidLine = 0;

//     static struct option long_options[] =
//     {
//         {"number-nonblank", 0, 0, 'b'},
//         {"number", 0, 0, 'n'},
//         {"squeeze-blank" , 0, 0, 's'}
        
//     };
    
//     if (argc != 1)
//     {
//         while (((ge = getopt_long(argc, argv, "beEnstTv?", long_options, NULL)) != -1))
//         {
//             switch (ge)
//             {
//                 case 'b': b++; break;
//                 case 'v': v++; break;
//                 case 'E':
//                 case 'e': e++; break;
//                 case 'n': n++; break;
//                 case 's': s++; break;
//                 case 'T':
//                 case 't': t++; break;
//                 case '?': 
//                 default: printf("Флаг не распознан!\n"); exit(0);
//             }
//         }
//         FILE *file;
//         int filename = optind;
//         char str[STR_SIZE]; 

//         while (filename <= argc)
//         {
//             if (filename != argc)
//             {
//                 file = fopen(argv[filename], "r");
//                 if (file == NULL)
//                 {
//                     perror("Файл не найден");
//                     exit(0);
//                 }
//             }
//            // gets !
//             while (fgets(str, STR_SIZE, file))
//             {
//                 int line = strlen(str);
//                 int lineQ = voidline(str, line);

//                 int flag_e = 0;
//                 if (e != 0)
//                 {
//                     for(int i = 0; i < line; i++)
//                     {
//                         if (str[i] == '\n')
//                         {
//                             str[i] = '$';
//                             flag_e++;
//                         } 
//                     } 
//                 } 
//                 int flag_v = 0;
//                 if (v != 0)
//                 {
//                     for(int i = 0; i < line; i++)
//                     {
//                         if (str[i] < 32 && str[i] != 9 && str[i] != 10)
//                         {
//                             str[i] += 64;
//                             //printf("^");  
//                             flag_v++;
//                         } 
//                         else if (str[i] == 127)
//                         {
//                             str[i] = '?';
//                             //printf("^");
//                             flag_v++;  
//                         }
//                        //printf("%c", str[i]);
//                     }
//                 }
//                 if (s != 0)
//                 {
//                     int nowLine;
//                     for(int i = 0; i < line; i++)
//                     {
//                         if (lineQ == 0)
//                         {
//                             nowLine = 1;
//                         } else
//                         {
//                             nowLine = 0;
//                         }
//                     }
//                     if (voidLine && nowLine)
//                     {
//                         continue;
//                     }
//                     voidLine = nowLine;
//                 }
//                 if (t != 0)
//                 {
//                     for(int i = 0; i < line; i++)
//                     {
//                         int flag = 0;
//                         if (str[i] == '\t')
//                         {
//                             str[i] = '^';
//                             flag++;
//                         }
//                         //printf("%c", str[i]);
//                         // if (flag)
//                         // {
//                         //     printf("I");
//                         // }
//                     }
//                 }
//                 if (b != 0)
//                 { 
//                     for(int i = 0; i < line; i++)
//                     {
//                         if (line > 1)
//                         {
//                             count(str, lineCount);
//                             lineCount++;
//                             break;
//                             //continue;
//                         }
//                         if (line == 1 && str[i] != '\n')
//                         {
//                             char *tmp = strdup(str);
//                             sprintf(str, "%*d  ", 6,  lineCount++);
//                             strcat(str, tmp);
//                         } 
//                     }
//                 } 
//                 else if (n != 0)
//                 {
//                     count(str, lineCount);
//                     lineCount++;
//                     //  char *tmp = strdup(str);
//                     //         sprintf(str, "%*d  ", 6,  lineCount++);
//                     //         strcat(str, tmp);
//                     //         printf("*");
//                 }
//                 if (b == 0 && n == 0)
//                 {
//                     for(int i = 0; i < line; i++)
//                     {   
//                         printf("%c", str[i]);
//                         if(v != 0 && flag_v != 0) printf("^");
//                         if (e != 0 && flag_e != 0 && str[i] == '$') printf("\n");
//                         if (t != 0 && str[i] == '^') printf("I");
//                         flag_v = 0;
//                     } 
//                 } 
//                 else
//                 {
//                     printf("%s", str);
//                 }
                
                
//             }
            
//         filename++;
//         fclose(file);
//         }
//     }
//     return 0;
// }

// int voidline(char *str, int line)
// {
//     int l = 0;
//     for(int i = 0; i < line; i++)
//     {
//         if (line > 1)
//         {
//             l = 1;
//         } else if (line == 1 && str[i] != '\n')
//         {
//             l = 1;
//         } else
//         {
//             l = 0;
//         }
//     }
//     return l;
// }

// int count (char *str, int x) 
// {
//     char *temp = strdup(str);
//     sprintf(str, "%6d  ", x);
//     strcat(str, temp);
//     return x;
// }
 





#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int val;
  int test = 0;

  struct flags {
    int flag_b;
    int flag_s;
    int flag_n;
    int flag_e;
    int flag_t;
    int flag_v;
    int catOutput;
  };
  struct flags flagsCat = {0};
  struct flags *p_flags = &flagsCat;
  static struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank)", 0, 0, 's'},
  };

  if (argc != 1) {
    while (test == 0 && (val = getopt_long(argc, argv, "ETtensbv", long_options,
                                           NULL)) != EOF) {
      switch (val) {
        case 'b':
          p_flags->flag_b++;
          p_flags->flag_b = (p_flags->flag_n = 0) + 1;
          p_flags->catOutput++;
          break;
        case 'e':
        case 'E':
          p_flags->flag_e++;
          p_flags->catOutput++;
          p_flags->flag_v++;
          break;
        case 'n':
          p_flags->flag_n++;
          p_flags->flag_n = p_flags->flag_b ? 0 : 1;
          p_flags->catOutput++;
          break;
        case 's':
          p_flags->flag_s++;
          p_flags->catOutput++;
          break;
        case 'v':
          p_flags->flag_v++;
          p_flags->catOutput++;
          break;
        case 'T':
        case 't':
          p_flags->flag_t++;
          p_flags->catOutput++;
          p_flags->flag_v++;
          break;
        default:
          exit(0);
          break;
      }
    }
  }
  // на каком арументе в массиве записан файл
  int argFile = optind;
  FILE *fp;

  int string_new = 0;
  // int string_old = 0;

  // Проверка на сущетсвование файла
  if ((fp = fopen(argv[argFile], "r")) == NULL) {
    perror("Error file");
    exit(0);
  }

  char simb;
  char oldSimb = '0';
  // int examination = 0;
  int numberSimbol = 1;
  int examS = 0;
  int examT = 0;
  int examV = 0;

  int number = 1;

  while ((simb = getc(fp)) != EOF) {
    // Смотрим, есть ли смвол переноса строки
    if (simb == '\n') string_new = string_new + 1;

    // отработка флага S
    if (flagsCat.flag_s) {
      if (string_new == 1 && numberSimbol == 1) {
        string_new = 2;
        examS = 1;
      }
      if (string_new < 3) {
        examS = 1;
        if (simb != '\n') string_new = 0;
      } else if (simb != '\n') {
        string_new = 0;
        examS = 1;
      }
    }

    // отработка флага N
    if (flagsCat.flag_n && !flagsCat.flag_b) {
      if ((oldSimb == '\n' || numberSimbol == 1) && !flagsCat.flag_s) {
        printf("%6.d\t", number);
        number++;
      } else if (flagsCat.flag_s && (oldSimb == '\n' || numberSimbol == 1)) {
        if (examS) {
          printf("%6.d\t", number);
          number++;
        }
      }
    }

    // отработка флага B
    if (flagsCat.flag_b) {
      if (!flagsCat.flag_s && oldSimb == '\n' && simb != '\n') {
        printf("%6.d\t", number);
        number++;
      }
      if (flagsCat.flag_s && (oldSimb == '\n' || numberSimbol == 1)) {
        if (simb != '\n' && examS) {
          printf("%6.d\t", number);
          number++;
        }
      }
    }

    // отработка флага E
    if (flagsCat.flag_e) {
      if (!flagsCat.flag_s && simb == '\n') {
        printf("$");
      } else if (examS && simb == '\n') {
        printf("$");
      }
    }

    // отработка флага t

    if (flagsCat.flag_t) {
      if (simb == 9) examT = 1;
    }

    // отработка флага V

    if (flagsCat.flag_v) {
      if (simb >= 0 && simb != 9 && simb != 10 && simb < 32) {
        printf("^%c", simb + 64);
        examV = 1;
      } else if (simb == 127) {
        printf("^?");
        examV = 1;
      }
    }

    // ВЫВОД В КОНСОЛЬ
    if (flagsCat.flag_s && examS) {
      if (examT) {
        printf("^I");
        examS = 0;
        examT = 0;
      } else if (examV) {
        examV = 0;
      } else {
        printf("%c", simb);
        examS = 0;
      }
    } else if (!flagsCat.flag_s) {
      if (examT) {
        printf("^");
        printf("I");
        examT = 0;
      } else if (examV) {
        examV = 0;
      } else {
        printf("%c", simb);
      }
    }
    oldSimb = simb;
    numberSimbol++;
  }

  fclose(fp);
  return 0;
}
