

#define VECTOR_IMPLEMENTATION
#include "../vector.h"

#include <stdio.h>

int main(){

	vector* v = vector_new(sizeof(int));

	int f = 99;
	v->resize(v, 9);
	v->fill(v, &f);

	printf("vector size is %u\n", v->length(v));

	unsigned int i;
	for(i=0; i!=v->length(v); ++i) printf("%d ", *(int*)v->at(v,i));
	printf("\n");
	
	int n = 88;
	v->insert(v, 4, &n);

	for(i=0; i!=v->length(v); ++i) printf("%d ", *(int*)v->at(v,i));
	printf("\n");

	v->free(v);

	return 0;
}
