

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
	C - UTILS

	Useful functions for the C Programming Language.

	Contains several small useful functions for C 
	using only the standard libraries.
	These functions can be classified into:
	* Useful data types
	* Memory Management
	* String Manipulation
	* 1D number array manipulation
	* 2D matrix operations (WIP)
	* File manipulation (WIP)


	VERSIONS

	1.0 - 29/03/2020
		First version.
		DataType: Added 'uint'.
		Memory: Added 'xmalloc' and 'xfree'.
		String: Added slicing and reversion.
		1D Array: Added generation (0, 1, value, range),
				printing, concatenation, copying,
				and reversing.

	1.1 - 30/03/2020
		Added auto-allocation functions for 1D Arrays:
			a_intzeros, a_intones, a_intval, a_intrange,
			a_intcpy, a_intcat.
		Added maximum and minimum functions for 1D Arrays:
			intmax, intmin, intimax, intimin
		Added sum function for 1D Arrays: intsum

	1.2 - 31/03/2020
		Modified xmalloc to return NULL and print an error
			message to stderr on fail.

	1.3 - 28/05/2020
		Modified xmalloc to exit program with error code "-1"
			on fail.
		Modified xfree to return '-1' on fail.
		Removed dependence of xmalloc on functions that allocate memory.
			Standard library function malloc is used instead, and,
			on fail, a NULL pointer is returned.
		Added additional 1D integer array functions for
			element mnaipulation: introll, intdel, intins, a_intins
		Added additional 1D integer array arithmetics:
			intadd, intsub, intfunc, instadd, intsmult, intdot, intcmp

	1.4 - 29/05/2020
		Added all equivalent functions for double-type 1D arrays.
		Added 1D double array functions:
			fltinv, fltexp, fltsqrt, fltsin, fltcos, fltlog, 
			fltlog10, fltdot, fltmag, fltisval, fltisnan
		Added data type conversion functions:
			inttoflt, a_inttoflt, flttoint, a_flttoint
		Improved documentation.


	FUTURE PLANS

	Matrices
	I/O
	Plotting


		


*/



/*
	DATA TYPES
*/
typedef unsigned int uint;


/*
	MEMORY
*/
/*
Allocates some memory of length 'bytes',
and returns a pointer ot it.
On fail, it exits the program.
*/
void * xmalloc(size_t bytes)
{
	if (bytes == 0){
		fprintf(stderr, " Error: can't allocate 0 bytes\n");
		exit(-1);
		return (NULL);
	}
    void *ptr = malloc(bytes);
    if (ptr)
        return ptr;

    fprintf(stderr, " Error: can't allocate %ld bytes\n", (long)bytes);
    exit(-1);
	return (NULL);
}

/*
Checks if pointer points to allocated memory
before freeing it.
*/
int xfree(void *ptr)
{
	if (ptr){
		free(ptr);
		return 0;
	}
	fprintf(stderr, " Error: failed to free pointer");
	return (-1);
}



/*
	STRINGS
*/
/*
Slices string from index i to index j.
On fail, it returns the original string.
*/
char *
strslc(char *s, size_t i, size_t j)
{
	/* Input checks */
	if( (i>j) || strlen(s)<(j-i+1) )
		return (NULL);

	/* Move pointer to left slice */
	char *ptr;
	ptr = s + i;

	/* Null terminator after right slice */
	ptr[j-i+1] = '\0';

	return ptr;
}


/* Reverses input string */
char *
strrev(char *s)
{
	/*Check input */
	if(!s)
		return (NULL);

	/* Declaring temporary space to save string */
	uint len = strlen(s);
	char buffer[len];

	/* Copying original string */
	strcpy(buffer, s);

	/* Reversing string from buffer */
	for(size_t i=0; i<len; i++)
		s[i] = buffer[len-i-1];

	return s;
}




/*
	INTEGER 1D ARRAYS
*/


/* Generates an array of a given value */
int *
intval(int * arr, size_t s, int val)
{
	for(size_t i=0; i<s; i++)
		arr[i] = val;
	return arr;
}

/* Generates an array of a given value */
int *
a_intval(size_t s, int val)
{
	int *arr = (int *) malloc(s*sizeof(int));
	if(!arr)
		return (NULL);
	intval(arr, s, val);
	return arr;
}

/* Generates an array of zeros */
int *
intzeros(int *arr, size_t s)
{
	intval(arr, s, 0);
	return arr;
}

/*
Allocates and generates an array of zeros.
You will need to free the pointer afterwards manually.
*/
int *
a_intzeros(size_t s)
{
	int *arr = a_intval(s, 0);
	return arr;
}

/* Generates an array of ones */
int *
intones(int *arr, size_t s)
{
	intval(arr, s, 1);
	return arr;
}

/*
Allocates and generates an array of ones.
You will need to free the pointer afterwards manually.
*/
int *
a_intones(size_t s)
{
	int *arr = a_intval(s, 1);
	return arr;
}

/* Generates an array of values in a range */
int *
intrange(int *arr, size_t s, 
		int start, int step)
{
	int val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/*
Allocates and generates an array of values in a range.
You will need to free the pointer afterwards.
*/
int *
a_intrange(size_t s, int start, int step)
{
	/*Allocating pointer*/
	int *arr = (int *) malloc(s*sizeof(int));
	if(!arr)
		return (NULL);
	/*Evaluating array*/
	int val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/* Copies an array to another */
int *
intcpy(int *dest, const int *src, size_t s)
{
	if( !dest || !src)
		return (NULL);
	for(size_t i=0; i<s; i++)
		dest[i] = src[i];
	return dest;
}

/*
Copies an array into another array it allocates,
and returns a pointer to it.
You will have to free it afterwards.
*/
int *
a_intcpy(const int *src, size_t s)
{
	if(!src)
		return (NULL);
	int *dest = (int *) malloc(s*sizeof(int));
	if(!dest)
		return (NULL);
	intcpy(dest, src, s);
	return dest;
}

/* Concatenates two arrays of integers into destination */
int *
intcat(int *dest, const int *a, size_t as, 
		const int *b, size_t bs)
{
	/* Check input */
	if (!dest || !a || !b)
		return (NULL);
	/* Append first array */
	intcpy(dest, a, as);
	/* Append second array */
	intcpy(dest+as, b, bs);
	return dest;
}

/*
Concatenates two arrays of integers,
allocates an array with the result,
and returns a pointer to it.
You will have to free it afterwards.
*/
int *
a_intcat(const int *a, size_t as, 
		const int *b, size_t bs)
{
	/* Check input */
	if (!a || !b)
		return (NULL);

	int *dest = (int *) malloc((as+bs)*sizeof(int));
	if(!dest)
		return (NULL);
	intcpy(dest, a, as);
	intcpy(dest+as, b, bs);
	return dest;
}

/* Prints an array of integers to stdout */
void
intprint(const int *src, size_t s)
{
	for(size_t i=0; i<s; i++)
		printf("%d ", src[i]);
	printf("\n");
}

/* Reverses input array */
int *
intrev(int *arr, size_t len)
{
	/*Check input */
	if(arr == NULL)
		return arr;

	/* Declaring temporary space to save string */
	int buffer[len];
	int *b = &(buffer[0]);

	/* Copying original string */
	intcpy(b, arr, len);

	/* Reversing string from buffer */
	for(size_t i=0; i<len; i++)
		arr[i] = buffer[len-i-1];

	return arr;
}



/* 	STATISTICS */
/* Finds maximum of array */
int
intmax(const int *arr, size_t len)
{
	/* Initialise max value on first array member */
	int max = arr[0];

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max)
			max = arr[i];
	}
	return max;
}

/* Finds minimum of array */
int
intmin(const int *arr, size_t len)
{
	/* Initialise min value on first array member */
	int min = arr[0];

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min)
			min = arr[i];
	}
	return min;
}

/* Finds index of maximum of array */
size_t
intimax(const int *arr, size_t len)
{
	/* Initialise max value and its index */
	int max = arr[0];
	size_t imax;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max ){
			max = arr[i];
			imax = i;
		}
	}
	return imax;
}


/* Finds index of minimum of array */
size_t
intimin(const int *arr, size_t len)
{
	/* Initialise min value and its index */
	int min = arr[0];
	size_t imin = 0;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min ){
			min = arr[i];
			imin = i;
		}
	}
	return imin;
}

/* Sums the members of an integer array */
int
intsum(const int *arr, size_t len)
{
	int sum = 0;
	for(size_t i=0; i<len; i++)
		sum += arr[i];
	return sum;
}

/* Makes all array members positive */
int *
intpos(int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = abs(arr[i]);
	return arr;
}

/* Makes all array members negative */
int *
intneg(int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (-1)*abs(arr[i]);
	return arr;
}

/* Switch the sign of array members */
int *
intsign(int *arr, size_t len)
{
	for(size_t i=0; i<len; i++){
		if(arr[i] > 0)
			arr[i] = -arr[i];
		else
			arr[i] = abs(arr[i]);
	}
	return arr;
}

/*
Moves array values an input number of places in the array.
A positive offset moves values forward, and a negative one, backwards.
*/
int *
introll(int *arr, size_t len, int offset)
{
	if(offset == 0)
		return arr;

	int buffer[len];
	int *buff = &(buffer[0]);
	size_t ind = 0;

	//Simplifying offset
	while( (size_t)abs(offset) >= len)
	{
		if (offset > 0)
			offset = offset - len;
		else if (offset < 0)
			offset = offset + len;
	}

	//Calculating roll
	if (offset < 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = i + abs(offset);
			if ( ind >= len )
				ind = i + abs(offset) - len;
			buff[i] = arr[ind];
		}
	}

	else if (offset > 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = len + i - offset;
			if (ind >= len)
				ind = i - offset;
			buff[i] = arr[ind];
		}
	}

	arr = intcpy(arr, buffer, len);
	return arr;
}


/*
Delete array element specified by input index.
Note that new length is reduced by one.
*/
int *
intdel(int *arr, size_t len, size_t index)
{
	if (index >= len)
		return arr;
	for(size_t i=index; i<(len-1); i++)
		arr[i] = arr[i+1];
	return arr;
}


/*
Insert a given value at the specified index
of an array of given length.
Provide enough memory for new element in
destination array. A pointer to this array is returned.
*/
int *
intins(int *dest, const int *arr, size_t len, size_t index, int val)
{
	dest = intcpy(dest, arr, len);
	if (index >= len){
		dest[len] = val;
		return dest;
	}
	for(size_t i=len; i>index; i--)
		dest[i] = arr[i-1];
	dest[index] = val;
	return dest;
}

/*
Insert array element of input value at a specified index
to an input array of given length.
The resulting array is allocated and a pointer to it is
returned.
Note that the size of the new array is one integer longer
than the size of the previous one, and must be freed
after its use.
*/
int *
a_intins(const int *arr, size_t len, size_t index, int val)
{
	int *dest = a_intzeros(len+1);
	if(!dest)
		return (NULL);
	intins(dest, arr, len, index, val);
	return dest;
}


//intissort - sorts array and returns list of array indices

/*
Adds the values of two integer arrays of equal length,
and the result is saved in the memory of the first array.
*/
int *
intadd(int *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] + arr[i];
	return dest;
}

/*
Subtracts the values of two integer arrays of equal length;
the result is saved in the memory of the first array.
*/
int *
intsub(int *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] - arr[i];
	return dest;
}

//intmult - multiplies members of two arrays
int *
intmult(int *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] * arr[i];
	return dest;
}

//intfunc - applies given function to array members
int *
intfunc(int (*func)(int), int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (*func)(arr[i]);
	return arr;
}

/*
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, positive if a>b, and negative if a<b.
*/
int
intcmp(const int *a, const int *b, size_t len)
{
	int cmp = abs(intsum(a,len)) - abs(intsum(b,len));
	return cmp;
}

//intsadd - add a scalar to all array members.
int *
intsadd(int *arr, size_t len, int val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i] + val;
	return arr;
}

//intsmult - multiply all array members by a scalar
int *
intsmult(int *arr, size_t len, int val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i]*val;
	return arr;
}

//intdot - dot product of two arrays
int
intdot(const int *a, const int *b, size_t len)
{
	int *arr = a_intcpy(a, len);
	int dot = intsum(intmult(arr, b, len), len);
	free(arr); 
	return dot;
}






/*
	DOUBLE 1D ARRAYS
*/


/* Generates an array of a given value */
double *
fltval(double * arr, size_t s, double val)
{
	for(size_t i=0; i<s; i++)
		arr[i] = val;
	return arr;
}

/* Generates an array of a given value */
double *
a_fltval(size_t s, double val)
{
	double *arr = (double *) malloc(s*sizeof(double));
	if(!arr)
		return (NULL);
	fltval(arr, s, val);
	return arr;
}

/* Generates an array of zeros */
double *
fltzeros(double *arr, size_t s)
{
	fltval(arr, s, 0);
	return arr;
}

/*
Allocates and generates an array of zeros.
You will need to free the pointer afterwards manually.
*/
double *
a_fltzeros(size_t s)
{
	double *arr = a_fltval(s, 0);
	return arr;
}

/* Generates an array of ones */
double *
fltones(double *arr, size_t s)
{
	fltval(arr, s, 1);
	return arr;
}

/*
Allocates and generates an array of ones.
You will need to free the pointer afterwards manually.
*/
double *
a_fltones(size_t s)
{
	double *arr = a_fltval(s, 1);
	return arr;
}

/* Generates an array of values in a range */
double *
fltrange(double *arr, size_t s, 
		double start, double step)
{
	double val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/*
Allocates and generates an array of values in a range.
You will need to free the pointer afterwards.
*/
double *
a_fltrange(size_t s, double start, double step)
{
	/*Allocating pointer*/
	double *arr = (double *) malloc(s*sizeof(double));
	if(!arr)
		return (NULL);
	/*Evaluating array*/
	double val = start;
	for(size_t i=0; i<s; i++){
		arr[i] = val;
		val += step;
	}
	return arr;
}

/* Copies an array to another */
double *
fltcpy(double *dest, const double *src, size_t s)
{
	if( !dest || !src)
		return (NULL);
	for(size_t i=0; i<s; i++)
		dest[i] = src[i];
	return dest;
}

/*
Copies an array into another array it allocates,
and returns a pointer to it.
You will have to free it afterwards.
*/
double *
a_fltcpy(const double *src, size_t s)
{
	if(!src)
		return (NULL);
	double *dest = (double *) malloc(s*sizeof(double));
	if(!dest)
		return (NULL);
	fltcpy(dest, src, s);
	return dest;
}

/* Concatenates two arrays of integers into destination */
double *
fltcat(double *dest, const double *a, size_t as, 
		const double *b, size_t bs)
{
	/* Check input */
	if (!dest || !a || !b)
		return (NULL);
	/* Append first array */
	fltcpy(dest, a, as);
	/* Append second array */
	fltcpy(dest+as, b, bs);
	return dest;
}

/*
Concatenates two arrays of integers,
allocates an array with the result,
and returns a pointer to it.
You will have to free it afterwards.
*/
double *
a_fltcat(const double *a, size_t as, 
		const double *b, size_t bs)
{
	/* Check input */
	if (!a || !b)
		return (NULL);

	double *dest = (double *) malloc((as+bs)*sizeof(double));
	if(!dest)
		return (NULL);
	fltcpy(dest, a, as);
	fltcpy(dest+as, b, bs);
	return dest;
}

/* Prints an array of integers to stdout */
void
fltprint(const double *src, size_t s)
{
	for(size_t i=0; i<s; i++)
		printf("%g ", src[i]);
	printf("\n");
}

/* Reverses input array */
double *
fltrev(double *arr, size_t len)
{
	/*Check input */
	if(arr == NULL)
		return arr;

	/* Declaring temporary space to save string */
	double buffer[len];
	double *b = &(buffer[0]);

	/* Copying original string */
	fltcpy(b, arr, len);

	/* Reversing string from buffer */
	for(size_t i=0; i<len; i++)
		arr[i] = buffer[len-i-1];

	return arr;
}



/* 	STATISTICS */
/* Finds maximum of array */
double
fltmax(const double *arr, size_t len)
{
	/* Initialise max value on first array member */
	double max = arr[0];
	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max)
			max = arr[i];
	}
	return max;
}

/* Finds minimum of array */
double
fltmin(const double *arr, size_t len)
{
	/* Initialise min value on first array member */
	double min = arr[0];

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min)
			min = arr[i];
	}
	return min;
}

/* Finds index of maximum of array */
size_t
fltimax(const double *arr, size_t len)
{
	/* Initialise max value and its index */
	double max = arr[0];
	size_t imax;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] > max ){
			max = arr[i];
			imax = i;
		}
	}
	return imax;
}

/* Finds index of minimum of array */
size_t
fltimin(const double *arr, size_t len)
{
	/* Initialise min value and its index */
	double min = arr[0];
	size_t imin = 0;

	/* Looping through array */
	for(size_t i=0; i<len; i++){
		if( arr[i] < min ){
			min = arr[i];
			imin = i;
		}
	}
	return imin;
}

/* Sums the members of an integer array */
double
fltsum(const double *arr, size_t len)
{
	double sum = 0;
	for(size_t i=0; i<len; i++)
		sum += arr[i];
	return sum;
}

/* Makes all array members positive */
double *
fltpos(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = fabs(arr[i]);
	return arr;
}

/* Makes all array members negative */
double *
fltneg(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (-1)*fabs(arr[i]);
	return arr;
}

/* Switch the sign of array members */
double *
fltsign(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++){
		if(arr[i] > 0)
			arr[i] = -arr[i];
		else
			arr[i] = fabs(arr[i]);
	}
	return arr;
}

/*
Moves array values an input number of places in the array.
A positive offset moves values forward, and a negative one, backwards.
*/
double *
fltroll(double *arr, size_t len, int offset)
{
	if(offset == 0)
		return arr;

	double buffer[len];
	double *buff = &(buffer[0]);
	size_t ind = 0;

	//Simplifying offset
	while( (size_t)abs(offset) >= len)
	{
		if (offset > 0)
			offset = offset - len;
		else if (offset < 0)
			offset = offset + len;
	}

	//Calculating roll
	if (offset < 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = i + abs(offset);
			if ( ind >= len )
				ind = i + abs(offset) - len;
			buff[i] = arr[ind];
		}
	}

	else if (offset > 0)
	{
		for(size_t i=0; i<len; i++)
		{
			ind = len + i - offset;
			if (ind >= len)
				ind = i - offset;
			buff[i] = arr[ind];
		}
	}

	arr = fltcpy(arr, buffer, len);
	return arr;
}


/*
Delete array element specified by input index.
Note that new length is reduced by one.
*/
double *
fltdel(double *arr, size_t len, size_t index)
{
	if (index >= len)
		return arr;
	for(size_t i=index; i<(len-1); i++)
		arr[i] = arr[i+1];
	return arr;
}


/*
Insert a given value at the specified index
of an array of given length.
Provide enough memory for new element in
destination array. A pointer to this array is returned.
*/
double *
fltins(double *dest, const double *arr, 
		size_t len, size_t index, double val)
{
	dest = fltcpy(dest, arr, len);
	if (index >= len){
		dest[len] = val;
		return dest;
	}
	for(size_t i=len; i>index; i--)
		dest[i] = arr[i-1];
	dest[index] = val;
	return dest;
}

/*
Insert array element of input value at a specified index
to an input array of given length.
The resulting array is allocated and a pointer to it is
returned.
Note that the size of the new array is one integer longer
than the size of the previous one, and must be freed
after its use.
*/
double *
a_fltins(const double *arr, size_t len, size_t index, double val)
{
	double *dest = a_fltzeros(len+1);
	if(!dest)
		return (NULL);
	fltins(dest, arr, len, index, val);
	return dest;
}


//intissort - sorts array and returns list of array indices

/*
Adds the values of two integer arrays of equal length,
and the result is saved in the memory of the first array.
*/
double *
fltadd(double *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] + arr[i];
	return dest;
}

/*
Subtracts the values of two integer arrays of equal length;
the result is saved in the memory of the first array.
*/
double *
fltsub(double *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] - arr[i];
	return dest;
}
/* Multiplies two arrays element-wise */
double *
fltmult(double *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = dest[i] * arr[i];
	return dest;
}

/* Applies an input function to the array elements individually */
double *
fltfunc(double (*func)(), double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		arr[i] = (*func)(arr[i]);
	return arr;
}

/*
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, positive if a>b, and negative if a<b.
*/
double
fltcmp(const double *a, const double *b, size_t len)
{
	double cmp = fabs(fltsum(a,len)) - fabs(fltsum(b,len));
	return cmp;
}

/* Adds a scalar value to all array elements */
double *
fltsadd(double *arr, size_t len, double val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i] + val;
	return arr;
}

/* Multiplies all array elements by a scalar value */
double *
fltsmult(double *arr, size_t len, double val)
{
	for(size_t i=0; i<len; i++)
		arr[i] = arr[i]*val;
	return arr;
}

/* Calculates inverse of array elements */
double *
fltinv(double *arr, size_t len)
{
	for(size_t i=0; i<len; i++){
		arr[i] = pow(arr[i], -1);
	}
	return arr;
}

/* Calculates exp() of array elements */
double *
fltexp(double *arr, size_t len)
{
	double (*func_ptr)(double) = &exp;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates square root of array elements */
double *
fltsqrt(double *arr, size_t len)
{
	double (*func_ptr)(double) = &sqrt;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates sine of array elements */
double *
fltsin(double *arr, size_t len)
{
	double (*func_ptr)(double) = &sin;
	fltfunc(func_ptr, arr, len);
	return arr;
}

/* Calculates cosine of array elements */
double *
fltcos(double *arr, size_t len)
{
	double (*func_ptr)(double) = &cos;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates natural log of array elements */
double *
fltlog(double *arr, size_t len)
{
	double (*func_ptr)(double) = &log;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates base 10 log of array elements */
double *
fltlog10(double *arr, size_t len)
{
	double (*func_ptr)(double) = &log10;
	fltfunc(func_ptr, arr, len);
	return arr; 
}

/* Calculates dot product of array */
double
fltdot(const double *a, const double *b, size_t len)
{
	double *arr = a_fltcpy(a, len);
	double dot = fltsum(fltmult(arr, b, len), len);
	free(arr);
	return dot;
}

/* Get magnitude of array vector */
double
fltmag(const double *arr, size_t len)
{
	return sqrt(fltdot(arr,arr,len));
}

/*
Find if array member is a value.
Returns array of 0s and 1s, where 0 is not value, and 1 is value.
Note that return array must have enough memory.
*/
int *
fltisval(int *dest, const double *arr, size_t len, double val)
{
	dest = intzeros(dest, len);
	for (size_t i=0; i<len; i++){
		if(arr[i] == val)
			dest[i] = 1;
	}
	return dest;
}


/*
Looks for NaN values in array
Returns array of 0s and 1s.
Note that return array must have enough memory.
*/
int *
fltisnan(int *dest, const double *arr, size_t len)
{
	dest = intzeros(dest, len);
	for (size_t i=0; i<len; i++){
		if(arr[i] != arr[i])
			dest[i] = 1;
	}
	return dest;
}


/* Converts an array of integers into an array of doubles */
double *
inttoflt(double *dest, const int *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = (double)(arr[i]);
	return dest;
}

/*
Converts an array of integers into an array of doubles,
allocates the new array, and returns a pointer to it.
*/
double *
a_inttoflt(const int *arr, size_t len)
{
	double *dest = a_fltzeros(len);
	for(size_t i=0; i<len; i++)
		dest[i] = (double)(arr[i]);
	return dest;
}

/* Converts an array of doubles into an array of integers */
int *
flttoint(int *dest, const double *arr, size_t len)
{
	for(size_t i=0; i<len; i++)
		dest[i] = (int)(arr[i]);
	return dest;
}

/*
Converts an array of doubles into an array of integers,
allocates the new array, and returns a pointer to it.
*/
int *
a_flttoint(const double *arr, size_t len)
{
	int *dest = a_intzeros(len);
	for(size_t i=0; i<len; i++)
		dest[i] = (int)(arr[i]);
	return dest;
}