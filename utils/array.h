
/*

--- array.h ---

Header-only library that adds the array data structure,
a list of numbers of immutable length, on which
a number of operations can be performed.

Currently, it only supports arrays of ints and doubles.

Standard: C99
Compiler: GCC


VERSIONS

v0.1
	- Basic creation, freeing: array_new and array->free()
	- Value initialziation: fill() and range()
	- Printing: print()
	- Debug: __array_debug();
	- Types supported: int and double.


*/



#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>


/*
 *	====================================
 *	DATA STRUCTURES & MACROS
 *	====================================
 */

typedef unsigned int uint;
typedef unsigned char uchar;

struct __attribute__((__packed__)) __array_struct {
	char* data;
	uint64_t size;
	uint8_t type;
	uint64_t bytes; //size in bytes of each member
	//Function pointers here
	void (*free)(struct __array_struct*);
	void (*fill)(struct __array_struct*, ...);
	void (*print)(struct __array_struct*);
	void (*range)(struct __array_struct*, ...);
};
typedef struct __array_struct array;

enum { INT, DOUBLE };



/*
 *	====================================
 *	FUNCTION DECLARATIONS
 *	====================================
 */

static inline uint64_t __type_bytes(uint8_t type);

static inline void __array_free(array* arr);
static inline void __array_debug(array* arr);
static inline int __array_getval_int(array* arr, uint64_t ind);
static inline double __array_getval_db(array* arr, uint64_t ind);
static inline int* __array_getptr_int(array* arr, uint64_t ind);
static inline double* __array_getptr_db(array* arr, uint64_t ind);

static inline void __array_fill_int(array* arr, int value);
static inline void __array_fill_db(array* arr, double value);
static inline void __array_fill(array* arr, ...);

static inline void __array_print_int(array* arr);
static inline void __array_print_double(array* arr);
static inline void __array_print(array* arr);

static inline void __array_fill_range_int(array* arr, int start, int end);
static inline void __array_fill_range_db(array* arr, double start, double end);
static inline void __array_fill_range(array* arr, ...);

static inline array* array_new(uint64_t size, uint8_t type);




/*
 *	====================================
 *	FUNCTION DEFINITIONS
 *	====================================
 */

uint64_t __type_bytes(uint8_t type){
	switch(type){
		case INT: default:
			return sizeof(int);
		case DOUBLE:
			return sizeof(double);
	}
}

void __array_free(array* arr){
	free(arr->data);
	free(arr);
}

void __array_debug(array* arr){
	// Data
	printf("new array at 0x%p\n", arr);
	printf(" -mem: %d bytes\n", (int)(arr->size*arr->bytes+sizeof(array)));
	printf(" -size: %d\n", (int)arr->size);
	printf(" -type: %d\n", (int)arr->type);
	printf(" -bytes: %d\n", (int)arr->bytes);
	printf(" -data at 0x%p\n", arr->data);
	//Function pointers
	printf(" -free_func at 0x%p\n", arr->free);
	printf(" -fill_func at 0x%p\n", arr->fill);
	printf(" -print_func at 0x%p\n", arr->print);
	printf(" -range_func at 0x%p\n", arr->range);

}

int __array_getval_int(array* arr, uint64_t ind){
	return *(int*)(arr->data + arr->bytes*ind);
}

double __array_getval_db(array* arr, uint64_t ind){
	return *(double*)(arr->data + arr->bytes*ind);
}

int* __array_getptr_int(array* arr, uint64_t ind){
	return (int*)(arr->data + arr->bytes*ind);
}

double* __array_getptr_db(array* arr, uint64_t ind){
	return (double*)(arr->data + arr->bytes*ind);
}

// ----------------------------------

void __array_print_int(array* arr){
	printf("[");
	for(uint i=0; i!=arr->size; ++i){
		printf(" %d", __array_getval_int(arr,i));
	}
	printf(" ]");
	printf("\n");
}

void __array_print_double(array* arr){
	printf("[");
	for(uint i=0; i!=arr->size; ++i){
		printf(" %g", __array_getval_db(arr,i));
	}
	printf(" ]");
	printf("\n");
}

void __array_print(array* arr){
	switch(arr->type){
		case INT:
			__array_print_int(arr);
			break;
		case DOUBLE:
			__array_print_double(arr);
			break;
	}
}
// ---------------------------------

void __array_fill_int(array* arr, int value){
	for(uint i=0; i!=arr->size; ++i){
		int* ptr = (int*)(arr->data + i*arr->bytes);
		*ptr = value;
	}
}

void __array_fill_db(array* arr, double value){
	for(uint i=0; i!=arr->size; ++i){
		double* ptr = (double*)(arr->data + i*arr->bytes);
		*ptr = value;
	}
}

void __array_fill(array* arr, ...){
	va_list args;
	va_start(args,arr);
	
	switch(arr->type){
		case INT:
			__array_fill_int(arr, va_arg(args,int));
			break;
		case DOUBLE:
			__array_fill_db(arr, va_arg(args,double));
			break;
	}
    va_end(args); 
}
//------------------------------------

void __array_fill_range_int(array* arr, int start, int end){
	double step = (double)(end - start)/(double)arr->size;
	for(uint i=0; i!=arr->size; ++i){
		int extra = start + (int)(step*(double)i);
		*(int*)(arr->data + i*arr->bytes) = extra;
	}
}

void __array_fill_range_db(array* arr, double start, double end){
	double val = start;
	double step = (end - start)/(double)arr->size;
	for(size_t i=0; i!=arr->size; ++i){
		*(double*)(arr->data + i*arr->bytes) = val;
		val += step;
	}
}

void __array_fill_range(array* arr, ...){
	va_list args;
	va_start(args,arr);
	switch(arr->type){
		case INT:
			__array_fill_range_int(arr, va_arg(args,int), va_arg(args,int));
			break;
		case DOUBLE:
			__array_fill_range_db(arr, va_arg(args,double), va_arg(args,double));
			break;
	}
    va_end(args);
}

//void __array_fill_linspace
//void __array_from_c_array()

//------------------------------------


array* array_new(uint64_t size, uint8_t type){
	uint64_t bytes;
	array* arr;

	bytes = __type_bytes(type);
	arr = malloc(sizeof(array));
	if(!arr) return NULL;

	arr->size = size;
	arr->type = type;
	arr->bytes = bytes;
	arr->data = calloc(size, bytes);
	if(!arr->data) return NULL;
	
	//Function pointers
	arr->free = &__array_free;
	arr->fill = &__array_fill;
	arr->print = &__array_print;
	arr->range = &__array_fill_range;

	return arr;
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

