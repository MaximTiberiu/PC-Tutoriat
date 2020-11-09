all: build, run, memcheck

build: pb2.c
	gcc -o pb2 -O0 -Wall -Wextra -pedantic pb2.c

run: pb2
	./pb2

memcheck: pb2
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./pb2