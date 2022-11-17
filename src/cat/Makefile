ALL: clean s21_cat

s21_cat:
	gcc -Wall -Werror -Wextra s21_cat.c -o s21_cat

clean:
	rm -rf s21_cat

test_func:ALL
	sh test_func_cat.sh

test_leak:ALL
	sh test_leak_cat.sh

style:
	clang-format -i s21_cat.c
	clang-format -i s21_cat.h
	clang-format -n s21_cat.c
	clang-format -n s21_cat.h