

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

#define ARRAY_IMPLEMENTATION
#include "array.h"


int main(){

	/* array of integers */
	array *arr = array_new(10, INT);
	if(!arr){
		printf("Error!\n");
		return 1;
	}

	/* __array_debug(arr); */
	arr->fill(arr,5);
	arr->print(arr);
	arr->range(arr,10,-10);
	arr->print(arr);
	int c_arr[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, -11};
	arr->from_c_array(arr, c_arr);
	arr->print(arr);
	arr->free(arr);

	arr = array_new(100, INT);
	if(!arr) return 1;
	arr->linspace(arr, -500, 1);

	printf("Max %d at %d\n", arr->maxi(arr), (int)arr->imax(arr));
	printf("Min %d at %d\n", arr->mini(arr), (int)arr->imin(arr));
	printf("Sum: %d\n", arr->sumi(arr));
	printf("Mean: %g\n", arr->mean(arr));

	arr->print(arr);
	arr->free(arr);

	/* array of doubles */
	array* nums = array_new(6, DOUBLE);
	if(!nums){
		fprintf(stderr, "Error!\n");
		return 1;
	}
	/* __array_debug(nums); */
	nums->range(nums, 3.1415, -0.77);
	nums->print(nums);
	printf("Max %g at %d\n", nums->maxf(nums), (int)nums->imax(nums));
	printf("Min %g at %d\n", nums->minf(nums), (int)nums->imin(nums));
	printf("Sum: %g\n", nums->sumf(nums));
	printf("Mean: %g\n", nums->mean(nums));
	nums->free(nums);

	return 0;
}
