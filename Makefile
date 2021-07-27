CC=gcc

CFLAGS = -Wall -Wextra -std=c89

all: string array vector arglib list pngread

string: test/string.c
	$(CC) -o bin/string test/string.c $(CFLAGS)

array: test/array.c
	$(CC) -o bin/array test/array.c $(CFLAGS)

vector: test/vector.c
	$(CC) -o bin/vector test/vector.c $(CFLAGS)

arglib: test/arglib.c
	$(CC) -o bin/arglib test/arglib.c $(CFLAGS)

list: test/list.c
	$(CC) -o bin/list test/list.c $(CFLAGS)

pngread: pngread.c
	$(CC) -o bin/pngread pngread.c -Wall -Wextra