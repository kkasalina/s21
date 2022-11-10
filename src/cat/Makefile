GCC = gcc
GCC1 = gcc -c -Wall -Werror -Wextra

all : s21_cat

s21_cat : s21_cat.o
	$(GCC) s21_cat.c -o s21_cat

s21_cat.o : s21_cat.c s21_cat.h
	$(GCC) s21_cat.c -c

clean :
	-rm *.o s21_cat
	
rebuild : clean
	all

