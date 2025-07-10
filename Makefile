CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic
DEPS=src/main.c src/include/cfg.c
LIBS=

build: src/main.c
	$(CC) $(CFLAGS) $(DEPS) $(LIBS)

run: build
	./a.out
