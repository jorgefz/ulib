
/*

--- array.h ---

Header-only library that adds the array data structure,
a list of numbers of immutable length, on which
a number of operations can be performed.

In order to use the functions from this library, write:
	#define ARRAY_IMPLEMENTATION
and THEN include the library:
	#include "array.h"

Currently, it only supports arrays of ints and doubles.

Standard: ANSI C89
Compiler: GCC version 9.2.0 (tdm64-1)


VERSIONS

v0.1 - 18/03/2021
	- Basics: array_new() and free()
	- Value generators: fill(), range(), linspace(), from_c_array()
	- Printing: print()
	- Debug: array__debug();
	- Types supported: int and double.
	- Get values (geti, getf) or a pointer (at).
	- Set values (seti, setf)

v0.2 - 19/03/2021
	- Rewritten in ANSI C89
	- Renamed functions to avoid reserved double underscore
	- Fixed bug with linespace function
	- Added functions for max and min (and their indices)
	- Added functions for element-wise sum and the mean.

Planned
	- Generic: reverse
	- Stats: median, stdev, etc
	- Operations: add, sub, mult, div, mod
	- Sorting: selection, bubble, etc.


*/


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		HEADER
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

/*
 *	DATA STRUCTURES & MACROS
 */
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

struct __attribute__((__packed__)) array__struct {
	char* data;
	ulong size;
	uint type;
	ulong bytes; /* size in bytes of each member */

	/* Function pointers */
	void (*free)(struct array__struct*);
	void (*print)(struct array__struct*);

	void (*fill)(struct array__struct*, ...);
	void (*range)(struct array__struct*, ...);
	void (*linspace)(struct array__struct*, ...);
	void (*from_c_array)(struct array__struct*, const void* c_arr);

	void (*seti)(struct array__struct*, ulong ind, int value);
	void (*setf)(struct array__struct*, ulong ind, double value);

	int (*geti)(struct array__struct*, ulong ind);
	double (*getf)(struct array__struct*, ulong ind);
	char* (*at)(struct array__struct*, ulong ind);

	/* stats */
	int (*maxi)(struct array__struct*);
	double (*maxf)(struct array__struct*);
	int (*mini)(struct array__struct*);
	double (*minf)(struct array__struct*);
	uint (*imax)(struct array__struct*);
	uint (*imin)(struct array__struct*);
	int (*sumi)(struct array__struct*);
	double (*sumf)(struct array__struct*);
	double (*mean)(struct array__struct*);

	void (*reverse)(struct array__struct*);

};
typedef struct array__struct array;

enum array__types {
	INT, DOUBLE
}; /* Supported types */


/*
 *	FUNCTION DECLARATIONS
 */

ulong array__type_bytes(uint type);

array* array_new(ulong size, uint type);
void array__free(array* arr);
void array__debug(array* arr);
void array__from_c_array(array* arr, const void* c_arr);   

int     array__getval_int(array* arr, ulong ind);
double  array__getval_db(array* arr, ulong ind);
char*   array__getptr(array* arr, ulong ind);
void    array__setval_int(array* arr, ulong ind, int value);
void    array__setval_db(array* arr, ulong ind, double value);

void array__print_int(array* arr);
void array__print_double(array* arr);
void array__print(array* arr);
/*
-->mixed white & asian, other background
*/

void array__fill_int(array* arr, int value);
void array__fill_db(array* arr, double value);
void array__fill(array* arr, ...);

void array__fill_range_int(array* arr, int start, int end);
void array__fill_range_db(array* arr, double start, double end);
void array__fill_range(array* arr, ...);

void array__fill_linspace_int(array* arr, int start, int step);
void array__fill_linspace_db(array* arr, double start, double step);
void array__fill_linspace(array* arr, ...);

/* Stats */
int array__max_int(array* arr);
double array__max_db(array* arr);
int array__min_int(array* arr);
double array__min_db(array* arr);

uint array__imax_int(array* arr);
uint array__imax_db(array* arr);
uint array__imax(array* arr);

uint array__imin_int(array* arr);
uint array__imin_db(array* arr);
uint array__imin(array* arr);

int array__sum_int(array* arr);
double array__sum_db(array* arr);
double array__mean_int(array* arr);
double array__mean_db(array* arr);
double array__mean(array* arr);

/* No need to know type, just copy chunks of bytes around */
void array__reverse(array* arr);


#endif /* array.h */



/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		IMPLEMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef ARRAY_IMPLEMENTATION


array* array_new(ulong size, uint type){
	ulong bytes;
	array* arr;

	bytes = array__type_bytes(type);
	arr = malloc(sizeof(array));
	if(!arr) return NULL;

	arr->size = size;
	arr->type = type;
	arr->bytes = bytes;
	arr->data = calloc(size, bytes);
	if(!arr->data) return NULL;
	
	/* Function pointers */
	arr->free = &array__free;
	arr->fill = &array__fill;
	arr->print = &array__print;
	arr->range = &array__fill_range;
	arr->linspace = &array__fill_linspace;
	arr->geti = &array__getval_int;
	arr->getf = &array__getval_db;
	arr->at = &array__getptr;
	arr->seti = &array__setval_int;
	arr->setf = &array__setval_db;
	arr->from_c_array = &array__from_c_array;

	arr->maxi = &array__max_int;
	arr->maxf = &array__max_db;
	arr->imax = &array__imax;

	arr->mini = &array__min_int;
	arr->minf = &array__min_db;
	arr->imin = &array__imin;

	arr->sumi = &array__sum_int;
	arr->sumf = &array__sum_db;

	arr->mean = &array__mean;
	arr->reverse = &array__reverse;

	return arr;
}

ulong array__type_bytes(uint type){
	switch(type){
		case INT: default:
			return sizeof(int);
		case DOUBLE:
			return sizeof(double);
	}
}

void array__free(array* arr){
	free(arr->data);
	free(arr);
}

void array__debug(array* arr){
	printf("new array at 0x%p\n", arr);
	printf(" -mem: %d bytes\n", (int)(arr->size*arr->bytes+sizeof(array)));
	printf(" -size: %d elements\n", (int)arr->size);
	printf(" -type: %d\n", (int)arr->type);
	printf(" -element bytes: %d\n", (int)arr->bytes);
	printf(" -data: 0x%p to 0x%p\n", &arr->data[0], &arr->data[0]+arr->bytes*(arr->size+1)-1);
}

int array__getval_int(array* arr, ulong ind){
	return *(int*)(&arr->data[0] + arr->bytes*ind);
}

double array__getval_db(array* arr, ulong ind){
	return *(double*)(&arr->data[0] + arr->bytes*ind);
}

char* array__getptr(array* arr, ulong ind){
	return (char*)(&arr->data[0] + arr->bytes*ind);
}

void array__setval_int(array* arr, ulong ind, int value){
	*(int*)(arr->data + arr->bytes*ind) = value;
}

void array__setval_db(array* arr, ulong ind, double value){
	*(double*)(arr->data + arr->bytes*ind) = value;
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__print_int(array* arr){
	uint i;
	printf("[");
	for(i=0; i!=arr->size; ++i){
		printf(" %d", array__getval_int(arr,i));
	}
	printf(" ]");
	printf("\n");
}

void array__print_double(array* arr){
	uint i;
	printf("[");
	for(i=0; i!=arr->size; ++i){
		printf(" %g", array__getval_db(arr,i));
	}
	printf(" ]");
	printf("\n");
}

void array__print(array* arr){
	switch(arr->type){
		case INT:
			array__print_int(arr);
			break;
		case DOUBLE:
			array__print_double(arr);
			break;
	}
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__fill_int(array* arr, int value){
	uint i;
	for(i=0; i!=arr->size; ++i){
		int* ptr = (int*)(arr->data + i*arr->bytes);
		*ptr = value;
	}
}

void array__fill_db(array* arr, double value){
	uint i;
	for(i=0; i!=arr->size; ++i){
		double* ptr = (double*)(arr->data + i*arr->bytes);
		*ptr = value;
	}
}

void array__fill(array* arr, ...){
	va_list args;
	va_start(args,arr);
	
	switch(arr->type){
		case INT:
			array__fill_int(arr, va_arg(args,int));
			break;
		case DOUBLE:
			array__fill_db(arr, va_arg(args,double));
			break;
	}
    va_end(args); 
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__fill_range_int(array* arr, int start, int end){
	uint i;
	int extra;
	double step = (double)(end - start)/(double)arr->size;
	for(i=0; i!=arr->size; ++i){
		extra = start + (int)(step*(double)i);
		*(int*)(arr->data + i*arr->bytes) = extra;
	}
}

void array__fill_range_db(array* arr, double start, double end){
	uint i;
	double val = start;
	double step = (end - start)/(double)arr->size;
	for(i=0; i!=arr->size; ++i){
		*(double*)(arr->data + i*arr->bytes) = val;
		val += step;
	}
}

void array__fill_range(array* arr, ...){
	va_list args;
	va_start(args,arr);
	switch(arr->type){
		case INT:
			array__fill_range_int(arr, va_arg(args,int), va_arg(args,int));
			break;
		case DOUBLE:
			array__fill_range_db(arr, va_arg(args,double), va_arg(args,double));
			break;
	}
    va_end(args);
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__fill_linspace_int(array* arr, int start, int step){
	printf("LINSPACE_INT: %d, %d\n", start, step);
	uint i;
	for(i=0; i!=arr->size; ++i){
		arr->seti(arr, i, start);
		start += step;
	}
}

void array__fill_linspace_db(array* arr, double start, double step){
	uint i;
	for(i=0; i!=arr->size; ++i){
		arr->setf(arr, i, start);
		start += step;
	}
}

void array__fill_linspace(array* arr, ...){
	int start_i, step_i;
	double start_db, step_db;
	va_list args;

	va_start(args, arr);
	switch(arr->type){
		case INT:
			start_i = va_arg(args,int);
			step_i = va_arg(args,int);
			array__fill_linspace_int(arr, start_i, step_i);
			break;
		case DOUBLE:
			start_db = va_arg(args,double);
			step_db = va_arg(args,double);
			array__fill_linspace_db(arr, start_db, step_db);
			break;
	}
    va_end(args);
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__from_c_array(array* arr, const void* c_arr){
	memcpy(arr->data, c_arr, arr->bytes*arr->size);
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

int array__max_int(array* arr){
	int max = arr->geti(arr,0);
	uint i;
	for(i=0; i!=arr->size; ++i){
		if(max < arr->geti(arr,i)) max = arr->geti(arr,i);
	}
	return max;
}

double array__max_db(array* arr){
	double max = arr->getf(arr,0);
	uint i;
	for(i=0; i!=arr->size; ++i){
		if(max < arr->getf(arr,i)) max = arr->getf(arr,i);
	}
	return max;
}

int array__min_int(array* arr){
	int min = arr->geti(arr,0);
	uint i;
	for(i=0; i!=arr->size; ++i){
		if(min > arr->geti(arr,i)) min = arr->geti(arr,i);
	}
	return min;
}

double array__min_db(array* arr){
	double min = arr->getf(arr,0);
	uint i;
	for(i=0; i!=arr->size; ++i){
		if(min > arr->getf(arr,i)) min = arr->getf(arr,i);
	}
	return min;
}

uint array__imax_int(array* arr){
	uint i, j = 0;
	int max = arr->geti(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(max < arr->geti(arr,i)){
			max = arr->geti(arr,i);
			j = i;
		}
	}
	return j;
}

uint array__imax_db(array* arr){
	uint i, j = 0;
	double max = arr->getf(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(max < arr->getf(arr,i)){
			max = arr->getf(arr,i);
			j = i;
		}
	}
	return j;
}

uint array__imax(array* arr){
	switch(arr->type){
		case INT: default:
			return array__imax_int(arr);
		case DOUBLE:
			return array__imax_db(arr);
	}
}


uint array__imin_int(array* arr){
	uint i, j = 0;
	int min = arr->geti(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(min > arr->geti(arr,i)){
			min = arr->geti(arr,i);
			j = i;
		}
	}
	return j;
}

uint array__imin_db(array* arr){
	uint i, j = 0;
	double min = arr->getf(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(min > arr->getf(arr,i)){
			min = arr->getf(arr,i);
			j = i;
		}
	}
	return j;
}

uint array__imin(array* arr){
	switch(arr->type){
		case INT: default:
			return array__imin_int(arr);
		case DOUBLE:
			return array__imin_db(arr);
	}
}

int array__sum_int(array* arr){
	int sum = 0;
	uint i;
	for(i=0; i!=arr->size; ++i) sum += arr->geti(arr,i);
	return sum;
}

double array__sum_db(array* arr){
	double sum = 0;
	uint i;
	for(i=0; i!=arr->size; ++i) sum += arr->getf(arr,i);
	return sum;
}

double array__mean_int(array* arr){
	return (double)arr->sumi(arr)/(double)arr->size;
}

double array__mean_db(array* arr){
	return arr->sumf(arr)/(double)arr->size;
}

double array__mean(array* arr){
	switch(arr->type){
		case INT: default:
			return array__mean_int(arr);
		case DOUBLE:
			return array__mean_db(arr);
	}
}

void array__reverse(array* arr){
	printf("WIP array->reverse (%u)\n", (uint)arr->size);
}


/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/


#endif /* ARRAY_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif


/*

// Checks that a list is sorted
int* sorted(int* data, int size){
	for(int i=1; i!=size; ++i){
		if(data[i] > data[i-1]) return NULL; //Assumes maximum is first element
	}
	return data;
}


// Sorting algorithms
int* selsort(int *data, int size){
	int c, i, maxi, swap;
	c = 0;
	while(c < size){
		maxi = c;
		for(i=c; i<size; ++i){
			if(data[maxi] < data[i]){
				maxi = i;
			}
		}
		swap = data[c];
		data[c] = data[maxi];
		data[maxi] = swap;
		c++;
	}
	return data;
}

int* bubblesort(int *data, int size){
	int i, swap;
	while(!sorted(data, size)){
		for(i=1; i!=size; ++i){
			if(data[i-1] >= data[i]) continue;
			swap = data[i-1];
			data[i-1] = data[i];
			data[i] = swap;
		}
	}
	return data;
}

//int* quick_sort();

//int* merge_sort();

*/

