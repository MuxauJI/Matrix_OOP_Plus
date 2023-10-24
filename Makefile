CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c++17 -pedantic -g -DALLOC_METHOD=1 #-fsanitize=address 
LIBS=-lstdc++ #-lcheck
LIBGTEST=-lgtest -lgtest_main
OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
	FLAGS += -D MACOS
else
	LIBS += -lsubunit -lrt -lm -lpthread
endif

rebuild: all

all: clean matrix_oop.a test gcov_report

matrix_oop.a: clean
	$(CC) $(FLAGS) -c matrix_oop.cpp -o matrix_oop.o
	ar rc matrix_oop.a matrix_oop.o
	ranlib matrix_oop.a

test: matrix_oop.a
	$(CC) $(FLAGS) -c test_matrix_oop.cpp -o test_matrix_oop.o
	$(CC) $(FLAGS) test_matrix_oop.o matrix_oop.a $(LIBGTEST) $(LIBS) -o test
	./test

remove_localtest:
	@rm -rf localtest localtest.o matrix_oop.o matrix_oop.a

localtest.o: localtest.cpp matrix_oop.cpp
	@$(CC) $(FLAGS) -c localtest.cpp -o localtest.o
	@$(CC) $(FLAGS) -DDEBUG -c matrix_oop.cpp -o matrix_oop.o
	@ar rc matrix_oop.a matrix_oop.o
	@ranlib matrix_oop.a

localtest: remove_localtest localtest.o
	@$(CC) $(FLAGS) localtest.o matrix_oop.a $(LIBS) -o localtest
	@./localtest

gcov_report:
	@$(CC) $(FLAGS) -c test_matrix_oop.cpp -o test_matrix_oop.o
	@$(CC) $(FLAGS) -c matrix_oop.cpp --coverage -o matrix_oop.o
	@$(CC) $(FLAGS) test_matrix_oop.o matrix_oop.o --coverage $(LIBGTEST) $(LIBS) -o test
	@./test
	@lcov -t "test_matrix_oop" -o test_matrix_oop.info -c -d .
	@genhtml -o report test_matrix_oop.info
	@rm -rf *.gcda *.gcno *.info
	@sh -c "if grep -iq microsoft /proc/version ; then cd ./report/; cmd.exe /c start index.html; elif [[ $(OS) == \"Darwin\" ]]; then open -a \"Google Chrome.app\" ./report/index.html; else open ./report/index.html; fi"

clean:
	rm -rf ./report *.o *.a *.css *.html *.gcda *.gcno *.info test localtest
	
style:
	clang-format -n --style=Google *.cpp *.hpp
	cppcheck --language=c++ *.cpp *.hpp

fix_style:
	clang-format -i --style=Google *.cpp *.hpp

leaks:
	@$(CC) $(FLAGS) -DDEBUG -c matrix_oop.cpp -o matrix_oop.o
	@$(CC) $(FLAGS) -c test_matrix_oop.cpp -o test_matrix_oop.o
	@$(CC) $(FLAGS) test_matrix_oop.o matrix_oop.o $(LIBGTEST) $(LIBS) -o test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --leak-check=full ./test
endif