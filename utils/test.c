

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>


#include "array.h"

int main(){

	// array of integers
	array *arr = array_new(10, INT);
	if(!arr){
		printf("Error!\n");
		return 1;
	}
	//__array_debug(arr);
	arr->fill(arr,5);
	arr->print(arr);
	arr->range(arr,10,0);
	arr->print(arr);
	int c_arr[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, -11};
	arr->from_c_array(arr, c_arr);
	arr->print(arr);
	arr->free(arr);

	arr = array_new(100, INT);
	if(!arr) return 1;
	arr->linspace(arr, -500, -111);
	arr->print(arr);
	arr->free(arr);

	// array of doubles
	array* nums = array_new(6, DOUBLE);
	if(!nums){
		fprintf(stderr, "Error!\n");
		return 1;
	}
	//__array_debug(nums);
	nums->range(nums, 3.1415, -0.77);
	nums->print(nums);

	double sum = 0;
	for(uint i=0; i!=nums->size; ++i)
		sum += nums->getf(nums,i);
	printf("Average: %.11g\n", sum/(double)nums->size);
	nums->free(nums);

	return 0;
}
