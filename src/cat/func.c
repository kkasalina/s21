// #ifndef SRC_CAT_S21_CAT_H_
// #define SRC_CAT_S21_CAT_H_
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int ge;
int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;

static struct option long_options[] =
    {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank" , 0, 0, 's'}
        
    };

void switch_f (int ge);
void big_func (int argc, char *argv[], int b, int e, int n, int s, int t, int v);
void file_open (int argc, char* argv[], int size, int filename);
void size_f (FILE* file, int size);

#define STR_SIZE 10000

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        while (((ge = getopt_long(argc, argv, "+beEnstTv?", long_options, NULL)) != -1))
        {
             switch_f (ge);
        }
        printf("1111");
        big_func (argc, argv, b, e, n, s, t, v);
    printf("2222");
    }
    return 0;
}

void switch_f (int ge)
{
    switch (ge)
    {
        case 'b': b++; break;
        case 'v': v++; break;
        case 'E':
        case 'e': e++; break;
        case 'n': n++; break;
        case 's': s++; break;
        case 'T':
        case 't': t++; break;
        case '?': 
        default: printf("Флаг не распознан!\n"); exit(1);
    }  printf("333");
}
void big_func (int argc, char *argv[], int b, int e, int n, int s, int t, int v)
{
         printf("4444");
            int size = 0;
            int filename = 0;
            FILE* file;
            file_open (argc, argv, size, filename);
            file = fopen(argv[filename], "r");
            char lastSim = '\n';
            char lastLastSim = '0';
            char c = '0';
            char flag_t = '0';
            int flag_v = 0;
            for (int symCount = 0; (c = getc(file)) != EOF; symCount++)
            {   printf("5555");
                int endStr = 0;
                if (c == '\n') endStr += 1;
                if (s)
                {
                    if (symCount == 1 && lastSim == '\n' && c == '\n') 
                    {
                        continue;
                        
                    }
                    if (lastLastSim == '\n' && lastSim == '\n' && c == '\n')
                    {
                        continue;
                    }
                }
                if (t != 0)
                {
                    v = 1;
                    if (c == '\t')
                    {   
                        flag_t = c;
                        c = '^';
                    }
                }
                if (b != 0) n = 0;
                if (n != 0 && b == 0)
                {
                    if (symCount == 0)
                    {
                        printf("%6d\t", n);
                        n++;
                    }
                }
                if (v == 1)
                {
                    if (c < 32 && c != 9 && c != 10)
                    {
                         c += 64;   
                        flag_v++;
                    }
                     if (c == 127)
                    {
                         c = '?';
                        flag_v++;
                        
                    }
                }   
                if (e != 0 && c == '\n')
                {
                    v = 1;
                    printf("$");
                }  
                   
                    if (n != 0 && flag_v == 0 ) printf("%c", c);
                    if (n != 0 && endStr != 0 && (symCount != size - 1 && c == '\n'))  printf("%6d\t", n++);
                    if (b != 0 && lastSim == '\n' && c != '\n') printf("%6d\t", b++);
                    if (v != 0 && flag_v != 0) printf("^");

                    if (n == 0 || flag_v != 0) printf("%c", c); 

                    if (t != 0 && c == '^' && flag_t == '\t') printf("I");
                
                lastLastSim = lastSim;
                lastSim = c;
                endStr = 0;
                flag_t = '0';
                flag_v = 0;
                if (symCount == size - 1) n = 1;
            }
            filename++;
            fclose(file);
}
void file_open (int argc, char* argv[], int size, int filename)
{   printf("6666");
        FILE *file;
        filename = optind;
        while (filename < argc)
        {
            file = fopen(argv[filename], "r");
            if (file == NULL)
            {
                perror("Файл не найден");
                exit(1);
            }
        }
            size_f(file, size);
        
}
void size_f (FILE* file, int size)
{ printf("777");
    char f;
    while ((f = getc(file)) != EOF)
    {
        size++;
    } 
    fclose(file);
}