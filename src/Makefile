CC := gcc 
CFLAGS := -Wall -Wextra -Werror -std=c11
APP = build/3DViewer.app
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -fprofile-arcs --coverage -L.


ifeq ($(shell uname), Linux)
    LDFLAGS += -lpthread -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    LDFLAGS += -lm
    OPEN_CMD := open
endif

all: install s21_parser.a s21_transform.a tests

build:
	mkdir build
	cd ./build/ && qmake6 ../3dviewer/3dviewer.pro && make first
	
install: build
	@mkdir ./3DViewer_v1
	@cp -rf $(APP) ./3DViewer_v1

uninstall:
	@rm -rf ./3DViewer_v1

dist:
	rm -rf Archive_3DViewer_v1/
	mkdir Archive_3DViewer_v1/
	cp Makefile 3dviewer/*.h 3dviewer/*.pro 3dviewer/*.cpp 3dviewer/*.ui 3dviewer/*.user 3dviewer/lib/s21*.* Archive_3dviewer_v1/src/
	tar cvzf Archive_3DViewer_v1.tgz Archive_3DViewer_v1/
	rm -rf Archive_3DViewer_v1/

dvi:
	@open ../README_RUS.md

check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n 3dviewer/lib/*.c 3dviewer/lib/*.h 3dviewer/*.cpp 3dviewer/*.h
	@clang-format -i 3dviewer/lib/*.c 3dviewer/lib/*.h 3dviewer/*.cpp 3dviewer/*.h
	@rm ./.clang-format

s21_parser.a:
	$(CC) $(CFLAGS) -c ./3dviewer/lib/s21_parser.c
	@ar rcs s21_parser.a s21_parser.o

s21_transform.a:
	$(CC) $(CFLAGS) -c ./3dviewer/lib/s21_transform.c
	@ar rcs s21_transform.a s21_transform.o

s21_parser_gcov.a: gcov_obj
	@ar rcs s21_parser_gcov.a 3dviewer/gcov_obj/s21_parser.o

s21_transform_gcov.a: gcov_obj
	@ar rcs s21_transform_gcov.a 3dviewer/gcov_obj/s21_transform.o

tests: s21_parser_gcov.a s21_transform_gcov.a
	@$(CC) s21_parser_gcov.a s21_transform_gcov.a 3dviewer/tests/test.c -o $@ $(LDFLAGS) $(GCOVFLAGS)
	@./$@ 

gcov_obj:
	-mkdir ./3dviewer/gcov_obj/
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c 3dviewer/lib/s21_parser.c -o 3dviewer/gcov_obj/s21_parser.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c 3dviewer/lib/s21_transform.c -o 3dviewer/gcov_obj/s21_transform.o

gcov_report: tests 
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html

valgrind: 
	$(CC) 3dviewer/lib/*.c 3dviewer/tests/test.c -o test_run -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
	CK_FORK=no valgrind --leak-check=full --track-origins=yes --log-file="valgrind.log" ./test_run

clean: 
	-rm -rf ./3dviewer/gcov_obj
	-rm -rf test*
	-rm -rf s21_parser_gcov.a
	-rm -rf s21_transform_gcov.a
	-rm -rf ./report/
	-rm -rf ./build/
	-rm -rf ./3DViewer_v1/
	-rm valgrind.log
	-rm test_run
	-rm s21_*.*


