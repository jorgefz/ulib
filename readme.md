
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

*String slicing*.
Slices a string at two input points *i* and *j*,
keeping the characters at both indices.
Returns pointer to sliced string.
On fail, it returns a NULL pointer.

```c	
char *str = strslc(char *s, size_t i, size_t j)
```

*String reversing*.
Reverses the order of the characters in a string.
Returns pointer to reversed string.
On fail, it returns a NULL pointer.

```c
char *str = strrev(char *s)
```

## 1D Integer Arrays

*Array of zeros*.
Generate an array of integers equal to zero
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *arr = intzeros(int *a, size_t size)
```

*Array of zeros (allocated)*.
Allocate and generate an array of integers equal to zero.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
int *arr = a_intzeros(size_t size)
```

*Array of ones*.
Generate an array of integers equal to one,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *arr = intones(int *a, size_t size)
```

*Array of ones (allocated)*.
Allocate and generate an array of integers equal to one.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
int *arr = a_intones(size_t size)
```

*Array of same values*.
Generate an array of integers equal to an input value,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *arr = intval(int *a, size_t size, int value)
```

*Array of same values (allocated)*.
Allocate and generate an array of integers equal to an input value.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
int *arr = a_intval(size_t size, int value)
```

*Array of values in range*.
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step',
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
int *arr = intrange(int *a, size_t size, int start, int step)
```

*Array of values in range (allocated)*.
Allocate and generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
int *arr = a_intrange(size_t size, int start, int step)
```

*Print integer array*.
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.

```c
intprint(const int *a, size_t size)
```

*Concatenate two arrays*.
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.

```c
int *arr = intcat(int *dest, const int *a, size_t as, const int *b, size_t bs)
```

*Concatenate two arrays (allocated)*.
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.

```c
int *arr = a_intcat(const int *a, size_t as, const int *b, size_t bs)
```

*Copy an array*.
Copies the values of an array into another,
and returns a pointer ot it.
On fail, it returns a NULL pointer.

```c
int *arr = intcpy(int *dest, const int *src, size_t s)
```

*Copy an array (allocated)*.
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.

```c
int *arr = a_intcpy(const int *src, size_t s)
```

*Reverse an array*.
Reverses the values of an input array
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns the NULL pointer.

```c
int *arr = intrev(int *arr, size_t s)
```

*Find maximum*.
Finds the maximum value in an array,
and returns the value.
```c
int max = intmax(const int *arr, size_t len)
```

*Find index of maximum*.
Finds the maximum value in an array,
and returns its index in the array.
```c
size_t imax = intimax(const int *arr, size_t len)
```

*Find minimum*.
Finds the minimum value in an array,
and returns the value.
```c
int min = intmin(const int *arr, size_t len)
```

*Find index of minimum*.
Finds the minimum value in an array,
and returns its index in the array.
```c
size_t imin = intimin(const int *arr, size_t len)
```

*Sum array members*.
Sums array members and returns the result.
```c
size_t sum = intsum(const int *arr, size_t len)
```

*Make array members positive*.
Changes the sign of all array members to positive.
```c
int *arr = intpos(int *arr, size_t len)
```

*Make array members negative*.
Changes the sign of all array members to negative.
```c
int *arr = intneg(int *arr, size_t len)
```

*Switch sign of array*.
Switches the sign of array members to positive if it
was negative, and viceversa.
```c
int *arr = intsign(int *arr, size_t len)
```

*Roll array elements*.
Moves the position of all array members
an input number of steps forward (positive offset)
of backward (negative offset).
```c
int *arr ±= introll(int *arr, size_t len, int offset)
```

*Delete array element*.
Removes element of given index from array,
and returns a pointer to it.
Note that memory of array is not reduced.
```c
int *arr = intdel(int *arr, size_t len, size_t index)
```

*Insert array element*.
Inserts a given value at the specified index
of an array of given length.
The result is stored in an input array 'dest'
and a pointer to it is returned.
Note: 'dest' must have enough memory for an extra element.
```c
int *dest = intins(int *dest, const int *arr, size_t len, size_t index, int val)
```

*Insert array element (allocated)*.
Inserts a given value 'val' at the specified index
of an array 'arr' of given length 'len'.
The result is allocated into an array of size 'len+1'
and a pointer to it is returned.
Note: the return array must be freed after its use.
```c
int *dest = a_intins(const int *arr, size_t len, size_t index, int val)
```

*Add two arrays*.
Adds the elements of two arrays of equal length to
each other, and returns a pointer to the first array.
```c
int *dest = intadd(int *dest, const int *arr, size_t len)
```

*Subtract two arrays*.
Subtracts the elements of two arrays of equal length, 
and returns a pointer to the first array.
```c
int *dest = intsub(int *dest, const int *arr, size_t len)
```

*Multiply two arrays*.
Multiplies the elements of two arrays of equal length
to one another, and returns a pointer to the first array.
```c
int *dest = intmult(int *dest, const int *arr, size_t len)
```

*Applies input function to array members*.
Computes a given function with each array element as
the single argument. The function must return an int type.
The return values of the function are saved in the memory
of the input array, and a pointer to it is returned.
```c
int *arr = intfunc(int (*func)(), int *arr, size_t len)
```

*Compare two arrays*.
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, positive if a>b, and negative if a < b.
```c
int ret_val = intcmp( const double *a, const double *b, size_t len)
```

*Add scalar to array*.
Adds the value of an integer scalar to all array elements.
```c
int *arr = intsadd(int *arr, size_t len, int val)
```

*Multiply array by scalar*.
Multiplies each array element by an integer scalar.
```c
int *arr = intsmult(int *arr, size_t len, int val)
```

*Dot product of vector*.
Performs dot product of two arrays and returns the value.
```c
int ret_val = intdot(const int *a, const int *b, size_t len)
```




## 1D Floating Point Arrays

*Array of zeros*.
Generate an array of integers equal to zero
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *arr = fltzeros(double *arr, size_t size)
```

*Array of zeros (allocated)*.
Allocate and generate an array of integers equal to zero.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
double *arr = a_fltzeros(size_t size)
```

*Array of ones*.
Generate an array of integers equal to one,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *arr = fltones(double *a, size_t size)
```

*Array of ones (allocated)*.
Allocate and generate an array of integers equal to one.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
double *arr = a_fltones(size_t size)
```

*Array of same values*.
Generate an array of integers equal to an input value,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *arr = fltval(double *a, size_t size, double value)
```

*Array of same values (allocated)*.
Allocate and generate an array of integers equal to an input value.
It returns a pointer to the allocated array.
Note that it must be freed after its use.

```c
double *arr = a_fltval(size_t size, double value)
```

*Array of values in range*.
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step',
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *arr = fltrange(double *a, size_t size, double start, double step)
```

*Array of values in range (allocated)*.
Allocate and generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
double *arr = a_fltrange(size_t size, double start, double step)
```

*Print integer array*.
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.
```c
intprint(const double *a, size_t size)
```

*Concatenate two arrays*.
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.
```c
double *arr = fltcat(double *dest, const double *a, size_t as, const double *b, size_t bs)
```

*Concatenate two arrays (allocated)*.
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.

```c
double *arr = a_fltcat(const double *a, size_t as, const double *b, size_t bs)
```

*Copy an array*.
Copies the values of an array into another,
and returns a pointer ot it.
On fail, it returns a NULL pointer.

```c
double *dest = fltcpy(double *dest, const double *src, size_t s)
```

*Copy an array (allocated)*.
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.

```c
double *arr = a_fltcpy(const double *src, size_t s)
```

*Reverse an array*.
Reverses the values of an input array
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns the NULL pointer.

```c
double *arr = fltrev(double *arr, size_t s)
```

*Find maximum*.
Finds the maximum value in an array,
and returns the value.
```c
double max = fltmax(const double *arr, size_t len)
```

*Find index of maximum*.
Finds the maximum value in an array,
and returns its index in the array.
```c
size_t imax = fltimax(const double *arr, size_t len)
```

*Find minimum*.
Finds the minimum value in an array,
and returns the value.
```c
double min = fltmin(const double *arr, size_t len)
```

*Find index of minimum*.
Finds the minimum value in an array,
and returns its index in the array.
```c
size_t imin = fltimin(const double *arr, size_t len)
```

*Sum array members*.
Sums array members and returns the result.
```c
size_t sum = fltsum(const double *arr, size_t len)
```

*Make array members positive*.
Changes the sign of all array members to positive.
```c
double *arr = fltpos(double *arr, size_t len)
```

*Make array members negative*.
Changes the sign of all array members to negative.
```c
double *arr = fltneg(double *arr, size_t len)
```

*Switch sign of array*.
Switches the sign of array members to positive if it
was negative, and viceversa.
```c
double *arr = fltsign(double *arr, size_t len)
```

*Roll array elements*.
Moves the position of all array members
an input number of steps forward (positive offset)
of backward (negative offset).
```c
double *arr = fltroll(double *arr, size_t len, int offset)
```

*Delete array element*.
Removes element of given index from array,
and returns a pointer to it.
Note that memory of array is not reduced.
```c
double *arr = fltdel(double *arr, size_t len, size_t index)
```

*Insert array element*.
Inserts a given value at the specified index
of an array of given length.
The result is stored in an input array 'dest'
and a pointer to it is returned.
Note: 'dest' must have enough memory for an extra element.
```c
double *dest = fltins(double *dest, const double *arr, size_t len, size_t index, double val)
```

*Insert array element (allocated)*.
Inserts a given value 'val' at the specified index
of an array 'arr' of given length 'len'.
The result is allocated into an array of size 'len+1'
and a pointer to it is returned.
Note: the return array must be freed after its use.
```c
double *dest = a_fltins(const double *arr, size_t len, size_t index, double val)
```

*Add two arrays*.
Adds the elements of two arrays of equal length to
each other, and returns a pointer to the first array.
```c
double *dest = fltadd(double *dest, const double *arr, size_t len)
```

*Subtract two arrays*.
Subtracts the elements of two arrays of equal length, 
and returns a pointer to the first array.
```c
double *dest = fltsub(double *dest, const double *arr, size_t len)
```

*Multiply two arrays*.
Multiplies the elements of two arrays of equal length
to one another, and returns a pointer to the first array.
```c
double *dest = fltmult(double *dest, const double *arr, size_t len)
```

*Applies input function to array members*.
Computes a given function with each array element as
the single argument. The function must return an int type.
The return values of the function are saved in the memory
of the input array, and a pointer to it is returned.
```c
double *arr = fltfunc(double (*func)(), double *arr, size_t len)
```

*Compare two arrays*.
Compares two arrays 'a' and 'b' and returns a value that
is zero if a==b, positive if a>b, and negative if a < b.
```c
double ret_val = fltcmp(const double *a, const double *b, size_t len)
```

*Add scalar to array*.
Adds the value of an integer scalar to all array elements.
```c
double *arr = fltsadd(double *arr, size_t len, double val)
```

*Multiply array by scalar*.
Multiplies each array element by an integer scalar.
```c
double *arr = fltsmult(double *arr, size_t len, double val)
```

*Inverse of array elements*.
Calculates the inverse value 1/x of each array element.
```c
double *arr = fltinv(double *arr, size_t len)
```

*Dot product of vector*.
Performs dot product of two arrays and returns the value.
```c
double ret_val = fltdot(const double *a, const double *b, size_t len)
```

*Calculates exp() of array elements*.
```c
double *arr = fltexp(double *arr, size_t len)
```

*Calculates square root of array elements*.
```c
double *arr = fltsqrt(double *arr, size_t len)
```

*Calculates sine of array elements*.
```c
double *arr = fltsin(double *arr, size_t len)
```

*Calculates cosine of array elements*.
```c
double *arr = fltcos(double *arr, size_t len)
```

*Calculates natural log of array elements*.
```c
double *arr = fltlog(double *arr, size_t len)
```

*Calculates base 10 log of array elements*.
```c
double *arr = fltlog10(double *arr, size_t len)
```

*Get magnitude of array vector*.
```c
double ret_val = fltmag(const double *arr, size_t len)
```

*Find if array member is a value*.
Returns array of 0s and 1s, where 0 is not value, and 1 is value.
Note that return array must have enough memory.
```c
int *arr = fltisval(int *dest, const double *arr, size_t len, double val)
```

*Looks for NaN values in array*.
Returns array of 0s and 1s.
Note that return array must have enough memory.
```c
int *arr = fltisnan(int *dest, const double *arr, size_t len)
```

*Convert array of integers into doubles*.
Casts an array of integers into doubles values, 
and returns a pointer to it.
```c
double *arr = inttoflt(double *dest, const int *arr, size_t len)
```

*Converts an array of integers into an array of doubles*.
allocates the new array, and returns a pointer to it.
```c
double *arr = a_inttoflt(const int *arr, size_t len)
```

*Convert array of doubles into integers*.
Casts an array of doubles into integer values, 
and returns a pointer to it.
```c
int *arr = flttoint(int *dest, const double *arr, size_t len)
```

*Convert array of doubles into integers*.
Casts an array of doubles into integer values, 
allocates the new array, and returns a pointer to it.
```c
int *arr = a_flttoint(const double *arr, size_t len)
```


### *WIP*.
* Sort array in ascending/descending order (use qsort).
* Sort and return array of indices (argsort).
 
