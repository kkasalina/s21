#include "s21_grep.h"

int main(int argc, char *argv[]) {
int gr;
int e = 0, i = 0, v = 0, c = 0, l = 0, n = 0, h = 0, s = 0, f = 0, o = 0;
while ((gr = getopt(argc, argv, "eivclnhsfo?"))) {
    switch(gr) {
        case 'e': e++; break;
        case 'i': i++; break;
        case 'v': v++; break;
        case 'c': c++; break;
        case 'l': l++; break;
        case 'n': n++; break;
        case 'h': h++; break;
        case 's': s++; break;
        case 'f': f++; break;
        case 'o': o++; break;
        case '?':
        default: printf("Флаг не распознан!\n"); exit(0);

    }
    

    FILE *file;
    int filename = optind;
    int strSize = 10000;
    char str[strSize];
    file = fopen(argv[filename], "r");
    if (file == NULL) {
        perror("Файл не найден");
        exit(0);
    }
}
    return 0;
}