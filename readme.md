
# C-Utils

*Useful functions for the C Programming Language*

Contains several small useful functions for C 
using only the standard libraries.
These functions can be classified into:
* Useful data types
* Memory Management
* String Manipulation
* 1D number array manipulation
* 2D matrix operations (WIP)
* File manipulation (WIP)

## Data Types
The unsigned integer type is shortened to simply 'uint'.

```c
typedef unsigned int uint;
```

## Memory

*Safe Memory Allocation*
Allocates a number of input bytes using 'malloc'.
On fail, it returns a NULL pointer.

```c
void *ptr = xmalloc(size_t bytes)
```

*Safe Memory Freeing*
Attempts to free a pointer.
On success, it returns 0.
Otherwise, it returns -1.

```c
int ret_val = xfree(void *ptr)
```


## Strings

*String slicing*
Slices a string at two input points *i* and *j*.
Returns pointer to sliced string.
On fail, it returns a NULL pointer.

```c	
char *str = strslc(char *s, const size_t i, const size_t j)
```

*String reversing*
Reverses the order of the characters in a string.
Returns pointer to reversed string.
On fail, it returns a NULL pointer.

```c
char *str = strrev(char *s)
```

## 1D Arrays

*Array of zeros*
Generate an array of integers equal to zero

```c
int *arr = intzeros(int *a, size_t size)
```

*Array of ones*
Generate an array of integers equal to one

```c
int *arr = intones(int *a, size_t size)
```

*Array of same values*
Generate an array of integers equal to an input value.

```c
int *arr = intval(int *a, size_t size, int value)
```

*Array of values in range*
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.

```c
int *arr = intrange(int *a, size_t size, int start, int step)
```

*Print integer array*
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.

```c
int *arr = intprint(int *a, size_t size)
```

*Concatenate two arrays*
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.

```c
int *arr = intcat(int *dest, int *a, size_t as, int *b, size_t bs)
```

*Copy an array*
Copies the values of an array into another.
On fail, it returns a NULL pointer.

```c
int *arr = intcpy(int *dest, int *src, size_t s)
```

*Reverse an array*
Copies the values of an array into another.
On fail, it returns a NULL pointer.

```c
int *arr = intrev(int *arr, size_t s)
```
	
WIP - Repeat for double datatype



## 2D Number Matrices (WIP)

intadd - add two matrices of integers
	*mat = intadd(*a, *b, rows, cols)
intsub - add two matrices of integers
	*mat = intsub(*a, *b, rows, cols)
	
intmult - multiply the members of two matrices of integers directly
	*mat = intmult(*a, *b, rows, cols)
	
intamult - matrix multiplication of two matrices of integers
	*mat = intmult(*a, *b, rows_a, cols_a)

inttsp - transpose of matrix of integers
	*mat = inttsp(*a, rows, cols)
	
intdet - determinant of matrix of integers
	*mat = intdet(*a, rows, cols)
	
intinv - inverse of matrix of integers
	*mat = intinv(*a, rows, cols)



 