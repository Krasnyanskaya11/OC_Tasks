all: compile run-with-default-values

compile: main.c quadraticEquation.c
	gcc main.c quadraticEquation.c -o main.out -lm

run-with-default-values: main.out
	./main.out 1 4 3