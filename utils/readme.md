
# C-Utils

*Useful functions and data structures for the C Programming Language*

This repository contains a small number of single-header libraries that add useful data structures. The code is fully written in ANSI C (C89).

* string.h: string container and manipulator.
* array.h: numeric array of static size.
* vector.h: generic resizeable container.
* arglib.h: command line argument manager.
* io.h: file input and output (WIP).

## String.h

Extends functionality of c strings in a similar manner as C++ std::string.

### Initialising

A string may be initialized from a null-terminated `char*` array with `string_new` , which returns a pointer to a `string` structure.
```c
string* my_string = string_new("Hello, World!");
```
The string's length can be retrieved with `my_string->length`, and the underlying char array with `my_string->str`. The predefined string methods can be called with function pointers.
```c
string* s->copy(string* s);
```

### Freeing (destructor)
To free the string after it is no longer needed, use the following function:
```c
void  s->free(string* s);
```
After using this function, the string pointer `my_string` can no longer be used.

### Printing
```c
void  s->print(string* s);
```
```c
printf("%s\n", s->str);
```

### Getters

This returns a pointer to a specified location in the string, with bounds checking. The input index 'j' can be positive (to indicate an offset from the beginning), or negative (an offset from the end).
```c
char* s->at(string* s, int j);
```
For example, `my_string->at(my_string, -1)` returns a char pointer to the last character in the string (before the terminator).


Thus fucntion returns a single character at the specified location in the string, which bounds checking. The input index can be both positive or negative.
```c
char  s->getc(string* s, int j);
```

### String Manipulation
This extends the string, inserting an input char array at the location of index 'j', which may be positive or negative.
```c
string* s->insert(string* s, const char* substr, int j);
```

This removes 'n' characters from the string from the location at index 'j', shrinking the string to save memory.
```c
string* s->erase(string* s, int j, unsigned int n);
```


## Array.h

This section is a Work in Progress.

### Initialisation
```c
array* array_new(ulong size, uint type);
```
### Array methods:
```c
void (*free)(struct array__struct*);
void (*print)(struct array__struct*);

void (*fill)(struct array__struct*, ...);
void (*range)(struct array__struct*, ...);
void (*linspace)(struct array__struct*, ...);
void (*from_c_array)(struct array__struct*, const void* c_arr);

void (*reverse)(struct array__struct*);

void (*seti)(struct array__struct*, ulong ind, int value);
void (*setf)(struct array__struct*, ulong ind, double value);

int (*geti)(struct array__struct*, ulong ind);
double (*getf)(struct array__struct*, ulong ind);
char* (*at)(struct array__struct*, ulong ind);


	/* Statistics */
int (*maxi)(struct array__struct*);
double (*maxf)(struct array__struct*);
int (*mini)(struct array__struct*);
double (*minf)(struct array__struct*);
uint (*imax)(struct array__struct*);
uint (*imin)(struct array__struct*);
int (*sumi)(struct array__struct*);
double (*sumf)(struct array__struct*);
double (*mean)(struct array__struct*);
	
```

## Vector.h

This section is a Work in Progress.


# Old Functions (IGNORE)

## Strings

### String copying (allocated)
Copies an input string into allocated memory,
and returns a pointer to it.
Note that it must be freed afterwards.
```c
char *strcpyA(const char *str)
```

### String slicing
Slices a string at two input points *i* and *j*,
keeping the characters at both indices.
Returns pointer to sliced string.
On fail, it returns a NULL pointer.
```c	
char *strslc(char *s, size_t i, size_t j)
```

### String reversing
Reverses the order of the characters in a string.
Returns pointer to reversed string.
On fail, it returns a NULL pointer.
```c
char *strrev(char *s)
```

## 1D Integer Arrays

### Array of zeros
Generate an array of integers equal to zero
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
int *intzeros(int *a, size_t size)
```

### Array of zeros (allocated)
Allocate and generate an array of integers equal to zero.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
int *intzerosA(size_t size)
```

### Array of ones
Generate an array of integers equal to one,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
int *intones(int *a, size_t size)
```

### Array of ones (allocated)
Allocate and generate an array of integers equal to one.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
int *intonesA(size_t size)
```

### Array of same values
Generate an array of integers equal to an input value,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
int *intval(int *a, size_t size, int value)
```

### Array of same values (allocated)
Allocate and generate an array of integers equal to an input value.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
int *intvalA(size_t size, int value)
```

### Array of values in range
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step',
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
int *intrange(int *a, size_t size, int start, int step)
```

### Array of values in range (allocated)
Allocate and generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
int *intrangeA(size_t size, int start, int step)
```

### Print integer array
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.

```c
void intprint(const int *a, size_t size)
```

### Concatenate two arrays
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.
```c
int *intcat(int *dest, const int *a, size_t as, const int *b, size_t bs)
```

### Concatenate two arrays (allocated)
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.
```c
int *intcatA(const int *a, size_t as, const int *b, size_t bs)
```

### Copy an array
Copies the values of an array into another,
and returns a pointer ot it.
On fail, it returns a NULL pointer.
```c
int *intcpy(int *dest, const int *src, size_t s)
```

### Copy an array (allocated)
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.
```c
int *intcpyA(const int *src, size_t s)
```

### Reverse an array
Reverses the values of an input array
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns the NULL pointer.

```c
int *intrev(int *arr, size_t s)
```

### Find maximum
Finds the maximum value in an array,
and returns the value.
```c
int intmax(const int *arr, size_t len)
```

### Find index of maximum
Finds the maximum value in an array,
and returns its index in the array.
```c
size_t intimax(const int *arr, size_t len)
```

### Find minimum
Finds the minimum value in an array,
and returns the value.
```c
int intmin(const int *arr, size_t len)
```

### Find index of minimum
Finds the minimum value in an array,
and returns its index in the array.
```c
size_t intimin(const int *arr, size_t len)
```

### Sum array members
Sums array members and returns the result.
```c
size_t intsum(const int *arr, size_t len)
```

### Make array members positive
Changes the sign of all array members to positive.
```c
int *intpos(int *arr, size_t len)
```

### Make array members negative
Changes the sign of all array members to negative.
```c
int *intneg(int *arr, size_t len)
```

### Switch sign of array
Switches the sign of array members to positive if it
was negative, and viceversa.
```c
int *intsign(int *arr, size_t len)
```

### Roll array elements
Moves the position of all array members
an input number of steps forward (positive offset)
of backward (negative offset).
```c
int *introll(int *arr, size_t len, int offset)
```

### Delete array element
Removes element of given index from array,
and returns a pointer to it.
Note that memory of array is not reduced.
```c
int *intdel(int *arr, size_t len, size_t index)
```

### Insert array element
Inserts a given value at the specified index
of an array of given length.
The result is stored in an input array 'dest'
and a pointer to it is returned.
Note: 'dest' must have enough memory for an extra element.
```c
int *intins(int *dest, const int *arr, size_t len, size_t index, int val)
```

### Insert array element (allocated)
Inserts a given value 'val' at the specified index
of an array 'arr' of given length 'len'.
The result is allocated into an array of size 'len+1'
and a pointer to it is returned.
Note: the return array must be freed after its use.
```c
int *intinsA(const int *arr, size_t len, size_t index, int val)
```

### Add two arrays
Adds the elements of two arrays of equal length to
each other, and returns a pointer to the first array.
```c
int *intadd(int *dest, const int *arr, size_t len)
```

### Subtract two arrays
Subtracts the elements of two arrays of equal length, 
and returns a pointer to the first array.
```c
int *intsub(int *dest, const int *arr, size_t len)
```

### Multiply two arrays
Multiplies the elements of two arrays of equal length
to one another, and returns a pointer to the first array.
```c
int *intmult(int *dest, const int *arr, size_t len)
```

### Apply function to array
Computes a given function with each array element as
the single argument. The function must return an int type.
The return values of the function are saved in the memory
of the input array, and a pointer to it is returned.
```c
int *intfunc(int (*func)(), int *arr, size_t len)
```

### Compare two arrays
Compares two arrays 'a' and 'b' and returns a value that
is zero only if a==b.
```c
int intcmp( const double *a, const double *b, size_t len)
```

### Add scalar to array
Adds the value of an integer scalar to all array elements.
```c
int *intsadd(int *arr, size_t len, int val)
```

### Multiply array by scalar
Multiplies each array element by an integer scalar.
```c
int *intsmult(int *arr, size_t len, int val)
```

### Dot product of array
Performs dot product of two arrays and returns the value.
```c
int intdot(const int *a, const int *b, size_t len)
```


## 1D Floating Point Arrays

### Array of zeros
Generate an array of integers equal to zero
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
double *fltzeros(double *arr, size_t size)
```

### Array of zeros (allocated)
Allocate and generate an array of integers equal to zero.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
double *fltzerosA(size_t size)
```

### Array of ones
Generate an array of integers equal to one,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.

```c
double *fltones(double *a, size_t size)
```

### Array of ones (allocated)
Allocate and generate an array of integers equal to one.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
double *fltonesA(size_t size)
```

### Array of same values
Generate an array of integers equal to an input value,
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
double *fltval(double *a, size_t size, double value)
```

### Array of same values (allocated)
Allocate and generate an array of integers equal to an input value.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
double *fltvalA(size_t size, double value)
```

### Array of values in range
Generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step',
at the location of the input pointer.
It returns the pointer on success,
and NULL otherwise.
```c
double *fltrange(double *a, size_t size, double start, double step)
```

### Array of values in range (allocated)
Allocate and generate an array of integers equal to 
a range of input values, specified by a
starting value 'start' and a step size 'step'.
It returns a pointer to the allocated array.
Note that it must be freed after its use.
```c
double *fltrangeA(size_t size, double start, double step)
```

### Print integer array
Prints a 1D array of integers 
to stdout horizontally, 
with values separated by single spaces.
```c
void intprint(const double *a, size_t size)
```

### Concatenate two arrays
Concatenates two arrays of integers
into an input array 'dest'.
On fail, it returns a NULL pointer.
```c
double *fltcat(double *dest, const double *a, size_t as, const double *b, size_t bs)
```

### Concatenate two arrays (allocated)
Concatenates two arrays of integers
into an allocated array 'dest',
and a pointer to it is returned.
Note that it must be freed after its use.
```c
double *fltcatA(const double *a, size_t as, const double *b, size_t bs)
```

### Copy an array
Copies the values of an array into another,
and returns a pointer ot it.
On fail, it returns a NULL pointer.
```c
double *fltcpy(double *dest, const double *src, size_t s)
```

### Copy an array (allocated)
Copies the values of an array into another
allocated array, and a pointer to it is returned.
Note that it must be freed after its use.

```c
double *fltcpyA(const double *src, size_t s)
```

### Reverse an array
Reverses the values of an input array
and saves them at the same location.
It returns a pointer to the input array.
On fail, it returns the NULL pointer.
```c
double *fltrev(double *arr, size_t s)
```

### Find maximum
Finds the maximum value in an array,
and returns the value.
```c
double fltmax(const double *arr, size_t len)
```

### Find index of maximum
Finds the maximum value in an array,
and returns its index in the array.
```c
size_t fltimax(const double *arr, size_t len)
```

### Find minimum
Finds the minimum value in an array,
and returns the value.
```c
double fltmin(const double *arr, size_t len)
```

### Find index of minimum
Finds the minimum value in an array,
and returns its index in the array.
```c
size_t fltimin(const double *arr, size_t len)
```

### Sum array members
Sums array members and returns the result.
```c
size_t fltsum(const double *arr, size_t len)
```

### Make array members positive
Changes the sign of all array members to positive.
```c
double *fltpos(double *arr, size_t len)
```

### Make array members negative
Changes the sign of all array members to negative.
```c
double *fltneg(double *arr, size_t len)
```

### Switch sign of array
Switches the sign of array members to positive if it
was negative, and viceversa.
```c
double *fltsign(double *arr, size_t len)
```

### Roll array elements
Moves the position of all array members
an input number of steps forward (positive offset)
of backward (negative offset).
```c
double *fltroll(double *arr, size_t len, int offset)
```

### Delete array element
Removes element of given index from array,
and returns a pointer to it.
Note that memory of array is not reduced.
```c
double *fltdel(double *arr, size_t len, size_t index)
```

### Insert array element
Inserts a given value 'val' at the specified index 'ind' of an array 'arr' of given length 'len'. The resulting array is stored in an array 'dest' of size 'len+1' and a pointer to it is returned.
```c
double *fltins(double *dest, const double *arr, size_t len, size_t index, double val)
```

### Insert array element (allocated)
Inserts a given value 'val' at the specified index 'ind' of an array 'arr' of given length 'len'. 
The result is allocated into an array of size 'len+1' and a pointer to it is returned. Note: the return array must be freed after its use.
```c
double *fltinsA(const double *arr, size_t len, size_t ind, double val)
```

### Add two arrays
Adds the elements of two arrays 'dest' and 'arr' of equal length together, stores the results in the memory of array 'dest' and returns a pointer to it.
```c
double *fltadd(double *dest, const double *arr, size_t len)
```

### Subtract two arrays
Subtracts the elements of two arrays 'dest' and 'arr' of equal length from one another, stores the results in the memory of array 'dest' and returns a pointer to it.
```c
double *fltsub(double *dest, const double *arr, size_t len)
```

### Multiply two arrays
Multiplies the elements of two arrays 'dest' and 'arr' of equal length to one another, stores the results in the memory of array 'dest' and returns a pointer to it.
```c
double *fltmult(double *dest, const double *arr, size_t len)
```

### Apply function to array members
Applies an input function 'func' to the elements of an array 'arr' of length 'len'. The results are saved over the values of 'arr', and a pointer to it is returned. The input function must have a single argument, of type double, and return have double return type too.
```c
double *fltfunc(double (*func)(), double *arr, size_t len)
```

### Compare two arrays
Compares two arrays 'a' and 'b' and returns a value that is zero only if the arrays are equal element-wise.
```c
double fltcmp(const double *a, const double *b, size_t len)
```

### Add scalar to array
Adds a value 'val' to the elements in an array 'arr'.
```c
double *fltsadd(double *arr, size_t len, double val)
```

### Multiply array by scalar
Multiplies each array element by a given value 'val'.
```c
double *fltsmult(double *arr, size_t len, double val)
```

### Inverse of array elements
Calculates the inverse value 1/x of elements in array 'arr'.
```c
double *fltinv(double *arr, size_t len)
```

### Dot product of two arrays.
Performs dot product between two arrays 'a' and 'b' and returns the value.
```c
double fltdot(const double *a, const double *b, size_t len)
```

### Exp of array elements
```c
double *fltexp(double *arr, size_t len)
```

### Square root of array elements
```c
double *fltsqrt(double *arr, size_t len)
```

### Sine of array elements
```c
double *fltsin(double *arr, size_t len)
```

### Cosine of array elements
```c
double *fltcos(double *arr, size_t len)
```

### Natural log of array elements
```c
double *fltlog(double *arr, size_t len)
```

### Log 10 of array elements
```c
double *fltlog10(double *arr, size_t len)
```

### Magnitude of array
The magnitude of an array 'arr' of lenght 'len' is calculated as if it was a vector: the square root of the sum of the elements squared. The result is returned.
```c
double fltmag(const double *arr, size_t len)
```

### Seek value in array of doubles
It seeks an input value 'val' an input array of doubles 'arr' of length 'len'. It writes the result into an input integer array 'dest' of same length and returns a pointer to it. If an array element is that value, a '1' is written in 'dest', otherwise a '0' is written.

```c
int *fltisval(int *dest, const double *arr, size_t len, double val)
```

### Seek NaN values in array of doubles
It seeks NAN values an input array of doubles 'arr' of length 'len'. It writes the result into an input integer array 'dest' of same length and returns a pointer to it. If an array element is NAN, a '1' is written in 'dest', whereas for non-NAN values, a '0' is written.
```c
int *fltisnan(int *dest, const double *arr, size_t len)
```


## 1D Array Data Type Conversion

### Array of integers into doubles
Casts an array of integers 'arr' into doubles values, saves the result in the memory of input array 'dest' and returns a pointer to it.
```c
double *inttoflt(double *dest, const int *arr, size_t len)
```

### Array of integers into doubles (allocated)
Casts an array of integers 'arr' into double values, allocates the new array, and returns a pointer to it.
```c
double *inttofltA(const int *arr, size_t len)
```

### Array of doubles into integers
Casts an array of doubles 'arr' into integer values, saves the result in the memory of input array 'dest' and returns a pointer to it.
```c
int *flttoint(int *dest, const double *arr, size_t len)
```

### Array of doubles into integers (allocated)
Casts an array of doubles 'arr' into integer values, allocates the new array, and returns a pointer to it.
```c
int *flttointA(const double *arr, size_t len)
```


## Input / Output

### Input string
Prompts the user to input a string using an input message 'msg'. The result is stored in the location of 'dest' and a pointer is returned to it. On fail, it returns NULL.
```c
char *getstr(char *dest, const char *msg)
```

### String to integer
Converts an input string 'str' into an integer, stores the result in the location of 'dest' and returns the pointer. On fail, it returns NULL.
```c
int *strtoint(int *dest, const char *str)
```

### String to double
Converts an input string 'str' into a double, stores the result in the location of 'dest' and returns the pointer. On fail, it returns NULL.
```c
double *strtoflt(double *dest, const char *str)
```

### Count tokens in string
Given a string 'str' and a delimiter 'delim', it returns the number of tokens in the string.
```c
size_t strtokn(char *str, const char *delim)
```
For example, for a string "aa;bb;cc" and a delimiter ";", this function returns '3', since there are three tokens in the string ('aa', 'bb', 'cc'). On fail, it returns zero.

### Partition string
Given an input pointer to a string 'ptr' and a delimiter 'delim', it searches for the first instance of the delimiter, subtitutes it with the terminator character '\0', and returns a pointer to the subsequent location (ptr+1). 
```c
char *strpar(char *ptr, const char *delim)
```

### Split string
Given a string 'str' and a delimiter 'delim', it splits the string at the delimiters, stores the pointers to the tokens in 'dest', and returns a pointer to it. On fail, it returns NULL.
```c
char **strsplit(char **dest, char *str, const char delim)
```

### Count lines in a file
Counts the lines in a text file located at the path 'path', and returns the value. The counting process discards empty lines and comment lines, defined by an input starting character 'comment'.
```c
size_t
CountTxtLines(size_t maxRead, const char *path, const char *comment)
```

### Read lines in a file

Reads the lines in a file, skipping the empty ones and the comments, as defined by a comment character 'comment'. The lines are stored as strings at the input array of strings '\*\*lines' and a pointer to it is returned. The maximum memory in which to copy read lines is defined by 'maxRead'. On fail, a NULL pointer is returned.
```c
char **ReadTxtLines(char **lines, size_t maxRead, const char *path, const char *comment)
```

### Load data from file

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



## *WIP*.
* SaveToTxt
* Array of integers into strings
* Array of doubles into strings

* Sort array in ascending/descending order (use qsort).
* Sort and return array of indices (argsort).
 
