

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


*/



/*
	DATA TYPES
*/
typedef unsigned int uint;


/*
	MEMORY
*/
/* Allocates some memory of length 'bytes' */
void * xmalloc(size_t bytes)
{
    void *ptr = malloc(bytes);
    if (ptr)
        return ptr;
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
strslc(char *s, const size_t i, const size_t j)
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
	char *b;
	b = &(buffer[0]);

	/* Copying original string */
	strcpy(b, s);

	/* Reversing string from buffer */
	size_t j = len-1;
	for(size_t i=0; i<len; i++){
		s[i] = buffer[j];
		j--;
	}

	return s;
}




/*
	INTEGER 1D ARRAYS
*/

/* Generates an array of zeros */
int *
intzeros(int *arr, size_t s)
{
	for(size_t i=0; i<s; i++)
		arr[i] = 0;
	return arr;
}

/* Generates an array of ones */
int *
intones(int *arr, size_t s)
{
	for(size_t i=0; i<s; i++)
		arr[i] = 1;
	return arr;
}

/* Generates an array of a given value */
int *
intval(int *arr, size_t s, int val)
{
	for(size_t i=0; i<s; i++)
		arr[i] = val;
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

/* Concatenates two arrays of integers into destination */
int *
intcat(int *dest, const int *a, const size_t as, 
	const int *b, const size_t bs)
{
	/* Check input */
	if (!dest || !a || !b)
		return (NULL);

	/* Append first array */
	for(size_t i=0; i<as; i++)
		dest[i] = a[i];

	/* Append second array */
	for(size_t i=as; i<(bs+as); i++)
		dest[i] = b[i-as];

	return dest;
}

/* Prints an array of integers to stdout */
void
intprint(int *src, size_t s)
{
	for(size_t i=0; i<s; i++)
		printf("%d ", src[i]);
	printf("\n");
}

/* Prints an array of integers to stdout */
int *
intcpy(int *dest, int *src, size_t s)
{
	if( !dest || !src)
		return (NULL);
	for(size_t i=0; i<s; i++)
		dest[i] = src[i];
	return dest;
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
	size_t j = len-1;
	for(size_t i=0; i<len; i++){
		arr[i] = buffer[j];
		j--;
	}

	return arr;
}

