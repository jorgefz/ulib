

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
	__array_debug(arr);
	arr->fill(arr,5);
	arr->print(arr);
	arr->range(arr,9,99);
	arr->print(arr);
	arr->free(arr);

	// array of doubles
	array* nums = array_new(6, DOUBLE);
	if(!nums){
		printf("Error!\n");
		return 1;
	}
	__array_debug(nums);
	nums->range(nums, 3.1415, -0.77);
	nums->print(nums);
	nums->free(nums);

	return 0;
}
