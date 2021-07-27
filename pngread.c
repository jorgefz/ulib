
/*

This is a simple tool for reading data in PNG images.
It reads an input PNG image and prints the chunk names and sizes.
Alternatively, if a number of bytes is defined, it prints
the PNG file raw data formatted in a somewhat human readable form.

Input arguments:
	-h, --help			Displays available optional arguments
	-p, --png [STR]		Input PNG filename to read
	-b, --bytes [INT]	If defines, activates raw reading mode.
						Number of bytes to print from the file.
	-v, --verbose		Prints extra information during reading.


To compile, simply use your MAKE implementation:

	make png


TO-DO:
	- Better implementation of verbose



*/


#define ARGLIB_IMPLEMENTATION
#include "arglib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Format specifier for unsigned long long */
#ifdef _WIN32
#define ULL_FMT "I64u"
#elif defined(unix) || defined(__unix__) || defined(__unix)
# define ULL_FMT "llu"
#endif

#define STR_MAX 100

typedef unsigned long long ULL;

int VERBOSE = 0;

const int png_sig[] = {137, 80, 78, 71, 13, 10, 26, 10};
const int sig_len = 8;

/*
Joins a list of integers into a single hexadecimal
value and returns it.
*/
ULL hexjoin(int *dec, size_t len)
{
	size_t index = 0;
	ULL retnum;
	char hexstr[STR_MAX] = {0};
	char *endptr;

	// Join hex values into string
	for (size_t i=0; i<len; i++){
   		index += sprintf(&hexstr[index], "%02x", dec[i]);
	}

	// Convert string with hex into final joint value
	retnum = (ULL)strtol(hexstr, &endptr, 16);
	return retnum;
}


/*
Reads the first 8 bytes of the file
and looks for the PNG signature.
*/
int png_read_signature(FILE *png)
{
	for(int i=0; i<sig_len; i++)
	{
		if( fgetc(png) != png_sig[i] )
		{
			printf(" PNG signature failed!\n");
			return 1;
		}
	}
	return 0;
}


/*
Reads N bytes off the PNG file,
and returns the joint integer value.
*/
ULL png_read_bytes_asnum(FILE *png, int n)
{
	int dec[n];
	ULL size;

	// Reading 4 hex values corresponding to chunk size
	for(int i=0; i<n; i++){
		dec[i] = (int)fgetc(png);
	}
		
	//Joining values into total size
	size = hexjoin(dec, n);

	return size;
}

/*
Reads and prints the image data on the header
*/
int png_read_ihdr(FILE *png)
{
	int read_total = 13;
	ULL width = png_read_bytes_asnum(png, 4);
	ULL height = png_read_bytes_asnum(png, 4);
	ULL bit_depth = png_read_bytes_asnum(png, 1);
	ULL color_type = png_read_bytes_asnum(png, 1);
	ULL compress_method = png_read_bytes_asnum(png, 1);
	ULL filter_method = png_read_bytes_asnum(png, 1);
	ULL interlace_method = png_read_bytes_asnum(png, 1);

	printf(" Width = %"ULL_FMT"\n", width);
	printf(" Height = %"ULL_FMT"\n", height);
	printf(" Bit Depth = %"ULL_FMT"\n", bit_depth);
	printf(" Color type = %"ULL_FMT"\n", color_type);
	printf(" Compression method = %"ULL_FMT"\n", compress_method);
	printf(" Filter method = %"ULL_FMT"\n", filter_method);
	printf(" Interlace method = %"ULL_FMT"\n", interlace_method);

	fseek(png, -read_total, SEEK_CUR);

	return 0;
}



/*
Reads the 4 bytes corresponding to a chunk name
*/
char *png_read_chunk_name(FILE *png, char *name)
{
	for(int i=0; i<4; i++)
	{
		name[i] = fgetc(png);
	}
	name[4] = '\0';
	return name;
}

/*
Reads a PNG file and prints
chunk information.
*/
void png_chunk_loop(FILE *f)
{
	if(png_read_signature(f) != 0){
		exit(1);
	}

	char cname[5];
	int cnum = 0;
	do{
		ULL csize = png_read_bytes_asnum(f, 4);
		
		png_read_chunk_name(f, cname);
		
		printf(" %2d) Read chunk %s of size %d\n", cnum, cname, (int)csize);
		cnum++;

		if(strcmp(cname, "IHDR") == 0){
			png_read_ihdr(f);
		}
		
		// Skipping chunk data (last 4 byets for CRC checksum)
		ULL offset = csize + 4;
		fseek(f, offset, SEEK_CUR);
	}while(strcmp(cname, "IEND") != 0);
}

/*
Prints n bytes from the file
in a semi-human-readable fashion:
Alphanumeric values are printed as characters,
and the rest in hexadecimal.
*/
void png_print_loop(FILE *f, ULL n)
{
	for(ULL i = 0; i < n; i++)
	{
		printf("%05" ULL_FMT, i);
		for(int j=0; j<10; j++)
		{
			int r = fgetc(f);
			if(isalnum(r) == 1){
				printf(" %3c ", r);
			}
			else{
				printf(" %03x ", r);
			}
			i++;
		}
		i--;
		printf("\n");
	}
}



int main(int argc, const char *argv[])
{
	/* Input argument parsing */
	arglib_init();
	arglib_add_option('p', "png", "Input PNG file", ARG_STR, ARG_REQ);
	arglib_add_option('b', "bytes", "Number of bytes to print in raw reading mode", ARG_INT, ARG_OPT);
	arglib_add_option('v', "verbose", "Prints extra info", ARG_FLAG, ARG_OPT);

	if(arglib_parse(argc, argv) == NULL){
		return 1;
	}

	char fpng[STR_MAX+1] = {0};
	int rbytes = 0;
	
	char *argpng = arglib_get_value("png");
	memcpy(fpng, argpng, strlen(argpng));
	if( arglib_get_value("bytes") ){
		rbytes = *(int*)arglib_get_value("bytes");
	}
	if( arglib_get_value("verbose") ){
		VERBOSE = 1;
	}

	arglib_free();



	FILE *f = fopen(fpng, "rb");
	if(!f){
		printf("Error opening file '%s'\n", fpng);
		return 1;
	}
	
	if( rbytes > 0){
		png_print_loop(f, rbytes);
	}
	else{
		png_chunk_loop(f);
	}
	
	

	fclose(f);

	return 0;
}