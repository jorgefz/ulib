

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


	/* Allocated 1D Arrays */
	int *aa = a_intzeros(sz);
	int *bb = a_intones(sz);
	int *cc = a_intval(sz, 7);
	int *dd = a_intrange(sz, 100, 11);

	int *cat = a_intcat(cc, sz, dd, sz);
	int *cpy = a_intcpy(dd, sz);

	printf(" Allocated int0\n");
	intprint(aa, sz);
	printf(" Allocated int1\n");
	intprint(bb, sz);
	printf(" Allocated int7\n");
	intprint(cc, sz);
	printf(" Allocated intr\n");
	intprint(dd, sz);
	printf(" Allocated cat\n");
	intprint(cat, 2*sz);
	printf(" Allocated cpy\n");
	intprint(cpy, sz);

	xfree(aa);
	xfree(bb);
	xfree(cc);
	xfree(dd);
	xfree(cat);
	xfree(cpy);

	/* Finding an item in the array */

	int *t1 = a_intrange(sz, -1, 4);
	int *t2 = a_intrange(sz, 5, -3);
	int *t = a_intcat(t1, sz, t2, sz);
	printf(" Finding items in array:\n");
	intprint(t, sz*2);

	int max = intmax(t, 2*sz);
	int min = intmin(t, 2*sz);
	printf(" Max and min are %d, %d \n", max, min);
	uint imax = intimax(t, 2*sz);
	uint imin = intimin(t, 2*sz);
	printf(" At indices %u, %u \n", imax, imin);

	int sum = intsum(t, 2*sz);
	printf(" Sum of values is %d\n", sum);

	xfree(t1);
	xfree(t2);
	xfree(t);


	return 0;
}