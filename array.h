
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

v0.3 - 01/08/2021
	- Migrated typing to types.h.
		ARRAY_INT => TYPE_INT
		ARRAY_DOUBLE => TYPE_DOUBLE
	- Changed all unsigned longs to unsigned ints.
	- Added length() function to obtain length of array.
	- Added checks for math errors:
		array->has_nan()
		array->has_inf()
		array->has_matherr()


	--> defs.h Added checks for NAN, INF, and -INF:
		ulib_nan()
		ulib_pinf()
		ulib_ninf()
		ulib_isnan(n)
		ulib_isinf()
		ulib_ispinf()
		ulib_isninf()

	--> Dropped support for ints. Array only works with doubles.

v0.1 - 18/03/2021
	- Basics: array_new() and free()
	- Value generators: fill(), range(), linspace(), from_c_array()
	- Printing: print()
	- Debug: array__debug();
	- Types supported: int and double.
	- Get values (geti, getf) or a pointer (at).
	- Set values (seti, setf)

Planned
	- Drop support for ints. Make it exclusive for doubles.

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
#ifndef ARRAY_H
#define ARRAY_H

#ifndef TYPE_IMPLEMENTATION
#define TYPE_IMPLEMENTATION
#include "types.h"
#endif


/*
 *	DATA STRUCTURES & MACROS
 */

typedef struct array__struct array;
struct array__struct {
	char* data;
	unsigned int size;
	unsigned int type;
	unsigned int bytes; /* size in bytes of each member */

	/* Function pointers */
	unsigned int (*length)(array*);
	void (*free)(array*);
	void (*print)(array*);

	void (*fill)(array*, ...);
	void (*range)(array*, ...);
	void (*linspace)(array*, ...);
	void (*from_c_array)(array*, const void* c_arr);
	void (*reverse)(array*);

	void (*seti)(array*, unsigned int ind, int value);
	void (*setf)(array*, unsigned int ind, double value);

	int (*geti)(array*, unsigned int ind);
	double (*getf)(array*, unsigned int ind);
	char* (*at)(array*, unsigned int ind);

	/* stats */
	int (*maxi)(array*);
	double (*maxf)(array*);
	int (*mini)(array*);
	double (*minf)(array*);
	unsigned int (*imax)(array*);
	unsigned int (*imin)(array*);
	int (*sumi)(array*);
	double (*sumf)(array*);
	double (*mean)(array*);	
};


/*
 *	FUNCTION DECLARATIONS
 */

unsigned int array__type_bytes(unsigned int type);

array* array_new(unsigned int size, unsigned int type);
unsigned int array__length(array* arr);
void array__free(array* arr);
void array__debug(array* arr);
void array__from_c_array(array* arr, const void* c_arr);   

int     array__getval_int(array* arr, unsigned int ind);
double  array__getval_db(array* arr, unsigned int ind);
char*   array__getptr(array* arr, unsigned int ind);
void    array__setval_int(array* arr, unsigned int ind, int value);
void    array__setval_db(array* arr, unsigned int ind, double value);

void array__print_int(array* arr);
void array__print_double(array* arr);
void array__print(array* arr);

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

unsigned int array__imax_int(array* arr);
unsigned int array__imax_db(array* arr);
unsigned int array__imax(array* arr);

unsigned int array__imin_int(array* arr);
unsigned int array__imin_db(array* arr);
unsigned int array__imin(array* arr);

int array__sum_int(array* arr);
double array__sum_db(array* arr);
double array__mean_int(array* arr);
double array__mean_db(array* arr);
double array__mean(array* arr);

int array__has_nan(array* arr);
int array__has_matherr(array* arr);

/* No need to know type, just copy chunks of bytes around */
void array__reverse(array* arr);


#endif /* array.h */



/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		IMPLEMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef ARRAY_IMPLEMENTATION


array* array_new(unsigned int size, unsigned int type){
	unsigned int bytes;
	array* arr;

	/* Supported types */
	if (type != TYPE_INT && type != TYPE_DOUBLE){
		return NULL;
	}

	bytes = array__type_bytes(type);
	arr = ULIB_MALLOC(sizeof(array));
	if(!arr) return NULL;

	arr->size = size;
	arr->type = type;
	arr->bytes = bytes;
	arr->data = calloc(size, bytes);
	if(!arr->data) return NULL;
	
	/* Function pointers */
	arr->length = array__length;
	arr->free = array__free;
	arr->fill = array__fill;
	arr->print = array__print;
	arr->range = array__fill_range;
	arr->linspace = array__fill_linspace;
	arr->geti = array__getval_int;
	arr->getf = array__getval_db;
	arr->at = array__getptr;
	arr->seti = array__setval_int;
	arr->setf = array__setval_db;
	arr->from_c_array = array__from_c_array;

	arr->maxi = array__max_int;
	arr->maxf = array__max_db;
	arr->imax = array__imax;

	arr->mini = array__min_int;
	arr->minf = array__min_db;
	arr->imin = array__imin;

	arr->sumi = array__sum_int;
	arr->sumf = array__sum_db;

	arr->mean = array__mean;
	arr->reverse = array__reverse;

	return arr;
}

unsigned int array__type_bytes(unsigned int type){
	switch(type){
		case TYPE_INT: default:
			return sizeof(int);
		case TYPE_DOUBLE:
			return sizeof(double);
	}
}

unsigned int array__length(array* arr){
	return arr->size;
}

void array__free(array* arr){
	ULIB_FREE(arr->data);
	ULIB_FREE(arr);
}

void array__debug(array* arr){
	ULIB_PRINTF("new array at 0x%p\n", arr);
	ULIB_PRINTF(" -mem: %d bytes\n", (int)(arr->size*arr->bytes+sizeof(array)));
	ULIB_PRINTF(" -size: %d elements\n", (int)arr->size);
	ULIB_PRINTF(" -type: %d\n", (int)arr->type);
	ULIB_PRINTF(" -element bytes: %d\n", (int)arr->bytes);
	ULIB_PRINTF(" -data: 0x%p to 0x%p\n", &arr->data[0], &arr->data[0]+arr->bytes*(arr->size+1)-1);
}

int array__getval_int(array* arr, unsigned int ind){
	return *(int*)(&arr->data[0] + arr->bytes*ind);
}

double array__getval_db(array* arr, unsigned int ind){
	return *(double*)(&arr->data[0] + arr->bytes*ind);
}

char* array__getptr(array* arr, unsigned int ind){
	return (char*)(&arr->data[0] + arr->bytes*ind);
}

void array__setval_int(array* arr, unsigned int ind, int value){
	*(int*)(arr->data + arr->bytes*ind) = value;
}

void array__setval_db(array* arr, unsigned int ind, double value){
	*(double*)(arr->data + arr->bytes*ind) = value;
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__print_int(array* arr){
	unsigned int i;
	ULIB_PRINTF("[");
	for(i=0; i!=arr->size; ++i){
		ULIB_PRINTF(" %d", array__getval_int(arr,i));
	}
	ULIB_PRINTF(" ]");
	ULIB_PRINTF("\n");
}

void array__print_double(array* arr){
	unsigned int i;
	ULIB_PRINTF("[");
	for(i=0; i!=arr->size; ++i){
		ULIB_PRINTF(" %g", array__getval_db(arr,i));
	}
	ULIB_PRINTF(" ]");
	ULIB_PRINTF("\n");
}

void array__print(array* arr){
	switch(arr->type){
		case TYPE_INT:
			array__print_int(arr);
			break;
		case TYPE_DOUBLE:
			array__print_double(arr);
			break;
	}
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__fill_int(array* arr, int value){
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		int* ptr = (int*)(arr->data + i*arr->bytes);
		*ptr = value;
	}
}

void array__fill_db(array* arr, double value){
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		double* ptr = (double*)(arr->data + i*arr->bytes);
		*ptr = value;
	}
}

void array__fill(array* arr, ...){
	ULIB_VA_LIST args;
	ULIB_VA_START(args,arr);
	
	switch(arr->type){
		case TYPE_INT:
			array__fill_int(arr, ULIB_VA_ARG(args,int));
			break;
		case TYPE_DOUBLE:
			array__fill_db(arr, ULIB_VA_ARG(args,double));
			break;
	}
    ULIB_VA_END(args); 
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__fill_range_int(array* arr, int start, int end){
	unsigned int i;
	int extra;
	double step = (double)(end - start)/(double)arr->size;
	for(i=0; i!=arr->size; ++i){
		extra = start + (int)(step*(double)i);
		*(int*)(arr->data + i*arr->bytes) = extra;
	}
}

void array__fill_range_db(array* arr, double start, double end){
	unsigned int i;
	double val = start;
	double step = (end - start)/(double)arr->size;
	for(i=0; i!=arr->size; ++i){
		*(double*)(arr->data + i*arr->bytes) = val;
		val += step;
	}
}

void array__fill_range(array* arr, ...){
	ULIB_VA_LIST args;
	ULIB_VA_START(args,arr);
	switch(arr->type){
		case TYPE_INT:
			array__fill_range_int(arr, ULIB_VA_ARG(args,int), ULIB_VA_ARG(args,int));
			break;
		case TYPE_DOUBLE:
			array__fill_range_db(arr, ULIB_VA_ARG(args,double), ULIB_VA_ARG(args,double));
			break;
	}
    ULIB_VA_END(args);
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__fill_linspace_int(array* arr, int start, int step){
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		arr->seti(arr, i, start);
		start += step;
	}
}

void array__fill_linspace_db(array* arr, double start, double step){
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		arr->setf(arr, i, start);
		start += step;
	}
}

void array__fill_linspace(array* arr, ...){
	int start_i, step_i;
	double start_db, step_db;
	ULIB_VA_LIST args;

	ULIB_VA_START(args, arr);
	switch(arr->type){
		case TYPE_INT:
			start_i = ULIB_VA_ARG(args,int);
			step_i = ULIB_VA_ARG(args,int);
			array__fill_linspace_int(arr, start_i, step_i);
			break;
		case TYPE_DOUBLE:
			start_db = ULIB_VA_ARG(args,double);
			step_db = ULIB_VA_ARG(args,double);
			array__fill_linspace_db(arr, start_db, step_db);
			break;
	}
    ULIB_VA_END(args);
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void array__from_c_array(array* arr, const void* c_arr){
	ULIB_MEMCPY(arr->data, c_arr, arr->bytes*arr->size);
}

/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

int array__max_int(array* arr){
	int max = arr->geti(arr,0);
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		if(max < arr->geti(arr,i)) max = arr->geti(arr,i);
	}
	return max;
}

double array__max_db(array* arr){
	double max = arr->getf(arr,0);
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		if(max < arr->getf(arr,i)) max = arr->getf(arr,i);
	}
	return max;
}

int array__min_int(array* arr){
	int min = arr->geti(arr,0);
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		if(min > arr->geti(arr,i)) min = arr->geti(arr,i);
	}
	return min;
}

double array__min_db(array* arr){
	double min = arr->getf(arr,0);
	unsigned int i;
	for(i=0; i!=arr->size; ++i){
		if(min > arr->getf(arr,i)) min = arr->getf(arr,i);
	}
	return min;
}

unsigned int array__imax_int(array* arr){
	unsigned int i, j = 0;
	int max = arr->geti(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(max < arr->geti(arr,i)){
			max = arr->geti(arr,i);
			j = i;
		}
	}
	return j;
}

unsigned int array__imax_db(array* arr){
	unsigned int i, j = 0;
	double max = arr->getf(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(max < arr->getf(arr,i)){
			max = arr->getf(arr,i);
			j = i;
		}
	}
	return j;
}

unsigned int array__imax(array* arr){
	switch(arr->type){
		case TYPE_INT: default:
			return array__imax_int(arr);
		case TYPE_DOUBLE:
			return array__imax_db(arr);
	}
}


unsigned int array__imin_int(array* arr){
	unsigned int i, j = 0;
	int min = arr->geti(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(min > arr->geti(arr,i)){
			min = arr->geti(arr,i);
			j = i;
		}
	}
	return j;
}

unsigned int array__imin_db(array* arr){
	unsigned int i, j = 0;
	double min = arr->getf(arr,0);
	for(i=0; i!=arr->size; ++i){
		if(min > arr->getf(arr,i)){
			min = arr->getf(arr,i);
			j = i;
		}
	}
	return j;
}

unsigned int array__imin(array* arr){
	switch(arr->type){
		case TYPE_INT: default:
			return array__imin_int(arr);
		case TYPE_DOUBLE:
			return array__imin_db(arr);
	}
}

int array__sum_int(array* arr){
	int sum = 0;
	unsigned int i;
	for(i=0; i!=arr->size; ++i) sum += arr->geti(arr,i);
	return sum;
}

double array__sum_db(array* arr){
	double sum = 0;
	unsigned int i;
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
		case TYPE_INT: default:
			return array__mean_int(arr);
		case TYPE_DOUBLE:
			return array__mean_db(arr);
	}
}

int array__has_nan(array* arr){
	if (arr->type == TYPE_INT) return 0;
	unsigned int i, cnt = 0;
	for(i=0; i!=arr->length(arr); ++i){
		if( ULIB_ISNAN(arr->getf(arr,i)) ){
			cnt++;
		}
	}
	return cnt;
}

int array__has_matherr(array* arr){
	if (arr->type == TYPE_INT) return 0;
	unsigned int i, cnt = 0;
	for(i=0; i!=arr->length(arr); ++i){
		if( ULIB_ISNAN(arr->getf(arr,i)) || ULIB_ISINF(arr->getf(arr,i)) ){
			cnt++;
		}
	}
	return cnt;
}

void array__reverse(array* arr){
	ULIB_PRINTF("WIP array->reverse (%u)\n", (unsigned int)arr->size);
}


/* 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/


#endif /* ARRAY_IMPLEMENTATION */


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

