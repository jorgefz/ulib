

#define ARRAY_IMPLEMENTATION
#include "../array.h"

/* compares doubles */
int cmpdb(double x, double y, double delta){
	if(delta < 0.0) delta *= -1.0;
	if( (x-y) >= 0.0 && (x-y) < delta )
		return 1;
	else if( (x-y) < 0.0 && (x-y) > -delta )
		return 1;
	else return 0;

}

void test_free(array* arr){
	ULIB_FPRINTF(stderr, "Free... ");
	arr->free(arr);
	ULIB_FPRINTF(stderr, "PASSED\n");
}

void test_new_int(){
	unsigned int len = 10;
	array *arr = array_new(len, TYPE_INT);
	if(!arr || arr->length(arr) != len){
		ULIB_FPRINTF(stderr, "New int: FAILED (%u)\n", len);
		exit(1);
	}
	ULIB_FPRINTF(stderr, "New int: PASSED\n");
	test_free(arr);
}

void test_fill_int(){
	array* arr = array_new(10, TYPE_INT);
	arr->fill(arr,5);
	unsigned int i;
	for(i=0; i!=arr->length(arr); ++i){
		if(arr->geti(arr,i) != 5){
			ULIB_FPRINTF(stderr, "Fill int: FAILED\n");
			exit(1);
		}
	}
	ULIB_FPRINTF(stderr, "Fill int: PASSED\n");
	arr->free(arr);
}

void test_range_int(){
	array* arr = array_new(10, TYPE_INT);
	arr->range(arr,10,-10);
	int result[] = {-10,-8,-6,-4,-2,0,2,4,6,8};
	unsigned int i;
	for(i=0; i!=arr->length(arr); ++i){
		if(arr->geti(arr,i) != result[i]){
			ULIB_FPRINTF(stderr, "Range int: FAILED\n");
			exit(1);
		}
	}
	ULIB_FPRINTF(stderr, "Range int: PASSED\n");
	arr->free(arr);
}

void test_from_c_arr_int(){
	array* arr = array_new(10, TYPE_INT);
	int c_arr[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, -11};
	arr->from_c_array(arr, c_arr);
	unsigned int i;
	for(i=0; i!=arr->length(arr); ++i){
		if(arr->geti(arr,i) != c_arr[i]){
			ULIB_FPRINTF(stderr, "From c-arr int: FAILED\n");
			exit(1);
		}
	}
	ULIB_FPRINTF(stderr, "From c-arr int: PASSED\n");
	arr->free(arr);
}


void test_linspace_int(){
	array* arr = array_new(100, TYPE_INT);
	arr->linspace(arr, -500, 1);
	unsigned int i;
	for(i=0; i!=arr->length(arr); ++i){
		if(arr->geti(arr,i) != (int)i-500){
			ULIB_FPRINTF(stderr, "Linspace int: FAILED\n");
			exit(1);
		}
	}
	ULIB_FPRINTF(stderr, "Linspace int: PASSED\n");
	arr->free(arr);
}

void test_stats_int(){

	array* arr = array_new(100, TYPE_INT);
	arr->linspace(arr, -500, 1);

	int max = -401;
	unsigned int imax = 99;
	int min = -500;
	unsigned int imin = 0;
	int sum = -45050;
	double mean = -450.5;

	if (arr->maxi(arr) != max){
		ULIB_FPRINTF(stderr, "Max: FAILED\n");
		exit(1);
	}

	if (arr->imax(arr) != imax){
		ULIB_FPRINTF(stderr, "Max-i: FAILED\n");
		exit(1);
	}

	if (arr->mini(arr) != min){
		ULIB_FPRINTF(stderr, "Min: FAILED\n");
		exit(1);
	}

	if (arr->imin(arr) != imin){
		ULIB_FPRINTF(stderr, "Min-i: FAILED\n");
		exit(1);
	}

	if (arr->sumi(arr) != sum){
		ULIB_FPRINTF(stderr, "Sum: FAILED\n");
		exit(1);
	}

	if (arr->mean(arr) != mean){
		ULIB_FPRINTF(stderr, "Mean: FAILED\n");
		exit(1);
	}

	ULIB_FPRINTF(stderr, "Stats int: PASSED\n");
	arr->free(arr);
}



void test_new_double(){
	unsigned int len = 10;
	array *arr = array_new(len, TYPE_DOUBLE);
	if(!arr || arr->length(arr) != len){
		ULIB_FPRINTF(stderr, "New double: FAILED (%u)\n", len);
		exit(1);
	}
	ULIB_FPRINTF(stderr, "New double: PASSED\n");
	test_free(arr);
}

void test_range_double(){
	array* nums = array_new(6, TYPE_DOUBLE);
	nums->range(nums, 3.1415, -0.77);
	double result[] = {-0.77, -0.118083, 0.533833, 1.18575, 1.83767, 2.48958};
	unsigned int i;
	for(i=0; i!=nums->length(nums); ++i){
		if( cmpdb(nums->getf(nums,i), result[i], 1e-4) == 0 ){
			ULIB_FPRINTF(stderr, "Range double: FAILED\n");
			exit(1);
		}
	}
	nums->free(nums);
	ULIB_FPRINTF(stderr, "Range double: PASSED\n");
}

void test_stats_double(){

	array* nums = array_new(6, TYPE_DOUBLE);
	nums->range(nums, 3.1415, -0.77);

	double max = 2.48958;
	unsigned int imax = 5;
	double min = -0.77000;
	unsigned int imin = 0;
	double sum = 5.15875;
	double mean = 0.859792;

	if ( cmpdb(nums->maxf(nums), max, 1e-4) == 0 ){
		ULIB_FPRINTF(stderr, "Max: FAILED\n");
		exit(1);
	}

	if (nums->imax(nums) != imax){
		ULIB_FPRINTF(stderr, "Max-i: FAILED\n");
		exit(1);
	}

	if ( cmpdb(nums->minf(nums), min, 1e-4) == 0 ){
		ULIB_FPRINTF(stderr, "Min: FAILED\n");
		exit(1);
	}

	if (nums->imin(nums) != imin){
		ULIB_FPRINTF(stderr, "Min-i: FAILED\n");
		exit(1);
	}

	if ( cmpdb(nums->sumf(nums), sum, 1e-4) == 0 ){
		ULIB_FPRINTF(stderr, "Sum: FAILED\n");
		exit(1);
	}

	if ( cmpdb(nums->mean(nums), mean, 1e-4) == 0 ){
		ULIB_FPRINTF(stderr, "Mean: FAILED\n");
		exit(1);
	}
	nums->free(nums);
	ULIB_FPRINTF(stderr, "Stats double: PASSED\n");
}


void test_matherr(){
	array* nums = array_new(10, TYPE_DOUBLE);
	nums->range(nums, 3.1415, -0.77);
	nums->setf(nums, 5, ULIB_NAN);
	nums->setf(nums, 2, ULIB_INF);

	if( array__has_nan(nums) != 1){
		ULIB_FPRINTF(stderr, "Nans: FAILED\n");
		exit(1);
	}

	if( array__has_matherr(nums) != 2){
		ULIB_FPRINTF(stderr, "Math error: FAILED\n");
		exit(1);
	}

	nums->free(nums);
	ULIB_FPRINTF(stderr, "Math error: PASSED\n");
}

int main(){

	test_new_int();
	test_fill_int();
	test_range_int();
	test_from_c_arr_int();
	test_new_int();
	test_linspace_int();
	test_stats_int();

	test_new_double();
	test_range_double();
	test_stats_double();
	test_matherr();

	return 0;
}
