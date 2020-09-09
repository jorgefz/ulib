

#ifndef VECTOR_H
#define VECTOR_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
Macro to create new vector.

vnew( data_type ) => vnew( "data_type", sizeof(data_type) )

Example of creating vector:
	vector *v = vnew(int)
*/
#define vnew(type) _vnew( (#type), sizeof(type))


typedef struct vectorStruct
{
	void *d;
	size_t size;
	size_t dtype;
	char *dtype_name;
} vector;



/*
Allocates new vector and returns pointer to it
*/
vector *_vnew(char *T, size_t bytes);


//		GETTERS
/*
Returns the size of the vector
*/
size_t vsize(vector *v);

/*
Returns the memory size of the
vector members' data type, in bytes
*/
size_t vdtype(vector *v);

/* Returns pointer to data array of vector */
void *vdata(vector *v);

/*
Returns a pointer to a vector member.
Must be cast to the appropriate data type.
e.g.
	double *var = *(double*) vat(v,0)
returns a pointer to the first member (index 0)
of a vector 'v' and casts it to a double.
*/
void *vat(vector *v, size_t i);

/*
Returns the total memory allocated for the vector
*/
size_t vmem(vector *v);



//		SETTERS


/* Changes the value of a vector member */
vector *vset(vector *v, size_t i, void *src);

/*
Substitutes every member in the vector with
the input member
*/
vector *vfill(vector *v, void *src);



//		SIZE MANIPULATION

/*
Inserts a new member into the vector
at index 'j'.
*/
vector *vinsert(vector *v, size_t j, void *new);

/* Removes member 'i' from vector */
vector *vdelete(vector *v, size_t i);

vector *vresize(vector *v, size_t newsize);

void vfree(vector *v);

#define vtovector(arr, n, type) _vtovector(arr, n, #type, sizeof(type))
/* Converts an array into a vector */
vector *_vtovector(void *arr, size_t elem_num, char *T, size_t elem_size);



#endif