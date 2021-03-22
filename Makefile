CC=gcc

CFLAGS = -Wall -Wextra -std=c89

test_string: test/test_string.c
	$(CC) -o test_string test/test_string.c $(CFLAGS)

test_array: test/test_array.c
	$(CC) -o test_array test/test_array.c $(CFLAGS)

test_vector: test/test_vector.c
	$(CC) -o test_vector test/test_vector.c $(CFLAGS)