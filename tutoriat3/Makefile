all: build, run, memcheck

build: pb1-semi3.c
	gcc -o pb1-semi3 -O0 -Wall -Wextra -pedantic pb1-semi3.c

run: pb1-semi3
	./pb1-semi3

memcheck: pb1-semi3
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./pb1-semi3