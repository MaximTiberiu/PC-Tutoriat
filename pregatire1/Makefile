all: build, run, memcheck

build: main.c
	gcc -o main main.c ex2.c ex2.h
run: main
	./main
memcheck: main
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./main