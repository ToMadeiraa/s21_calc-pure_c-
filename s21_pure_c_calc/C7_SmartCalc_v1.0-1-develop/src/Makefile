# sudo apt-get install libgtk-3-dev
CFLAGS = -std=c11 -Wall -Wextra -Werror
GFLAGS = -fprofile-arcs -ftest-coverage
FILES = gui.c plot+bonus.c s21_smartcalc.c
TESTFILES = ./all_tests/tests.c 

OS=$(shell uname)

ifeq (${OS}, Darwin)
	LIBS = -L. -lcheck -lm
else
	LIBS = -L. -lcheck -lm -lsubunit
endif 

all: clean s21_smartcalc gcov_report

s21_smartcalc: $(FILES)
	gcc $(CFLAGS) -rdynamic $(FILES) -o s21_smartcalc $(LIBS) `pkg-config --cflags --libs gtk+-3.0`

test: $(TESTFILES) s21_smartcalc.c
	gcc $(CFLAGS) $(TESTFILES) s21_smartcalc.c -o tests $(LIBS)
	./tests

gcov_report: $(TESTFILES) s21_smartcalc.c
	gcc $(CFLAGS) $(GFLAGS) -c s21_smartcalc.c
	gcc $(CFLAGS) -c all_tests/tests.c
	gcc $(GFLAGS) *.o -o tests $(LIBS)
	./tests
	lcov -t "a.out" -o REPORT.info -c -d .
	genhtml -o html REPORT.info
	open html/index.html

install: clean s21_smartcalc
	mkdir ../install/
	cp s21_smartcalc ./../install

uninstall:
	rm -rf .././install/

dist: clean
	mkdir dist/
	cp *.c dist/
	cp *.h dist/
	cp -r all_tests/ dist/all_tests
	cp Makefile dist/Makefile
	cp -r build/ dist/build
	cp -r docs/ dist/docs
	tar cvzf calc_archive.tgz dist/
	rm -rf dist/

dvi:
	latex -output-directory=./docs ./docs/text.tex ./docs/brief.dvi
	latex -output-directory=./docs ./docs/text.tex ./docs/brief.dvi
	pdflatex -output-directory=./docs ./docs/text.tex ./docs/brief.pdf

rebuild: clean all

clean:
	rm -f s21_smartcalc tests ./*.o ./*.a report *.gcda *.gcno *info calc_archive.tgz
	rm -f docs/text.aux docs/text.pdf docs/text.dvi docs/text.log docs/text.toc
	rm -rf html ../install ./dist

check:
	clang-format -style=Google -n $(FILES) $(TESTFILES) *.h
	
clang:
	clang-format -style=Google -i $(FILES) $(TESTFILES) *.h 