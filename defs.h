/*

		defs.h

*/

#ifndef DEFS_H
#define DEFS_H 1

/* stdio.h functions */
#if !defined(ULIB_PRINTF) || !defined(ULIB_FPRINTF)
	#include <stdio.h>
	#define ULIB_PRINTF printf
	#define ULIB_FPRINTF fprintf
#endif

/* stdlib.h functions */
#if !defined(ULIB_MALLOC) || !defined(ULIB_REALLOC)
	#include <stdlib.h>
	#define ULIB_MALLOC malloc
	#define ULIB_REALLOC realloc
#endif

#if !defined(ULIB_STRTOL) || !defined(ULIB_STRTOD)
	#include <stdlib.h>
	#define ULIB_STRTOL strtol
	#define ULIB_STRTOD strtod
#endif

/* string.h functions */
#ifndef ULIB_MEMCPY
	#define ULIB_MEMCPY ulib__memcpy
#endif

#ifndef ULIB_STRLEN
	#define ULIB_STRLEN ulib__strlen
#endif

#ifndef ULIB_STRCPY
	#define ULIB_STRCPY ulib__strcpy
#endif

#ifndef ULIB_STRCMP
	#define ULIB_STRCMP ulib__strcmp
#endif

#ifndef ULIB_STRCAT
	#define ULIB_STRCAT ulib__strcat
#endif

/* stdarg.h functions */
#if !defined(ULIB_VA_LIST)  || \
	!defined(ULIB_VA_START) || \
	!defined(ULIB_VA_ARG)   || \
	!defined(ULIB_VA_END)
	
	#include <stdarg.h>
	#define ULIB_VA_LIST va_list
	#define ULIB_VA_START va_start
	#define ULIB_VA_ARG va_arg
	#define ULIB_VA_END va_end
#endif


void* ulib__memcpy(void*, const void*, unsigned int);
unsigned int ulib__strlen(const char*);
char* ulib__strcpy(char* dst, const char* src);

int ulib__strcmp(const char*, const char*);
char* ulib__strcat(char*, const char*);

#endif /* DEFS_H */


#ifdef DEFS_IMPLEMENTATION

void* ulib__memcpy(void* dst, const void* src, unsigned int bytes){
	unsigned int i;
	char *d = dst;
	const char* s = src;
	for (i=0; i!=bytes; ++i) d[i] = s[i];
	return dst;
}

unsigned int ulib__strlen(const char* str){
	unsigned int len=0;
	while(*str++) len++;
	return len;
}

char* ulib__strcpy(char* dst, const char* src){
	return ULIB_MEMCPY(dst, src, ULIB_STRLEN(src) + 1);	
}

int ulib__strcmp(const char* x, const char* y){
	while(*x){
		if(*x!=*y) break;
		x++;
		y++;
	}
	return *(const unsigned char*)x - *(const unsigned char*)y;
}

char* ulib__strcat(char* dst, const char* src){
	char* ret = dst;
	while(*dst) dst++;
	while( (*dst++ = *src++) );
	return ret;
}

#endif /* DEFS_IMPLEMENTATION */
