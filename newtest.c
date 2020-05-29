

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	C file to test some of the functions defined in 'utils.h'.
*/

#include "utils.h"
#include <math.h>
#include <time.h>

double test(double a)
{
	if(a==0)
		return 0;
	return (a+1)/a;
}


int main(void)
{

	printf("Testing\n");

	size_t sz = 10;
	double *a = a_fltrange(sz, 1.2, 0.8);
	fltprint(a, sz);

	printf("Exp\n");
	fltexp(a, sz);
	fltprint(a, sz);

	printf("Sqrt\n");
	fltsqrt(a, sz);
	fltprint(a, sz);

	printf("Sin\n");
	fltsin(a, sz);
	fltprint(a, sz);

	printf("Cos\n");
	fltcos(a, sz);
	fltprint(a, sz);

	fltpos(a, sz);

	printf("Log\n");
	fltlog(a, sz);
	fltprint(a, sz);

	fltpos(a, sz);

	printf("Log10\n");
	fltlog10(a, sz);
	fltprint(a, sz);

	printf("Mag\n");
	fltmag(a, sz);
	fltprint(a, sz);
	free(a);

	printf("To int\n");
	double *b = a_fltrange(sz, 2.5, -3.89);
	fltprint(b, sz);
	int *c = a_flttoint(b, sz);
	intprint(c, sz);
	double *d = a_inttoflt(c, sz);
	fltprint(d, sz);

	printf("Mult by 0.1 and add (-0.6)\n");
	fltsmult(d, sz, 0.1);
	fltprint(d, sz);
	fltsadd(d, sz, -0.6);
	fltprint(d, sz);

	free(b);
	free(c);
	free(d);



	return 0;
}