

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_IMPLEMENTATION
#include "../vector.h"


int main(){

	vector* v = vnew(sizeof(int));
	int f = 99;
	vresize(v, 9);
	vfill(v, &f);

	printf("vector size is %u\n", vsize(v));

	unsigned int i;
	for(i=0; i!=vsize(v); ++i) printf("%d ", *(int*)vat(v,i));
	printf("\n");
	
	int n = 88;
	vinsert(v, 4, &n);

	for(i=0; i!=vsize(v); ++i) printf("%d ", *(int*)vat(v,i));
	printf("\n");

	vfree(v);

	return 0;
}
