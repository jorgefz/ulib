

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
On fail,  
*/
void * xmalloc(size_t bytes)
{
	if (bytes == 0){
		fprintf(stderr, " Error: can't allocate 0 bytes\n");
		return (NULL);
	}
    void *ptr = malloc(bytes);
    if (ptr)
        return ptr;
    
    fprintf(stderr, " Error: can't allocate %zu bytes\n", bytes);
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
	return 1;
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
	int *arr = (int *) xmalloc(s*sizeof(int));
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
		size_t start, size_t step)
{
	size_t val = start;
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
a_intrange(size_t s, size_t start, size_t step)
{
	/*Allocating pointer*/
	int *arr = (int *) xmalloc(s*sizeof(int));
	/*Evaluating array*/
	size_t val = start;
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
	int *dest = (int *) xmalloc(s*sizeof(int));
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

	int *dest = (int *) xmalloc((as+bs)*sizeof(int));
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
uint
intimax(const int *arr, size_t len)
{
	/* Initialise max value and its index */
	int max = arr[0];
	int imax;

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
	int imin = 0;

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

//intsign - switches sign of array members
//intneg - makes all array members negative
//intpos - makes all array members positive
//introll - moves array members places forwards/backward

//intsort - sorts in ascending/descending order
//intissort - sorts array and returns list of array indices

//intadd - sums two arrays of same size
//intsub - subtracts two arrays of same size
//intmult - multiplies two arrays
//intdiv - divides members of two arrays
//intcmp - (sum of abs(value) of both, and compare)


//---Repeat this for arrays of doubles

//---Matrix operations