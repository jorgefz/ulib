

/*
	======= vector.h =======

	This library provides a new object 'vector'
	that behaves as an easily resizeable array
	for any data type and structure.

	To create a new vector, use:
		vector *v = vnew( sizeof(T) );
	where T is the data type of its members.

	To insert a new member 'var' at index 0, use:
		vinsert( v, 0, &var );

	To retrieve the current vector size, use:
		vsize(v);

	To delete a vector member at index 'i', use:
		vdelete( v, i);

	To retrieve a pointer to a specific member
	at index 'i', use:
		T *ptr = vat( v, i );

	To free a vector, use:
		vfree(v);

	To resize a vector to a given size, use:
		vresize(v, size);

	To fill every vector member with the same item, use:
		vfill(v, &item);




	----- Version History -----

	1.0 - 19/07/2020
		- Added basic vector functions:
		vnew, vfree, vsize, vat,
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
			


*/


#ifndef VECTOR_H
#define VECTOR_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct __attribute__((__packed__)) vector__struct {
	void *d;
	unsigned int size;
	unsigned int dtype;
};
typedef struct vector__struct vector;

/* Function Prototypes */
vector *vnew(unsigned int bytes);
unsigned int vsize(vector *v);

unsigned int vdtype(vector *v);
void *vdata(vector *v);
void *vat(vector *v, unsigned int i);

unsigned int vmem(vector *v);

vector *vset(vector *v, unsigned int i, void *src);
vector *vfill(vector *v, void *src);

vector *vinsert(vector *v, unsigned int j, void *new);
vector *vdelete(vector *v, unsigned int i);
vector *vresize(vector *v, unsigned int newsize);
void vfree(vector *v);
vector *vtovector(void *arr, unsigned int elem_num, unsigned int elem_size);

#endif


#ifdef VECTOR_IMPLEMENTATION

/* Allocates new vector and returns pointer to it */
vector *vnew(unsigned int bytes) {
	vector *v = malloc(sizeof(vector));
	if(!v) return NULL;
	v->d = NULL;
	v->size = 0;
	v->dtype = bytes;

	return v;
}

unsigned int vsize(vector *v){
	return v->size;
}

unsigned int vdtype(vector *v){
	return v->dtype;
}

void *vdata(vector *v){
	return v->d;
}

void *vat(vector *v, unsigned int i){
	if(i >= vsize(v)) return NULL;
	void *ptr = v->d + i*v->dtype;
	return ptr;
}

unsigned int vmem(vector *v){
	if(!v) return 0;
	return sizeof(vector)+vsize(v)*vdtype(v);
}

vector *vset(vector *v, unsigned int i, void *src){
	if(i >= vsize(v)) return NULL;
	void *dest = vat(v, i);
	memcpy(dest, src, v->dtype);
	return v;
}

vector *vfill(vector *v, void *src){
	unsigned int i;
	for(i=0; i<vsize(v); i++) vset(v, i, src);
	return v;
}

vector *vinsert(vector *v, unsigned int j, void *new){
	if(j > vsize(v)) return NULL;

	/*Reallocate with one extra space*/
	v->d = realloc(v->d, v->dtype*(v->size+1) );
	if(v->d == NULL) return NULL;
	v->size++;

	/*Shift values forward from insert index*/
	unsigned int i;
	for(i=vsize(v)-1; i>j; i--){
		void *dest = vat(v, i);
		void *src = vat(v, i-1);
		memcpy(dest, src, v->dtype);
	}

	/*Copy new member data from input pointer*/
	void *dest = vat(v, j);
	memcpy(dest, new, v->dtype);

	return v;
}

vector *vdelete(vector *v, unsigned int i){
	if(i >= vsize(v)) return NULL;

	/*If there is only one member to delete, free instead*/
	if(v->size == 1){
		free(v->d);
		v->size--;
		return v;
	}

	/*Shift memory back over deleted member*/
	unsigned int j;
	for(j=i; j<vsize(v)-1; j++){
		void *src = vat(v, j+1);
		void *dest = vat(v, j);
		memcpy(dest, src, v->dtype);
	}

	/*Reallocate to reduce memory usage*/	
	v->d = realloc(v->d, v->dtype*(v->size-1) );	
	v->size--;
	if(!v->d)
		return NULL;

	return v;
}

vector *vresize(vector *v, unsigned int newsize){
	v->d = realloc(v->d, sizeof(v->dtype)*newsize);
	if(v->d == NULL)
		return NULL;
	v->size = newsize;
	return v;
}

void vfree(vector *v){
	if(!v || !v->d) return
	free(v->d);
	free(v);
}

vector *vtovector(void *arr, unsigned int elem_num, unsigned int elem_size){
	vector *v = vnew(elem_size);
	vresize(v, elem_num);
	memcpy(vdata(v), arr, elem_num*elem_size);
	return v;
}

#endif /* VECTOR_IMPLEMENTATION */