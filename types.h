
#ifndef TYPES_H
#define TYPES_H 1

/*
	TYPES.H

*/

#ifndef DEFS_IMPLEMENTATION
#define DEFS_IMPLEMENTATION
#include "defs.h"
#endif

enum types__types{
	TYPE_INT,
	TYPE_UINT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_CHAR,
	TYPE_UCHAR,
	TYPE_STR_10,
	TYPE_STR_20,
	TYPE_STR_50,
	TYPE_STR_100,
	TYPE_OTHER
};

unsigned int types__sizes[] = {
	sizeof(int),
	sizeof(unsigned int),
	sizeof(float),
	sizeof(double),
	sizeof(char),
	sizeof(unsigned char),
	sizeof(char)*10,
	sizeof(char)*20,
	sizeof(char)*50,
	sizeof(char)*100,
	sizeof(char*)
};

char types__fmts[] = {
	'd',
	'u',
	'f',
	'g',
	'c',
	'd',
	's',
	's',
	's',
	's',
	'p'
};

const char* types__names[] = {
	"int",
	"unsigned int",
	"float",
	"double",
	"char",
	"unsigned char",
	"str(10)",
	"str(20)",
	"str(50)",
	"str(100)",
	"object"
};


void types__print(unsigned int type, void* var);


#endif /* TYPES_H */



#ifdef TYPES_IMPLEMENTATION

void types__print(unsigned int type, void* var){
	switch(type){
		case TYPE_INT:
			ULIB_PRINTF("%d", *(int*)var);
			break;
		case TYPE_UINT:
			ULIB_PRINTF("%u", *(unsigned int*)var);
			break;
		case TYPE_FLOAT:
			ULIB_PRINTF("%f", *(float*)var);
			break;
		case TYPE_DOUBLE:
			ULIB_PRINTF("%g", *(double*)var);
			break;
		case TYPE_CHAR:
			ULIB_PRINTF("%c", *(char*)var);
			break;
		case TYPE_UCHAR:
			ULIB_PRINTF("%u", (unsigned int)*(unsigned char*)var);
			break;
		case TYPE_STR_10:
		case TYPE_STR_20:
		case TYPE_STR_50:
		case TYPE_STR_100:
			ULIB_PRINTF("%s", (char*)var);
			break;
		default:
			ULIB_PRINTF("%p", var);
			break;
	}
}


#endif /* TYPES_IMPLEMENTATION */




