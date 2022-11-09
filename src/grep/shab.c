#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

/ * Функция для получения подстроки * /
static char* substr(const char*str,
unsigned start, unsigned end)
{
  unsigned n = end - start;
  static char stbuf[256];
  strncpy(stbuf, str + start, n);
  stbuf[n] = 0;
  return stbuf;
}

/ * Основная программа * /
int main(int argc, char** argv)
{
  char * pattern;
  int x, z, lno = 0, cflags = 0;
  char ebuf[128], lbuf[256];
  regex_t reg;
  regmatch_t pm[10];
  const size_t nmatch = 10;
/ * Скомпилируйте регулярное выражение * /
  pattern = argv[1];
  z = regcomp(?, pattern, cflags);
  if (z != 0){
    regerror(z, ?, ebuf, sizeof(ebuf));
    fprintf(stderr, "%s: pattern '%s' \n",ebuf, pattern);
    return 1;
  }
/ * Обрабатывать входные данные построчно * /
  while(fgets(lbuf, sizeof(lbuf), stdin))
  {
    ++lno;
    if ((z = strlen(lbuf)) > 0 && lbuf[z-1] == '\n')
    lbuf[z - 1] = 0;
/ * Применение регулярного выражения к каждой строке * /
    z = regexec(?, lbuf, nmatch, pm, 0);
    if (z == REG_NOMATCH) continue;
    else if (z != 0) {
      regerror(z, ?, ebuf, sizeof(ebuf));
      fprintf(stderr, "%s: regcom('%s')\n", ebuf, lbuf);
      return 2;
    }
/ * результат обработки вывода * /
    for (x = 0; x < nmatch && pm[x].rm_so != -1; ++ x)
    {
      if (!x) printf("%04d: %s\n", lno, lbuf);
      printf(" $%d='%s'\n", x, substr(lbuf, pm[x].rm_so, pm[x].rm_eo));
    }
  }
/ * освободить регулярное выражение * /
  regfree(?);
  return 0;
}