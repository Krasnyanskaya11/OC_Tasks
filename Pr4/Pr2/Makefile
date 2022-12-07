all: compile run-with-help-option run-with-specific-mode run-with-file-option

compile: main.c
	gcc main.c -o main.out

run-with-help-option: main.out
	./main.out -h

run-with-specific-mode: main.out
	./main.out -c

run-with-file-option: main.out
	./main.out -o main.out