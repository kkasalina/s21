#include "s21_cat.h"

#define STR_SIZE 10000

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        while (((ge = getopt_long(argc, argv, "+beEnstTv?", long_options, NULL)) != -1))
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
            }
        }
        FILE *file;
        int filename = optind;
            
            
        while (filename < argc)
        {
            file = fopen(argv[filename], "r");
            if (file == NULL)
            {
                perror("Файл не найден");
                exit(1);
            }

            char f;
            int size = 0;
            while ((f = getc(file)) != EOF)
            {
                size++;
            
            } 
            fclose(file);
            file = fopen(argv[filename], "r");
           
            char lastSim = '\n';
            char lastLastSim = '0';
            char c = '0';
            char flag_t = '0';
            int flag_v = 0;
            int flag_n = 1;
            int flag_b = 1;
            

            for (int symCount = 0; (c = getc(file)) != EOF; symCount++)
            {   
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
                    if (symCount == 0 || lastSim == 10)
                    {
                        printf("%6d\t", flag_n);
                        flag_n++;
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
                    if (b != 0 && lastSim == '\n' && c != '\n') printf("%6d\t", flag_b++);
                    if (v != 0 && flag_v != 0) printf("^");

                    if (n == 0 || flag_v != 0) printf("%c", c); 

                    if (t != 0 && c == '^' && flag_t == '\t') printf("I");
                
                lastLastSim = lastSim;
                lastSim = c;
                endStr = 0;
                flag_t = '0';
                flag_v = 0;
                if (symCount == size - 1) flag_n = 1;
            }
            
        filename++;
        fclose(file);
        }
    }
    return 0;
}