

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	C file to test some of the functions defined in 'utils.h'.
*/

#include "utils.h"


int main(void)
{

	/* Strings */
	char str[] = "hello world!";
	char *s = str;
	printf("Original: %s\n", s);
	
	strslc(s, 0, 3);
	printf("Sliced: %s\n", s);
	
	strrev(s);
	printf("Reversed: %s\n", s);


	/* 1D Arrays */
	size_t sz = 10;
	int a[sz];
	int b[sz];
	int c[2*sz];

	intzeros(&(a[0]), sz);
	intrange(&(b[0]), sz, 10, -2);
	printf("Original arrays:\n");
	intprint(&(a[0]), sz);
	intprint(&(b[0]), sz);

	printf("Concatenated array:\n");
	intcat(&(c[0]), &(a[0]), sz, &(b[0]), sz);
	intprint(&(c[0]), 2*sz);

	printf("Reversed array:\n");
	intrev(&(c[0]), 2*sz);
	intprint(&(c[0]), 2*sz);

	return 0;
}