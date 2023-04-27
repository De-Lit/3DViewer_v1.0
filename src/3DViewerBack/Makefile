#-------------------------------------------------------
#    Узнаем какая ОС, Присваиваем значение флагов
#-------------------------------------------------------

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    TEST_FLAGS = -lcheck  -pthread -lrt -lm -lsubunit
    LEAKS_RUN = valgrind ./test
    OPEN = xdg-open
else
    TEST_FLAGS = -lcheck
    LEAKS_RUN = CK_FORK=no leaks -atExit -- ./test
    OPEN = open
endif

FLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

#-------------------------------------------------------
#    Переменная для компилятора
#-------------------------------------------------------

CC = gcc

#-------------------------------------------------------
#    Ищем файлы для библиотеки, делаем переменную
#    Переименовываем для объектных файлов
#-------------------------------------------------------

SRCS = $(wildcard *.c) $(wildcard **/*.c) $(wildcard **/**/*.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRCS))

#-------------------------------------------------------
#    Переменная которая указывает на наш Makefile
#-------------------------------------------------------

THIS_FILE := $(lastword $(MAKEFILE_LIST))

#-------------------------------------------------------
#    Переменная для создания каталога report
#-------------------------------------------------------

REPORT = @mkdir -p report

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: 3dviewer.a

3dviewer.a: $(OBJ_FILES)
	ar rcs 3dviewer.a $(OBJ_FILES)
	ranlib 3dviewer.a
	@$(MAKE) -f $(THIS_FILE) clean_src

tests.c:
	checkmk ./tests/3dviewer_tests > tests.c

test: tests.c $(SRCS)
	$(CC) tests.c $(SRCS) $(FLAGS) $(TEST_FLAGS) $(GCOV_FLAGS) -o test
	./test

gcov_report: test
	$(REPORT)
	gcovr -r . --html --html-details -o report/report.html
	@$(MAKE) -f $(THIS_FILE) clean_src
	$(OPEN) ./report/report.html

make_google_style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h **/*.h **/**/*.c
	rm .clang-format

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h **/*.h **/**/*.c
	rm .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c **/**/*.c

leaks: test
	$(LEAKS_RUN)
	@$(MAKE) -f $(THIS_FILE) clean_src

clean_src:
	rm -rf *.o **/*.o **/**/*.o *.gcda *.gcno *.gcov

clean: clean_src
	rm -rf report *.a test tests.c .clang-format
