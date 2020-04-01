

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	C file to test some of the functions defined in 'utils.h'.
*/

#include "utils.h"


int main(void)
{

	/* === Strings === */

	/* Let's begin by initialising a pointer to a string */
	char str[] = "hello world!";
	char *s = str;
	printf("Original: %s\n", s);

	/* To slice it from index 0 to index 3, call strslc */
	strslc(s, 0, 3);
	printf("Sliced: %s\n", s);
	
	/* Now, to reverse the sliced string, just call strrev */
	strrev(s);
	printf("Reversed: %s\n", s);


	/* === 1D Arrays === */

	/* Let's see several functions to work with 1D arrays
	of numbers */

	/* Begin by initialising three arrays of integers */
	size_t sz = 10;
	/* Two arrays of the same size, and a third twice as long */
	int a[sz];
	int b[sz];
	int c[2*sz];

	/* We'll set the members of the first array all to 0 */
	intzeros(&(a[0]), sz);

	/* For the second array, we'll give it values in range,
	starting from 10, and jumping in steps of '-2' (decreasing),
	until it reaches the end of the array */
	intrange(&(b[0]), sz, 10, -2);

	/* Now, let's print the arrays to stdout */
	printf("Original arrays:\n");
	intprint(&(a[0]), sz);
	intprint(&(b[0]), sz);

	/* Then, we'll join these two arrays together,
	to form a third array, stored at the address of the longer
	array we defined above */
	printf("Concatenated array:\n");
	intcat(&(c[0]), &(a[0]), sz, &(b[0]), sz);
	intprint(&(c[0]), 2*sz);

	/* Finally, we'll reverse the concatenated array */
	printf("Reversed array:\n");
	intrev(&(c[0]), 2*sz);
	intprint(&(c[0]), 2*sz);

	/* Allocated 1D Arrays */
	/* No, we'll make use of a variation of some array functions
	which allocate their own space for the array */
	int *aa = a_intzeros(sz);
	int *bb = a_intones(sz);
	int *cc = a_intval(sz, 7);
	int *dd = a_intrange(sz, 100, 11);
	/* Note that you should free these pointers afterwards */

	/* We'll concatenate two of these arrays */
	/* There's no need to input destination pointer, since
	the result is allocated automatically */
	int *cat = a_intcat(cc, sz, dd, sz);

	/* Now copy the result to another allocated array */
	int *cpy = a_intcpy(cat, 2*sz);

	printf(" Allocated array of zeros\n");
	intprint(aa, sz);
	printf(" Allocated array of ones\n");
	intprint(bb, sz);
	printf(" Allocated array of sevens\n");
	intprint(cc, sz);
	printf(" Allocated array in range (100, 200)\n");
	intprint(dd, sz);
	printf(" Allocated concatenated arrays\n");
	intprint(cat, 2*sz);
	printf(" Allocated copy of concatenated arrays\n");
	intprint(cpy, 2*sz);

	/* Of course, free all the memory
	when you're not using it anymore */
	xfree(aa);
	xfree(bb);
	xfree(cc);
	xfree(dd);
	xfree(cat);
	xfree(cpy);

	/* Next, we'll be doing some arithmetics
	with the array members */
	/* Generate some allocated arrays with ranges of values*/
	int *t1 = a_intrange(sz, -1, 4);
	int *t2 = a_intrange(sz, 5, -3);
	int *t = a_intcat(t1, sz, t2, sz);
	printf(" Finding items in array:\n");
	intprint(t, sz*2);

	/* These functions find the maximum and minimum values
	in the arrays, and return their values */
	int max = intmax(t, 2*sz);
	int min = intmin(t, 2*sz);
	printf(" Max and min are %d, %d \n", max, min);

	/* These functions find the maximum and minimum values
	in the arrays, and return the indices in the array */
	uint imax = intimax(t, 2*sz);
	uint imin = intimin(t, 2*sz);
	printf(" At indices %u, %u \n", imax, imin);

	/* Finally, this function sums up all the values in the array */
	int sum = intsum(t, 2*sz);
	printf(" Sum of values is %d\n", sum);

	xfree(t1);
	xfree(t2);
	xfree(t);


	return 0;
}