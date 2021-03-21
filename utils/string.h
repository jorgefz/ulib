
/*

--- string.h ---

Header-only library that adds the array data structure,
a list of numbers of immutable length, on which
a number of operations can be performed.

In order to use the functions from this library, write:
	#define ARRAY_IMPLEMENTATION
and THEN include the library:
	#include "array.h"

Currently, it only supports arrays of ints and doubles.

Standard: ANSI C89
Compiler: GCC version 9.2.0 (tdm64-1)


VERSIONS

v0.1 - 20/03/2021
	- Initialising: new, init, copy
	- Retrieving: at, getc
	- Editing: insert, erase
	- Other: free, print

*/


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		HEADER
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

/*
 *	DATA STRUCTURES & MACROS
 */

struct __attribute__((__packed__)) string__struct {
	char* str;
	unsigned long length;

	/* Function pointers */
	void (*free)(struct string__struct*);
	void (*print)(struct string__struct*);
	struct string__struct* (*copy)(struct string__struct*);
	char* (*at)(struct string__struct*, int j);
	char (*getc)(struct string__struct*, int j);
	struct string__struct* (*insert)(struct string__struct*, const char* substr, int j);
	struct string__struct* (*erase)(struct string__struct* s, int j, unsigned int n);
};
typedef struct string__struct string;

/*
 *	FUNCTION DECLARATIONS
 */
string* string_init(string* s, const char* s_orig);
string* string_new(const char* s_orig);
void string__free(string* s);

char* string__at(string* s, int j);
char string__getc(string* s, int j);

void string__print(string* s);
string* string__copy(string* s);

string* string__insert(string* s, const char* substr, int j);
string* string__erase(string* s, int j, unsigned int n);

/*

void clear(string *s) //cleans string to be emtpy

void append(string *s, const char* substr);

void slice(string *s, int from, int to) //reduce string to substring

------------------------------------

void string__find(string* s, const char* substr);
void string__substr(string* s, int i, int j);
int string__compare(string* s1, string* s2);
void string__cat(string* s1, string* s2);
void string__join(unsigned long num, ...);

remove certain tokens
remove all whitespaces

separate by tokens

*/

#endif /* string.h */



/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		IMPLEMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef STRING_IMPLEMENTATION

string* string_init(string* s, const char* s_orig){

	s->length = s_orig ? strlen(s_orig) : 0;
	s->str = calloc(s->length+1, sizeof(char));
	if(!s->str) return NULL;
	if(s_orig) strcpy(s->str, s_orig);

	/* Function pointers */
	s->free = &string__free;
	s->at = &string__at;
	s->getc = &string__getc;
	s->print = &string__print;
	s->copy = &string__copy;
	s->insert = &string__insert;
	s->erase = &string__erase;

	return s;
}

string* string_new(const char* s_orig){
	string* s;
	s = malloc(sizeof(string));
	if(!s) return NULL;
	return string_init(s, s_orig);
}

char* string__at(string* s, int j){
	if(abs(j) > (int)s->length) j = (int)s->length * j/abs(j);
	if(j < 0) j = (int)s->length + j;
	return (s->str + j);
}

char string__getc(string* s, int j){
	return *(s->at(s, j));
}

void string__print(string* s){
	printf("\"%s\"\n", s->str);
}

void string__free(string* s){
	free(s->str);
	free(s);
}

string* string__copy(string* s){
	string *new;
	new = malloc(sizeof(string));
	if(!new) return NULL;
	memcpy(new, s, sizeof(string));
	new->str = malloc(s->length+1);
	if(!new->str) return NULL;
	memcpy(new->str, s->str, s->length+1);
	return new;
}

string* string__insert(string* s, const char* substr, int j){
	if(j < 0) j = (int)s->length + j + 1;
	if(j > (int)s->length || j < 0) return NULL;

	unsigned int sslength = strlen(substr);

	char* insptr = s->str + j;
	char* newstr = realloc(s->str, s->length + sslength + 1);
	if(!newstr) return NULL;
	
	s->str = newstr;
	s->length += sslength;

	memcpy(insptr + sslength, insptr, s->length - sslength);
	memcpy(insptr, substr, sslength);
	*(s->str + s->length) = (char)0;

	return s;
}

string* string__erase(string* s, int j, unsigned int n){
	if(j < 0) j = (int)s->length + j + 1;
	if(j > (int)s->length || j < 0) return NULL;
	if(j+(int)n > (int)s->length) n = s->length - j;

	memcpy(s->str+j, s->str+j+n, s->length-j-n);

	char* newstr = realloc(s->str, s->length - n + 1);
	if(!newstr) return NULL;
	s->str = newstr;
	s->length -= n;
	*(s->str + s->length) = (char)0;
	return s;
}


#endif /* STRING_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif
