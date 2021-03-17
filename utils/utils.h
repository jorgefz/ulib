#ifndef _UTILS_HEADER_1
#define _UTILS_HEADER_1

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
			intzerosA, a_intones, intvalA, a_intrange,
			intcpyA, a_intcat.
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

	1.5 - 03/06/2020
		Added functions for Input/Output:
			getstr, strtoint, strtointArr, strtoflt, strtofltArr,
			CountTxtLines, ReadTxtLines, GenFromTxt
		Renamed all allocated functions from 'a_funcname' to 'funcnameA'.

	1.6 - 23/06/2020
		Split main file into utils.h header and utils.c.

	1.7 - 04/10/2020
		Removed xfree and xmalloc.
		Added variadic function to join several strings: strjoin.
		Added array comparison macros: ARR_WHERE, ARR_ANY, ARR_COUNT, ARR_SUBS
		Added array comparison functions: intisval_any, fltisval_any.
		Added NaN-dealing functions: fltisnan_where, fltisnan_any, fltisnan_subs
		Added int/double array conversion to string functions: flttostr_arr, inttostr_arr
		Added file I/O function: SaveToTxt
		Renamed functions that return allocated memory from 'A' to '_alloc'.

	1.8 - 16/03/2021
		Added unsigned char - uchar.
		Removed wacky macros
		strcpya
		-Enum for types
		-Support for int, double, and bool arrays.
		-Error management with errno



	FUTURE PLANS
	
	Sorting
	Matrices
	I/O
	Printf functions
	Plotting

*/



// ---------------------------------------

enum {
	INT, DOUBLE, BOOL
}



//-----------------------------------------

/*
	STRINGS
*/

/*
Copies an input string into allocated memory,
and returns a pointer to it.
Note: free the string once it has been used.
*/
char *
strcpy_alloc(const char *str);


/*
Slices the input string from index i to index j,
and returns a pointer to it.
Note that it modifies the input string.
On fail, it returns a null pointer.
*/
char *
strslc(char *s, size_t i, size_t j);


/*
Slices a string 'str' from index i to index j
and stores the result in the input string 'dest',
leaving the original string untouched.
On fail, it returns a null pointer.
*/
char *
strslc2(char *dest, const char *str, size_t i, size_t j);


/* Reverses input string */
char *
strrev(char *s);


/*
Joins a series of strings into one,
stores the result in an input string 'dest',
and returns a pointer to it.
*/
char *strjoin(char *dest, int num, ...);






/*
	INTEGER ARRAYS
*/

/* Generates an array of a given value */
int *
intval(int *arr, size_t s, int val);

/* Generates an array of a given value */
int *
intval_alloc(size_t s, int val);

/* Generates an array of zeros */
int *
intzeros(int *arr, size_t s);

/*
Allocates and generates an array of zeros.
You will need to free the pointer afterwards manually.
*/
int *
intzeros_alloc(size_t s);

/* Generates an array of ones */
int *
intones(int *arr, size_t s);

/*
Allocates and generates an array of ones.
You will need to free the pointer afterwards manually.
*/
int *
intones_alloc(size_t s);

/* Generates an array of values in a range */
int *
intrange(int *arr, size_t s, 
		int start, int step);

/*
Allocates and generates an array of values in a range.
You will need to free the pointer afterwards.
*/
int *
intrange_alloc(size_t s, int start, int step);

/* Copies an array to another */
int *
intcpy(int *dest, const int *src, size_t s);

/*
Copies an array into another array it allocates,
and returns a pointer to it.
You will have to free it afterwards.
*/
int *
intcpy_alloc(const int *src, size_t s);

/* Concatenates two arrays of integers into destination */
int *
intcat(int *dest, const int *a, size_t as, 
		const int *b, size_t bs);

/*
Concatenates two arrays of integers,
allocates an array with the result,
and returns a pointer to it.
You will have to free it afterwards.
*/
int *
intcat_alloc(const int *a, size_t as, 
		const int *b, size_t bs);

/* Prints an array of integers to stdout */
void
intprint(const int *src, size_t s);

/* Reverses input array */
int *
intrev(int *arr, size_t len);



/* 	STATISTICS */
/* Finds maximum of array */
int
intmax(const int *arr, size_t len);

/* Finds minimum of array */
int
intmin(const int *arr, size_t len);

/* Finds index of maximum of array */
size_t
intimax(const int *arr, size_t len);


/* Finds index of minimum of array */
size_t
intimin(const int *arr, size_t len);

/* Sums the members of an integer array */
int
intsum(const int *arr, size_t len);

/* Makes all array members positive */
int *
intpos(int *arr, size_t len);

/* Makes all array members negative */
int *
intneg(int *arr, size_t len);

/* Switch the sign of array members */
int *
intsign(int *arr, size_t len);

/*
Moves array values an input number of places in the array.
A positive offset moves values forward, and a negative one, backwards.
*/
int *
introll(int *arr, size_t len, int offset);


/*
Delete array element specified by input index.
Note that new length is reduced by one.
*/
int *
intdel(int *arr, size_t len, size_t index);


/*
Insert a given value at the specified index
of an array of given length.
Provide enough memory for new element in
destination array. A pointer to this array is returned.
*/
int *
intins(int *dest, const int *arr, size_t len, size_t index, int val);

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
intins_alloc(const int *arr, size_t len, size_t index, int val);


//intissort - sorts array and returns list of array indices

/*
Adds the values of two integer arrays of equal length,
and the result is saved in the memory of the first array.
*/
int *
intadd(int *dest, const int *arr, size_t len);

/*
Subtracts the values of two integer arrays of equal length;
the result is saved in the memory of the first array.
*/
int *
intsub(int *dest, const int *arr, size_t len);

//intmult - multiplies members of two arrays
int *
intmult(int *dest, const int *arr, size_t len);

//intfunc - applies given function to array members
int *
intfunc(int (*func)(int), int *arr, size_t len);

/*
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, positive if a>b, and negative if a<b.
*/
int
intcmp(const int *a, const int *b, size_t len);

//intsadd - add a scalar to all array members.
int *
intsadd(int *arr, size_t len, int val);

//intsmult - multiply all array members by a scalar
int *
intsmult(int *arr, size_t len, int val);

//intdot - dot product of two arrays
int
intdot(const int *a, const int *b, size_t len);






/*
	DOUBLE 1D ARRAYS
*/


/* Generates an array of a given value */
double *
fltval(double * arr, size_t s, double val);

/* Generates an array of a given value */
double *
fltval_alloc(size_t s, double val);

/* Generates an array of zeros */
double *
fltzeros(double *arr, size_t s);

/*
Allocates and generates an array of zeros.
You will need to free the pointer afterwards manually.
*/
double *
fltzeros_alloc(size_t s);

/* Generates an array of ones */
double *
fltones(double *arr, size_t s);

/*
Allocates and generates an array of ones.
You will need to free the pointer afterwards manually.
*/
double *
fltones_alloc(size_t s);

/* Generates an array of values in a range */
double *
fltrange(double *arr, size_t s, 
		double start, double step);

/*
Allocates and generates an array of values in a range.
You will need to free the pointer afterwards.
*/
double *
fltrange_alloc(size_t s, double start, double step);

/* Copies an array to another */
double *
fltcpy(double *dest, const double *src, size_t s);

/*
Copies an array into another array it allocates,
and returns a pointer to it.
You will have to free it afterwards.
*/
double *
fltcpy_alloc(const double *src, size_t s);

/* Concatenates two arrays of integers into destination */
double *
fltcat(double *dest, const double *a, size_t as, 
		const double *b, size_t bs);

/*
Concatenates two arrays of integers,
allocates an array with the result,
and returns a pointer to it.
You will have to free it afterwards.
*/
double *
fltcat_alloc(const double *a, size_t as, 
		const double *b, size_t bs);


/* Prints an array of integers to stdout */
void
fltprint(const double *src, size_t s);


/* Reverses input array */
double *
fltrev(double *arr, size_t len);



/* 	STATISTICS */
/* Finds maximum of array */
double
fltmax(const double *arr, size_t len);


/* Finds minimum of array */
double
fltmin(const double *arr, size_t len);

/* Finds index of maximum of array */
size_t
fltimax(const double *arr, size_t len);

/* Finds index of minimum of array */
size_t
fltimin(const double *arr, size_t len);

/* Sums the members of an integer array */
double
fltsum(const double *arr, size_t len);

/* Makes all array members positive */
double *
fltpos(double *arr, size_t len);

/* Makes all array members negative */
double *
fltneg(double *arr, size_t len);

/* Switch the sign of array members */
double *
fltsign(double *arr, size_t len);

/*
Moves array values an input number of places in the array.
A positive offset moves values forward, and a negative one, backwards.
*/
double *
fltroll(double *arr, size_t len, int offset);


/*
Delete array element specified by input index,
store in input array 'dest', and return a pointer to it.
Note that 'must' have a size of at least len-1.
*/
double *
fltdel(double *dest, const double *arr, 
			size_t len, size_t index);


/*
Delete array element specified by input index,
store new array in allocated memory, and return a
pointer to it.
Note that the size of the new array is one integer shorter
than the size of the previous one, and must be freed
after its use.
*/
double *
fltdel_alloc(const double *arr, size_t len, size_t index);


/*
Insert a given value at the specified index
of an array of given length.
Provide enough memory for new element in
destination array. A pointer to this array is returned.
*/
double *
fltins(double *dest, const double *arr, 
		size_t len, size_t index, double val);

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
fltins_alloc(const double *arr, size_t len, size_t index, double val);


//intissort - sorts array and returns list of array indices

/*
Adds the values of two integer arrays of equal length,
and the result is saved in the memory of the first array.
*/
double *
fltadd(double *dest, const double *arr, size_t len);

/*
Subtracts the values of two integer arrays of equal length;
the result is saved in the memory of the first array.
*/
double *
fltsub(double *dest, const double *arr, size_t len);


/* Multiplies two arrays element-wise */
double *
fltmult(double *dest, const double *arr, size_t len);


/* Applies an input function to the array elements individually */
double *
fltfunc(double (*func)(), double *arr, size_t len);


/*
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, and non-zero if a!=b.
*/
double
fltcmp(const double *a, const double *b, size_t len);


/* Adds a scalar value to all array elements */
double *
fltsadd(double *arr, size_t len, double val);


/* Multiplies all array elements by a scalar value */
double *
fltsmult(double *arr, size_t len, double val);


/* Calculates inverse of array elements */
double *
fltinv(double *arr, size_t len);


/* Calculates exp() of array elements */
double *
fltexp(double *arr, size_t len);

/* Calculates square root of array elements */
double *
fltsqrt(double *arr, size_t len);

/* Calculates sine of array elements */
double *
fltsin(double *arr, size_t len);

/* Calculates cosine of array elements */
double *
fltcos(double *arr, size_t len);

/* Calculates natural log of array elements */
double *
fltlog(double *arr, size_t len);

/* Calculates base 10 log of array elements */
double *
fltlog10(double *arr, size_t len);

/* Calculates dot product of array */
double
fltdot(const double *a, const double *b, size_t len);

/* Get magnitude of array vector */
double
fltmag(const double *arr, size_t len);



/*
Looks for NaN values in array
Returns array of 0s and 1s.
Note that return array must have enough memory.
*/
int *
fltisnan_where(int *dest, const double *arr, size_t len);


/*
Returns the input array pointer if it finds any NAN
values in the array.
Otherwise, returns NULL.
*/
double *
fltisnan_any(double *arr, size_t len);


/*
Substitutes NAN values found in an array with an input double 'val'.
Returns NULL if no NAN values where found.
*/
double *
fltisnan_subs(double *arr, size_t len, double val);




// ARRAY TYPE CONVERSIONS


/* Converts an array of integers into an array of doubles */
double *
inttoflt(double *dest, const int *arr, size_t len);

/*
Converts an array of integers into an array of doubles,
allocates the new array, and returns a pointer to it.
*/
double *
inttoflt_alloc(const int *arr, size_t len);

/* Converts an array of doubles into an array of integers */
int *
flttoint(int *dest, const double *arr, size_t len);

/*
Converts an array of doubles into an array of integers,
allocates the new array, and returns a pointer to it.
*/
int *
flttoint_alloc(const double *arr, size_t len);






/*
	INPUT FUNCTIONS
*/


/*
Asks user for input with a message,
and returns a string.
*/
char *
getstr(char *dest, const char *msg);


/*
Converts a input string 'str' into an integer.
The result is stored at the input pointer 'dest'.
On fail, NULL is returned.
*/
int *
strtoint(int *dest, const char *str);


/*
Converts and array of strings if length 'size' 
into an array of integers.
Values are stored in memory of input array 'dest'.
*/
int *
strtoint_arr(int *dest, const char **str, size_t size);



/*
Convert string to double.
*/
double *
strtoflt(double *dest, const char *str);

/*
Converts and array of strings of length 'size' 
into an array of doubles.
Values are stored in memory of input array 'dest'.
*/
double *
strtoflt_arr(double *dest, const char **str, size_t size);



/*
Given a string and a delimiter,
it returns the number of tokens in the string.
*/
size_t
strtokn(char *str, const char *delim);


/*
Given a string and a delimiter,
it runs through the first field
of the string until the delimiter,
substitutes the delimiter by a "\0",
and returns a pointer to the next field.
If the end of the string is reached, a NULL
pointer is returned.
*/
char *
strpar(char *ptr, const char delim);

/*
Given a string 'str' and a delimiter 'delim',
it splits the string at the delimiters, stores
the pointers to the tokens in 'dest', and returns
a pointer to it.
On fail, it returns NULL.
*/
char **
strsplit(char **dest, char *str, const char delim);




/*
Counts the lines in a txt file,
and returns the value.
The counting process discards empty lines
and comment lines, defined by an input starting character.

Input:
	size_t maxRead:	maximum size in which to store a file line.
	char *path:		string to file path.
	char *comment:	pointer to character that defines file comment.
Output:
	size_t lineCount:	number of non-comment non-empty lines in file.
*/
size_t
CountTxtLines(size_t maxRead, const char *path, const char *comment);


/*
Reads the non-comment lines from a txt 
and returns the strings.
One should first call CountTxTLines, then initialize
enough memory.

Input:
	char *path: 	string with file path.
	char **lines: 	pointer to array of pointers of strings
					with enough memory to hold all the lines.
	size_t MaxRead: memory size of each line in chars.
	char *comment: 	comment character.

Output:
	NULL:			if file not found.
	char **lines:	input pointer defined above.
*/
char **
ReadTxtLines(char **lines, size_t maxRead, 
				const char *path, const char *comment);


/*
Reads data from a file, separated into rows and columns
by an input delimiter

Input:
	size_t *shape: 	pointer to array of two members, stores
					number of rows and columns of data.
	size_t maxSize:	maximum size in which to store file line.
	char *path: 	string with file path.
	char delim:		character data delimiter.
	char comment:	character that indicates a comment to skip
					in the file.
Output:
	char **data:	pointer to allocated memory of size
					shape[0] * shape[1] * maxSize
					Individual strings can be accessed via
					data[r*cols + c]
					where 'r' and 'c' are the row and column
					of the string, and 'cols' is the total number
					of columns.
					As it is allocated, it must be freed afterwards.
					Both the pointer **data and the individual strings
					must be freed.
	NULL:			If file not found, empty, or has uenxpected format;
					and if memory allocation error occurs.
*/
char **
GenFromTxt(const char *path, size_t *shape, const size_t maxSize, 
			const char delim, const char comment);


/*
Saves an array of strings 'data' into a file as lines,
lcoated at 'path'.
Returns a pointer to the first string on success,
and NULL otherwise.
*/
char *
SaveToTxt(char **data, size_t lines, const char *path);


/*
Converts an array of doubles into strings,
which are saved at location 'dest'.
*/
char **
flttostr_arr(double *arr, size_t len, char **dest);


/*
Converts an array of ints into strings,
which are saved at location 'dest'.
*/
char **
inttostr_arr(int *arr, size_t len, char **dest);


//array of ints into strings



#endif