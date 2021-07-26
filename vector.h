

/*
	======= vector.h =======

	This library provides a new object 'vector'
	that behaves as an easily resizeable array
	for any data type and structure.

	To create a new vector, use:
		vector *v = vector_new( sizeof(T) );
	where T is the data type of its members.

	To insert a new member 'var' at index 0, use:
		v->insert( v, 0, &var );

	To retrieve the current vector size, use:
		v->length(v);

	To delete a vector member at index 'i', use:
		v->delete( v, i);

	To retrieve a pointer to a specific member
	at index 'i', use:
		T *ptr = v->at( v, i );

	To free a vector, use:
		v->free(v);

	To resize a vector to a given size, use:
		v->resize(v, size);

	To fill every vector member with the same item, use:
		v->fill(v, &item);




	----- Version History -----

	1.0 - 19/07/2020
		- Added basic vector functions:
		vnew, vfree, v->length, vat,
		vinsert, vdelete.
		- Added functions to aid vector manipulation
		vdtype, vresize, vfill

	1.1 - 25/07/2020
		- Solved bug with vinsert.
		- Added function to retrieve data array
		directly: vdata
		- Addded function to overwrite specific
		vector member: vset

	1.2 - 29/10/2020
		- Added vtovector to convert conventional
			array to vector

	1.3 - 25/07/2021
		- Removed dependency on standard library
		- User can define own implementation of
		memory allocation with ULIB_MALLOC
		and ULIB_REALLOC
		- User can define own implementation of
		memcpy by defining ULIB_MEMCPY
		- Migrated vector functions to struct methods
		(function pointers).


%%%%% TO-DO %%%%%
- Avoid over-usage of getters.

*/


#ifndef VECTOR_H
#define VECTOR_H 1

#include "defs.h"


struct vector__struct {
	struct string__struct* (*substr)(struct string__struct* s, int j, int k);

	void *d;
	unsigned int len;
	unsigned int dtype;
	/* Methods */
	unsigned int (*length)(struct vector__struct*);
	unsigned int (*elem_size)(struct vector__struct*);
	void* (*data)(struct vector__struct*);
	void* (*at)(struct vector__struct*, unsigned int);
	unsigned int (*mem)(struct vector__struct*);
	struct vector__struct* (*set)(struct vector__struct*, unsigned int, void*);
	struct vector__struct* (*fill)(struct vector__struct*, void*);
	struct vector__struct* (*insert)(struct vector__struct*, unsigned int, void*);
	struct vector__struct* (*delete)(struct vector__struct*, unsigned int);
	struct vector__struct* (*resize)(struct vector__struct*, unsigned int);
	struct vector__struct* (*from_array)(void*, unsigned int, unsigned int);
	void (*free)(struct vector__struct*);
};
typedef struct vector__struct vector;

/* Function Declarations */
vector *vector_new(unsigned int bytes);
unsigned int vector__length(vector *v);

unsigned int vector__dtype(vector *v);
void *vector__data(vector *v);
void *vector__at(vector *v, unsigned int i);

unsigned int vector__mem(vector *v);

vector *vector__set(vector *v, unsigned int i, void *src);
vector *vector__fill(vector *v, void *src);

vector *vector__insert(vector *v, unsigned int j, void *new);
vector *vector__delete(vector *v, unsigned int i);
vector *vector__resize(vector *v, unsigned int newsize);
void vector__free(vector *v);
vector *vector__from_array(void *arr, unsigned int elem_num, unsigned int elem_size);

#endif


#ifdef VECTOR_IMPLEMENTATION

/* Allocates new vector and returns pointer to it */
vector *vector_new(unsigned int bytes) {
	vector *v = ULIB_MALLOC(sizeof(vector));
	if(!v) return NULL;
	/* Variables */
	v->d = NULL;
	v->len = 0;
	v->dtype = bytes;
	/* Methods */
	v->length = vector__length;
	v->elem_size = vector__dtype;
	v->data = vector__data;
	v->at = vector__at;
	v->mem = vector__mem;
	v->set = vector__set;
	v->fill = vector__fill;
	v->insert = vector__insert;
	v->delete = vector__delete;
	v->resize = vector__resize;
	v->from_array = vector__from_array;
	v->free = vector__free;

	return v;
}

unsigned int vector__length(vector *v){
	return v->len;
}

unsigned int vector__dtype(vector *v){
	return v->dtype;
}

void *vector__data(vector *v){
	return v->d;
}

void *vector__at(vector *v, unsigned int i){
	if(i >= v->length(v)) return NULL;
	void *ptr = v->d + i*v->dtype;
	return ptr;
}

unsigned int vector__mem(vector *v){
	if(!v) return 0;
	return sizeof(vector)+v->length(v)*v->dtype;
}

vector *vector__set(vector *v, unsigned int i, void *src){
	if(i >= v->length(v)) return NULL;
	void *dest = v->at(v, i);
	ULIB_MEMCPY(dest, src, v->dtype);
	return v;
}

vector *vector__fill(vector *v, void *src){
	unsigned int i;
	for(i=0; i<v->length(v); i++) v->set(v, i, src);
	return v;
}

vector *vector__insert(vector *v, unsigned int j, void *new){
	if(j > v->length(v)) return NULL;

	/*Reallocate with one extra space*/
	v->d = ULIB_REALLOC(v->d, v->dtype*(v->len+1) );
	if(v->d == NULL) return NULL;
	v->len++;

	/*Shift values forward from insert index*/
	unsigned int i;
	for(i=v->length(v)-1; i>j; i--){
		void *dest = v->at(v, i);
		void *src = v->at(v, i-1);
		ULIB_MEMCPY(dest, src, v->dtype);
	}

	/*Copy new member data from input pointer*/
	void *dest = v->at(v, j);
	ULIB_MEMCPY(dest, new, v->dtype);

	return v;
}

vector *vector__delete(vector *v, unsigned int i){
	if(i >= v->length(v)) return NULL;

	/*If there is only one member to delete, free instead*/
	if(v->len == 1){
		free(v->d);
		v->len--;
		return v;
	}

	/*Shift memory back over deleted member*/
	unsigned int j;
	for(j=i; j<v->length(v)-1; j++){
		void *src = v->at(v, j+1);
		void *dest = v->at(v, j);
		ULIB_MEMCPY(dest, src, v->dtype);
	}

	/*Reallocate to reduce memory usage*/	
	v->d = ULIB_REALLOC(v->d, v->dtype*(v->len-1) );	
	v->len--;
	if(!v->d)
		return NULL;

	return v;
}

vector *vector__resize(vector *v, unsigned int newsize){
	v->d = ULIB_REALLOC(v->d, sizeof(v->dtype)*newsize);
	if(v->d == NULL)
		return NULL;
	v->len = newsize;
	return v;
}

void vector__free(vector *v){
	if(!v || !v->d) return
	free(v->d);
	free(v);
}

vector *vector__from_array(void *arr, unsigned int elem_num, unsigned int elem_size){
	vector *v = vector_new(elem_size);
	v->resize(v, elem_num);
	ULIB_MEMCPY(v->data(v), arr, elem_num*elem_size);
	return v;
}

#endif /* VECTOR_IMPLEMENTATION */