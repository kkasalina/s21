#include "s21_grep.h"

int main(int argc, char *argv[]) {
    if (argc != 1)
    {
        while ((gr = getopt(argc, argv, "+eivclnhsfo?"))) {
            flags (gr, argv);
        }
        shablon_str(argv);
        input_file_open(argc, argv, optind);
    }
    return 0;
}  
// чтение флагов
void flags (int gr, char** argv)
{
    switch(gr) {
        case 'e': e++; shablon_str(argv); break;
        case 'i': i++; break;
        case 'v': v++; break;
        case 'c': c++; break;
        case 'l': l++; break;
        case 'n': n++; break;
        case 'h': h++; break;
        case 's': s++; break;
        case 'f': f++; shablon_str(argv); break;
        case 'o': o++; break;
        case '?':
        default: printf("Флаг не распознан!\n"); exit(1);
    }
}
// чтение шаблона из потока ввода
void shablon_str(char** argv)
{
    char str[SIZE];
    char buf[SIZE];
    if (e == 1 && f == 0)
    {
        sprintf(shablon, SIZE, "%s", );
    }
}
// открытие и проверка файла, доработать 
void input_file_open (int argc, char** argv, int optind)
{
    FILE *file;
    int filename = optind;
    char *str;
    
        for (str = argv[filename]; str != NULL; filename++)
        {
            if (str)
            {
                file = fopen(argv[filename], "r");
                if (file == NULL) 
                {
                    if (s == 0)
                    {
                        perror("Файл не найден");
                        exit(1);  
                    }
                }
                void big_func ();
            }
            fclose(file); 
        }
}
// функция взаимодействия флагов и печать
void big_func ();