#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int ge;
  unit flag = {0};
  arr chars = {'\n', '0', '0', '0', 0, 1, 1};
  if (argc != 1) {
    while (((ge = getopt_long(argc, argv, "+beEnstTv?", long_options, NULL)) !=
            -1)) {
      flags(ge, &flag);
    }
    file_open(argc, argv, optind, &flag, &chars);
  }

  return 0;
}

void flags(int ge, unit *flag) {
  switch (ge) {
    case 'b':
      flag->b = 1;
      break;
    case 'v':
      flag->v = 1;
      break;
    case 'E':
    case 'e':
      flag->e = 1;
      break;
    case 'n':
      flag->n = 1;
      break;
    case 's':
      flag->s = 1;
      break;
    case 'T':
    case 't':
      flag->t = 1;
      break;
    case '?':
    default:
      printf("Флаг не распознан!\n");
      exit(1);
  }
}

void file_open(int argc, char **argv, int optind, unit *flag, arr *chars) {
  FILE *file;
  int filename = optind;
  while (filename < argc) {
    file = fopen(argv[filename], "r");
    if (file == NULL) {
      perror("Файл не найден");
      exit(1);
    }
    file = fopen(argv[filename], "r");
    big(file, flag, chars);
    filename++;
    fclose(file);
    chars->flag_n = 1;
  }
}

void big(FILE *file, unit *flag, arr *chars) {
  for (int symCount = 0; (chars->c = getc(file)) != EOF; symCount++) {
    int endStr = 0;
    if (chars->c == '\n') endStr += 1;
    if (flag->s) {
      if (symCount == 1 && chars->lastSim == '\n' && chars->c == '\n') {
        continue;
      }
      if (chars->lastLastSim == '\n' && chars->lastSim == '\n' &&
          chars->c == '\n') {
        continue;
      }
    }
    if (flag->t != 0) {
      flag->v = 1;
      if (chars->c == '\t') {
        chars->flag_t = chars->c;
        chars->c = '^';
      }
    }
    if (flag->b != 0) flag->n = 0;
    if (flag->n != 0 && flag->b == 0) {
      if (symCount == 0 || chars->lastSim == 10) {
        printf("%6d\t", chars->flag_n);
        chars->flag_n++;
      }
    }
    if (flag->v == 1) {
      if (chars->c < 32 && chars->c != 9 && chars->c != 10) {
        chars->c += 64;
        chars->flag_v++;
      }
      if (chars->c == 127) {
        chars->c = '?';
        chars->flag_v++;
      }
    }
    if (flag->e != 0 && chars->c == '\n') {
      flag->v = 1;
      printf("$");
    }
    if (flag->n != 0 && chars->flag_v == 0) printf("%c", chars->c);
    if (flag->b != 0 && chars->lastSim == '\n' && chars->c != '\n')
      printf("%6d\t", chars->flag_b++);
    if (flag->v != 0 && chars->flag_v != 0) printf("^");
    if (flag->n == 0 || chars->flag_v != 0) printf("%c", chars->c);
    if (flag->t != 0 && chars->c == '^' && chars->flag_t == '\t') printf("I");
    chars->lastLastSim = chars->lastSim;
    chars->lastSim = chars->c;
    endStr = 0;
    chars->flag_t = '0';
    chars->flag_v = 0;
  }
}