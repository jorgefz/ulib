
# C-Utils

*Useful functions for the C Programming Language*

Contains several small useful functions for C 
using only the standard libraries.
These functions can be classified into:
* New Data types
* Memory Management
* String Manipulation
* 1D number array manipulation
* 2D matrix manipulation (WIP)
* File manipulation (WIP)

## Data Types
The unsigned integer type is shortened to simply 'uint'.

```c
typedef unsigned int uint;
```

## Memory

*Safe Memory Allocation*.
Allocates a number of input bytes using 'malloc'.
On fail, it prints an error message to stderr
and exits the program with error code "-1".

```c
void *ptr = xmalloc(size_t bytes)
```

*Safe Memory Freeing*.
Attempts to free a pointer. On fail, it prints
an error message.

```c
void ret_val = xfree(void *ptr)
```


## Strings

*String copying (allocated)*
Copies an input string into allocated memory,
and returns a pointer to it.
Note that it must be freed afterwards.
```c
char *strcpyA(const char *str)
```

*String slicing*.
Slices a string at two input points *i* and *j*,
keeping the characters at both indices.
Returns pointer to sliced string.
On fail, it returns a NULL pointer.
```c	
char *strslc(char *s, size_t i, size_t j)
```

*String reversing*.
Reverses the order of the characters in a string.
Returns pointer to reversed string.
On fail, it returns a NULL pointer.

```c
char *strrev(char *s)
```

## 1D Integer Arrays

*Array of zeros*.
Generate an array of integers equal to zero
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *intzeros(int *a, size_t size)
```

*Array of zeros (allocated)*.
Allocate and generate an array of integers equal to zero.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
int *intzerosA(size_t size)
```

*Array of ones*.
Generate an array of integers equal to one,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *intones(int *a, size_t size)
```

*Array of ones (allocated)*.
Allocate and generate an array of integers equal to one.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
int *intonesA(size_t size)
```

*Array of same values*.
Generate an array of integers equal to an input value,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *intval(int *a, size_t size, int value)
```

*Array of same values (allocated)*.
Allocate and generate an array of integers equal to an input value.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
int *intvalA(size_t size, int value)
```

*Array of values in range*.
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step',
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *intrange(int *a, size_t size, int start, int step)
```

*Array of values in range (allocated)*.
Allocate and generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
int *intrangeA(size_t size, int start, int step)
```

*Print integer array*.
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.

```c
void intprint(const int *a, size_t size)
```

*Concatenate two arrays*.
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.

```c
int *intcat(int *dest, const int *a, size_t as, const int *b, size_t bs)
```

*Concatenate two arrays (allocated)*.
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.

```c
int *intcatA(const int *a, size_t as, const int *b, size_t bs)
```

*Copy an array*.
Copies the values of an array into another,
and returns a pointer ot it.
On fail, it returns a NULL pointer.

```c
int *intcpy(int *dest, const int *src, size_t s)
```

*Copy an array (allocated)*.
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.

```c
int *intcpyA(const int *src, size_t s)
```

*Reverse an array*.
Reverses the values of an input array
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns the NULL pointer.

```c
int *intrev(int *arr, size_t s)
```

*Find maximum*.
Finds the maximum value in an array,
and returns the value.
```c
int intmax(const int *arr, size_t len)
```

*Find index of maximum*.
Finds the maximum value in an array,
and returns its index in the array.
```c
size_t intimax(const int *arr, size_t len)
```

*Find minimum*.
Finds the minimum value in an array,
and returns the value.
```c
int intmin(const int *arr, size_t len)
```

*Find index of minimum*.
Finds the minimum value in an array,
and returns its index in the array.
```c
size_t intimin(const int *arr, size_t len)
```

*Sum array members*.
Sums array members and returns the result.
```c
size_t intsum(const int *arr, size_t len)
```

*Make array members positive*.
Changes the sign of all array members to positive.
```c
int *intpos(int *arr, size_t len)
```

*Make array members negative*.
Changes the sign of all array members to negative.
```c
int *intneg(int *arr, size_t len)
```

*Switch sign of array*.
Switches the sign of array members to positive if it
was negative, and viceversa.
```c
int *intsign(int *arr, size_t len)
```

*Roll array elements*.
Moves the position of all array members
an input number of steps forward (positive offset)
of backward (negative offset).
```c
int *introll(int *arr, size_t len, int offset)
```

*Delete array element*.
Removes element of given index from array,
and returns a pointer to it.
Note that memory of array is not reduced.
```c
int *intdel(int *arr, size_t len, size_t index)
```

*Insert array element*.
Inserts a given value at the specified index
of an array of given length.
The result is stored in an input array 'dest'
and a pointer to it is returned.
Note: 'dest' must have enough memory for an extra element.
```c
int *intins(int *dest, const int *arr, size_t len, size_t index, int val)
```

*Insert array element (allocated)*.
Inserts a given value 'val' at the specified index
of an array 'arr' of given length 'len'.
The result is allocated into an array of size 'len+1'
and a pointer to it is returned.
Note: the return array must be freed after its use.
```c
int *intinsA(const int *arr, size_t len, size_t index, int val)
```

*Add two arrays*.
Adds the elements of two arrays of equal length to
each other, and returns a pointer to the first array.
```c
int *intadd(int *dest, const int *arr, size_t len)
```

*Subtract two arrays*.
Subtracts the elements of two arrays of equal length, 
and returns a pointer to the first array.
```c
int *intsub(int *dest, const int *arr, size_t len)
```

*Multiply two arrays*.
Multiplies the elements of two arrays of equal length
to one another, and returns a pointer to the first array.
```c
int *intmult(int *dest, const int *arr, size_t len)
```

*Applies input function to array members*.
Computes a given function with each array element as
the single argument. The function must return an int type.
The return values of the function are saved in the memory
of the input array, and a pointer to it is returned.
```c
int *intfunc(int (*func)(), int *arr, size_t len)
```

*Compare two arrays*.
Compares two arrays 'a' and 'b' and returns a value that
is zero only if a==b.
```c
int intcmp( const double *a, const double *b, size_t len)
```

*Add scalar to array*.
Adds the value of an integer scalar to all array elements.
```c
int *intsadd(int *arr, size_t len, int val)
```

*Multiply array by scalar*.
Multiplies each array element by an integer scalar.
```c
int *intsmult(int *arr, size_t len, int val)
```

*Dot product of vector*.
Performs dot product of two arrays and returns the value.
```c
int intdot(const int *a, const int *b, size_t len)
```




## 1D Floating Point Arrays

*Array of zeros*.
Generate an array of integers equal to zero
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *fltzeros(double *arr, size_t size)
```

*Array of zeros (allocated)*.
Allocate and generate an array of integers equal to zero.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
double *fltzerosA(size_t size)
```

*Array of ones*.
Generate an array of integers equal to one,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *fltones(double *a, size_t size)
```

*Array of ones (allocated)*.
Allocate and generate an array of integers equal to one.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
double *fltonesA(size_t size)
```

*Array of same values*.
Generate an array of integers equal to an input value,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *fltval(double *a, size_t size, double value)
```

*Array of same values (allocated)*.
Allocate and generate an array of integers equal to an input value.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
double *fltvalA(size_t size, double value)
```

*Array of values in range*.
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step',
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *fltrange(double *a, size_t size, double start, double step)
```

*Array of values in range (allocated)*.
Allocate and generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
double *fltrangeA(size_t size, double start, double step)
```

*Print integer array*.
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.
```c
void intprint(const double *a, size_t size)
```

*Concatenate two arrays*.
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.
```c
double *fltcat(double *dest, const double *a, size_t as, const double *b, size_t bs)
```

*Concatenate two arrays (allocated)*.
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.

```c
double *fltcatA(const double *a, size_t as, const double *b, size_t bs)
```

*Copy an array*.
Copies the values of an array into another,
and returns a pointer ot it.
On fail, it returns a NULL pointer.

```c
double *fltcpy(double *dest, const double *src, size_t s)
```

*Copy an array (allocated)*.
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.

```c
double *fltcpyA(const double *src, size_t s)
```

*Reverse an array*.
Reverses the values of an input array
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns the NULL pointer.

```c
double *fltrev(double *arr, size_t s)
```

*Find maximum*.
Finds the maximum value in an array,
and returns the value.
```c
double fltmax(const double *arr, size_t len)
```

*Find index of maximum*.
Finds the maximum value in an array,
and returns its index in the array.
```c
size_t fltimax(const double *arr, size_t len)
```

*Find minimum*.
Finds the minimum value in an array,
and returns the value.
```c
double fltmin(const double *arr, size_t len)
```

*Find index of minimum*.
Finds the minimum value in an array,
and returns its index in the array.
```c
size_t fltimin(const double *arr, size_t len)
```

*Sum array members*.
Sums array members and returns the result.
```c
size_t fltsum(const double *arr, size_t len)
```

*Make array members positive*.
Changes the sign of all array members to positive.
```c
double *fltpos(double *arr, size_t len)
```

*Make array members negative*.
Changes the sign of all array members to negative.
```c
double *fltneg(double *arr, size_t len)
```

*Switch sign of array*.
Switches the sign of array members to positive if it
was negative, and viceversa.
```c
double *fltsign(double *arr, size_t len)
```

*Roll array elements*.
Moves the position of all array members
an input number of steps forward (positive offset)
of backward (negative offset).
```c
double *fltroll(double *arr, size_t len, int offset)
```

*Delete array element*.
Removes element of given index from array,
and returns a pointer to it.
Note that memory of array is not reduced.
```c
double *fltdel(double *arr, size_t len, size_t index)
```

*Insert array element*.
Inserts a given value at the specified index
of an array of given length.
The result is stored in an input array 'dest'
and a pointer to it is returned.
Note: 'dest' must have enough memory for an extra element.
```c
double *fltins(double *dest, const double *arr, size_t len, size_t index, double val)
```

*Insert array element (allocated)*.
Inserts a given value 'val' at the specified index
of an array 'arr' of given length 'len'.
The result is allocated into an array of size 'len+1'
and a pointer to it is returned.
Note: the return array must be freed after its use.
```c
double *fltinsA(const double *arr, size_t len, size_t index, double val)
```

*Add two arrays*.
Adds the elements of two arrays of equal length to
each other, and returns a pointer to the first array.
```c
double *fltadd(double *dest, const double *arr, size_t len)
```

*Subtract two arrays*.
Subtracts the elements of two arrays of equal length, 
and returns a pointer to the first array.
```c
double *fltsub(double *dest, const double *arr, size_t len)
```

*Multiply two arrays*.
Multiplies the elements of two arrays of equal length
to one another, and returns a pointer to the first array.
```c
double *fltmult(double *dest, const double *arr, size_t len)
```

*Applies input function to array members*.
Computes a given function with each array element as
the single argument. The function must return an int type.
The return values of the function are saved in the memory
of the input array, and a pointer to it is returned.
```c
double *fltfunc(double (*func)(), double *arr, size_t len)
```

*Compare two arrays*.
Compares two arrays 'a' and 'b' and returns a value that
is zero only if a==b.
```c
double fltcmp(const double *a, const double *b, size_t len)
```

*Add scalar to array*.
Adds the value of an integer scalar to all array elements.
```c
double *fltsadd(double *arr, size_t len, double val)
```

*Multiply array by scalar*.
Multiplies each array element by an integer scalar.
```c
double *fltsmult(double *arr, size_t len, double val)
```

*Inverse of array elements*.
Calculates the inverse value 1/x of each array element.
```c
double *fltinv(double *arr, size_t len)
```

*Dot product of vector*.
Performs dot product of two arrays and returns the value.
```c
double fltdot(const double *a, const double *b, size_t len)
```

*Calculates exp() of array elements*.
```c
double *fltexp(double *arr, size_t len)
```

*Calculates square root of array elements*.
```c
double *fltsqrt(double *arr, size_t len)
```

*Calculates sine of array elements*.
```c
double *fltsin(double *arr, size_t len)
```

*Calculates cosine of array elements*.
```c
double *fltcos(double *arr, size_t len)
```

*Calculates natural log of array elements*.
```c
double *fltlog(double *arr, size_t len)
```

*Calculates base 10 log of array elements*.
```c
double *fltlog10(double *arr, size_t len)
```

*Get magnitude of array vector*.
```c
double fltmag(const double *arr, size_t len)
```

*Find if array member is a value*.
Returns array of 0s and 1s, where 0 is not value, and 1 is value.
Note that return array must have enough memory.
```c
int *fltisval(int *dest, const double *arr, size_t len, double val)
```

*Looks for NaN values in array*.
Returns array of 0s and 1s.
Note that return array must have enough memory.
```c
int *fltisnan(int *dest, const double *arr, size_t len)
```


## 1D Array Data Type Conversion

*Convert array of integers into doubles*.
Casts an array of integers into doubles values, 
and returns a pointer to it.
```c
double *inttoflt(double *dest, const int *arr, size_t len)
```

*Converts an array of integers into an array of doubles*.
allocates the new array, and returns a pointer to it.
```c
double *inttofltA(const int *arr, size_t len)
```

*Convert array of doubles into integers*.
Casts an array of doubles into integer values, 
and returns a pointer to it.
```c
int *flttoint(int *dest, const double *arr, size_t len)
```

*Convert array of doubles into integers*.
Casts an array of doubles into integer values, 
allocates the new array, and returns a pointer to it.
```c
int *flttointA(const double *arr, size_t len)
```


## Input / Output

*Input string*
Prompts the user to input a string using an input message
'msg'. The result is stored in the location of 'dest'
and a pointer is returned to it.
On fail, it returns NULL.
```c
char *getstr(char *dest, const char *msg)
```

*String to integer*
Converts an input string 'str' into an integer,
stores the result in the location of 'dest'
and returns the pointer.
On fail, it returns NULL.
```c
int *strtoint(int *dest, const char *str)
```

*String to double*
Converts an input string 'str' into a double,
stores the result in the location of 'dest'
and returns the pointer.
On fail, it returns NULL.
```c
double *strtoflt(double *dest, const char *str)
```

*Count tokens in string*
Given a string and a delimiter,
it returns the number of tokens in the string,
For example, for a string "aa;bb;cc" and a delimiter ";",
this function returns '3', since there are three tokens
in the string ('aa', 'bb', 'cc').
On fail, it returns zero.
```c
size_t strtokn(char *str, const char *delim)
```

*Partition string*
Given an input pointer to a string 'ptr'
and a delimiter 'delim', it searches for the first instance
of the delimiter, subtitutes it with the terminator character '\0',
and returns a pointer to the subsequent location (ptr+1). 
```c
char *strpar(char *ptr, const char *delim)
```

*Split string*
Given a string 'str' and a delimiter 'delim',
it splits the string at the delimiters, stores
the pointers to the tokens in 'dest', and returns
a pointer to it.
On fail, it returns NULL.
```c
char **strsplit(char **dest, char *str, const char delim)
```

*Count lines in a file*
Counts the lines in a text file located at the path 'path', 
and returns the value. The counting process discards empty lines
and comment lines, defined by an input starting character 'comment'.
```c
size_t
CountTxtLines(size_t maxRead, const char *path, const char *comment)
```

*Read lines in a file*

Reads the lines in a file, skipping the empty ones and the comments, as defined by a comment character 'comment'. The lines are stored as strings at the input array of strings '\*\*lines' and a pointer to it is returned. The maximum memory in which to copy read lines is defined by 'maxRead'. On fail, a NULL pointer is returned.
```c
char **ReadTxtLines(char **lines, size_t maxRead, const char *path, const char *comment)
```

*Load data from file*

Automatically reads data from an input file at location 'path'. The data is expected to be organised in rows and columns, in which columns are separated by a delimiter character 'delim', and individual lines are stored in memory with maximum size 'maxSize'. Comments starting with input character 'comment' are skipped. The size of the data to read is stored in input array 'shape' of two members, storing the number of rows and the number of columns.
```c
char **GenFromTxt(const char *path, size_t *shape, const size_t maxSize, const char delim, const char comment)
```

For example, there is a file 'data.txt' in the same directory, with the contents:
```c
# This is a comment
star_name;parallax;Vmag;Vmag_error
HR_8799;1.15;15;0.3
HIP_23585;2.87;18;0.7
```
Here, the data delimiter is set as semicolon ';', the comment character is set as a hash '#' and the max length in which to store a line is set to '100'. An array of two integers 'shape[2]' is initialised to store the number of rows and columns of the data, and a pointer to it is passed to the function.

The function will return a pointer 'data' to allocated memory. Each data field in the file is accessed via 'data[row\*columns + col]', where 'row' and 'col' are the current row and column of the data point, and 'columns' is the total number of columns. The size of the data matrix, that is number of rows and columns, is saved at the input integer array 'shape[0]' and 'shape[1]', respectively.

Once the data is not necessary, it must be freed by first iterating through every individual string and freeing it, and then freeing the main pointer '\*\*data'.



### *WIP*.
* SaveToTxt
* Array of integers into strings
* Array of doubles into strings

* Sort array in ascending/descending order (use qsort).
* Sort and return array of indices (argsort).
 
