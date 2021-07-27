
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

v0.2 - 22/0.3/2021
	- Editing: append, clear, slice, substr

*/


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		HEADER
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/


#ifndef STRING_H
#define STRING_H

#ifndef DEFS_IMPLEMENTATION
#define DEFS_IMPLEMENTATION
#include "defs.h"
#endif

/*
 *	DATA STRUCTURES & MACROS
 */

struct string__struct {
	char* str;
	unsigned long length;

	/* Function pointers */
	void (*free)(struct string__struct*);
	void (*print)(struct string__struct*);
	struct string__struct* (*copy)(struct string__struct*);
	char* (*at)(struct string__struct*, int j);
	char (*getc)(struct string__struct*, int j);
	struct string__struct* (*insert)(struct string__struct*, const char* substr, int j);
	struct string__struct* (*append)(struct string__struct*, const char* substr);
	
	struct string__struct* (*erase)(struct string__struct* s, int j, unsigned int n);
	struct string__struct* (*clear)(struct string__struct* s);
	struct string__struct* (*slice)(struct string__struct* s, int j, int k);
	struct string__struct* (*substr)(struct string__struct* s, int j, int k);
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
string* string__append(string* s, const char* substr);

string* string__erase(string* s, int j, unsigned int n);
string* string__clear(string* s);
string* string__slice(string* s, int j, int k);

string* string__substr(string* s, int j, int k);

/*

void string__reverse(string* s);
//reverses input string

string* string__trim(string* s);
//removes trailing whitespaces

int string__find(string* s, const char* substr);
//Returns index of location of substring, or (-1) otherwise.

int string__compare(string* s1, string* s2);
//Same as strcmp

int string__equals(string* s1, string *s2);
//Returns 1 if same, 0 otherwise

void string__join(unsigned long num, ...);
//last string must be "\0"

int string__ntoken(string* s, const char* tokens)
//Returns number of occurences of input tokens in string, -1 if none found.

int string__ftoken(string* s, const char* tokens, int j)
//Returns index of first occurence of any input token,
// starting search from given index 'j'.
// Returns -1 if none found.

string* string__dtoken(string* s, const char* tokens)
// removes all instances of input tokens

string* string__split(string* s, const char* tokens)
//Separates a string by input tokens
// Returns an array of pointers to substrings

*/

#endif /* string.h */



/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		IMPLEMENTATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef STRING_IMPLEMENTATION

string* string_init(string* s, const char* s_orig){

	s->length = s_orig ? ULIB_STRLEN(s_orig) : 0;
	s->str = calloc(s->length+1, sizeof(char));
	if(!s->str) return NULL;
	if(s_orig) ULIB_STRCPY(s->str, s_orig);

	/* Function pointers */
	s->free = &string__free;
	s->at = &string__at;
	s->getc = &string__getc;
	s->print = &string__print;
	s->copy = &string__copy;
	
	s->insert = &string__insert;
	s->append = &string__append;

	s->erase = &string__erase;
	s->clear = &string__clear;
	s->slice = &string__slice;
	s->substr = &string__substr;

	return s;
}

string* string_new(const char* s_orig){
	string* s;
	s = malloc(sizeof(string));
	if(!s) return NULL;
	return ( string_init(s, s_orig) );
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

	if(!s) printf("s is null\n");
	if(!s->str) printf("str is null\n");

	free(s->str);
	free(s);
}

string* string__copy(string* s){
	string *new;
	new = malloc(sizeof(string));
	if(!new) return NULL;
	ULIB_MEMCPY(new, s, sizeof(string));
	new->str = malloc(s->length+1);
	if(!new->str) return NULL;
	ULIB_MEMCPY(new->str, s->str, s->length+1);
	return new;
}

string* string__insert(string* s, const char* substr, int j){

	if(j < 0) j = (int)s->length + j + 1;
	if(j > (int)s->length || j < 0) return NULL;

	unsigned int sslength = ULIB_STRLEN(substr);
	char* insptr = s->str + j;

	char* newstr = realloc(s->str, (s->length + sslength + 1)*sizeof(char) );
	if(!newstr) return NULL;

	s->str = newstr;
	s->length += sslength;

	ULIB_MEMCPY(insptr + sslength, insptr, s->length - sslength - j);
	ULIB_MEMCPY(insptr, substr, sslength);
	*(s->str + s->length) = (char)0;

	return s;
}

string* string__append(string* s, const char* substr){
	return ( s->insert(s, substr, s->length) );
}

string* string__erase(string* s, int j, unsigned int n){
	if(j < 0) j = (int)s->length + j + 1;
	if(j > (int)s->length || j < 0) return NULL;
	if(j+(int)n > (int)s->length) n = s->length - j;

	ULIB_MEMCPY(s->str+j, s->str+j+n, s->length-j-n);

	char *newstr = NULL;
	newstr = realloc(s->str, s->length - n + 1 );
	if(!newstr) return NULL;

	s->str = newstr;
	s->length -= n;
	*(s->str + s->length) = (char)0;
	return s;
}

string* string__clear(string* s){
	return s->erase(s, 0, s->length+1);
}

string* string__slice(string* s, int j, int k){
	unsigned int n;
	j < 0 ? n = s->length+(unsigned int)j : (n = (unsigned int)j);
	if( s->erase(s, 0, n) == NULL ) return NULL;
	if( s->erase(s, k-j, s->length) == NULL) return NULL;
	return s;
}


string* string__substr(string* s, int j, int k){
	string *substr = s->copy(s);
	if(!substr) return NULL;

	string* ret = substr->slice(substr, j, k);
	if(!ret){
		substr->free(substr);
		return NULL;
	}

	return substr;
}

#endif /* STRING_IMPLEMENTATION */

