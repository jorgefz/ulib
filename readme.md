
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

*Array of zeros*.
Generate an array of integers equal to zero,
stored at the address to whicht he input pointer points.
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
Generate an array of integers equal to zero,
stored at the address to which the input pointer points.
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
stored at the address to which the input pointer points.
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
starting value 'start' and a step size 'step'.
Stored at the address to which the input pointer points.
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
intprint(int *a, size_t size)
```

*Concatenate two arrays*.
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.

```c
int *arr = intcat(int *dest, int *a, size_t as, int *b, size_t bs)
```

*Concatenate two arrays (allocated)*.
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.

```c
int *arr = a_intcat(int *a, size_t as, int *b, size_t bs)
```

*Copy an array*.
Copies the values of an array into another.
On fail, it returns a NULL pointer.

```c
int *arr = intcpy(int *dest, int *src, size_t s)
```

*Copy an array (allocated)*.
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.

```c
int *arr = a_intcpy(int *src, size_t s)
```

*Reverse an array*
Reverses the values of an input array,
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns NULL.

```c
int *arr = intrev(int *arr, size_t s)
```

*Find maximum*.
Finds the maximum value in an array,
and returns the value.
```c
int max = intmax(const int *arr, const size_t len)
```

*Find index of maximum*.
Finds the maximum value in an array,
and returns array index of its location.
```c
size_t imax = intimax(const int *arr, const size_t len)
```

*Find minimum*.
Finds the minimum value in an array,
and returns the value.
```c
int min = intmin(const int *arr, const size_t len)
```

*Find index of minimum*.
Finds the minimum value in an array,
and returns array index of its location.
```c
size_t imin = intimin(const int *arr, const size_t len)
```

### *WIP*.
* Sort array in ascending/descending order.
* Sort and return array of old indices (argsort).
* Switch sign of array members.
* Set all array members to positice/negative.
* Add/Subtract/multiply/divide members of two arrays.
* Compare two arrays.
* Repeat for double datatype



## 2D Number Matrices (WIP)

* Add two matrices of integers.
	*mat = mintadd(*a, *b, rows, cols)
* Subtract two matrices of integers.
	*mat = mintsub(*a, *b, rows, cols)
* Multiply the members of two matrices of integers directly.
	*mat = mintmult(*a, *b, rows, cols)
* Divide the members of two matrices of integers directly.
	*mat = mintdiv(*a, *b, rows, cols)

 