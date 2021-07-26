/*

		defs.h

*/


#if !defined(ULIB_PRINTF)
#include <stdio.h>
#define ULIB_PRINTF printf
#endif

#if !defined(ULIB_MALLOC) || !defined(ULIB_REALLOC)
#include <stdlib.h>
#define ULIB_MALLOC malloc
#define ULIB_REALLOC realloc
#endif

#ifndef ULIB_MEMCPY
#define ULIB_MEMCPY ulib__memcpy
void* ulib__memcpy(void* dst, const void* src, unsigned int bytes){
	unsigned int i;
	char *d = dst;
	const char* s = src;
	for (i=0; i!=bytes; ++i) d[i] = s[i];
	return dst;
}
#endif

#ifndef ULIB_STRLEN
#define ULIB_STRLEN ulib__strlen
unsigned int ulib__strlen(const char* str){
	unsigned int len=0;
	while(*str++) len++;
	return len;
}
#endif

#ifndef ULIB_STRCPY
#define ULIB_STRCPY ulib__strcpy
char* ulib__strcpy(char* dst, const char* src){
	return ULIB_MEMCPY(dst, src, ULIB_STRLEN(src) * sizeof(char));	
}
#endif

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