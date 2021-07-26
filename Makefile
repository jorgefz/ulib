CC=gcc

CFLAGS = -Wall -Wextra -std=c89

all: test_string test_array test_vector

test_string: test/test_string.c
	$(CC) -o bin/test_string test/test_string.c $(CFLAGS)

test_array: test/test_array.c
	$(CC) -o bin/test_array test/test_array.c $(CFLAGS)

test_vector: test/test_vector.c
	$(CC) -o bin/test_vector test/test_vector.c $(CFLAGS)