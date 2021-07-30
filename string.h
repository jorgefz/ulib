
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

TO-DO
	- Let string_new accept formatted strings like sprintf.
		E.g. string* string_new(char*, ...) ->
			string_new(NULL), string_new("Hello"), string_new("%d+%d=%d", a, b, c)

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

typedef struct string__struct string;
struct string__struct {
	char* str;
	unsigned long len;

	/* Function pointers */
	unsigned int (*length)(string*);
	void (*free)(string*);
	void (*print)(string*);
	string* (*copy)(string*);
	char* (*at)(string*, int j);
	char (*getc)(string*, int j);
	string* (*insert)(string*, const char* substr, int j);
	string* (*append)(string*, const char* substr);
	
	string* (*erase)(string* s, int j, unsigned int n);
	string* (*clear)(string* s);
	string* (*slice)(string* s, int j, int k);
	string* (*substr)(string* s, int j, int k);
};


/*
 *	FUNCTION DECLARATIONS
 */
string* string_init(string* s, const char* s_orig);
string* string_new(const char* s_orig, ...);
void string__free(string* s);

unsigned int string__length(string* s);
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

	s->len = s_orig ? ULIB_STRLEN(s_orig) : 0;
	s->str = calloc(s->len+1, sizeof(char));
	if(!s->str) return NULL;
	if(s_orig) ULIB_STRCPY(s->str, s_orig);

	/* Function pointers */
	s->free = &string__free;
	s->length = string__length;
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

/* NEW */
FILE* fopen_null(){
	#ifdef _WIN32
		const char* snull = "nul";
	#else
		const char* snull = "/dev/null";
	#endif
	return ULIB_FOPEN(snull, "w");
}

/* NEW */
/* Returns the final length of a formatted string */
int vfstrlen(const char* fmt, ULIB_VA_LIST vargs){
	FILE* fnull = fopen_null();
	if(!fnull) return -1;
	int len = ULIB_VFPRINTF(fnull, fmt, vargs); /* returns negative number on fail */
	ULIB_FCLOSE(fnull);
	return len;
}

string* string_new(const char* fmt, ...){
	/* allocate string */
	string* s = ULIB_MALLOC(sizeof(string));
	if(!s) return NULL;
	if(!fmt) return string_init(s, NULL); /* create empty string */

	/*
	 * Fake snprintf for C89 (not in standard lib till C99).
	 * fprintf to NUL to get final length,
	 * allocate as much, and create formatted string.
	 * This avoids buffer overflow on sprintf.
	 */
	ULIB_VA_LIST vargs;
	ULIB_VA_START(vargs, fmt);
	int slength = vfstrlen(fmt, vargs); /* returns negative number on fail */
	
	#ifdef ULIB_DEBUG
	ULIB_PRINTF("DEBUG: new string vfstrlen -> %d\n", slength);
	#endif

	if(slength < 0){
		ULIB_FREE(s);
		return NULL;
	}
	char* fullstr = ULIB_MALLOC(slength+1);
	if(!fullstr){
		ULIB_FREE(s);
		return NULL;
	}
	int retsize = ULIB_VSPRINTF(fullstr, fmt, vargs); /* returns negative number on fail */
	if (retsize < 0 || retsize != slength){
		ULIB_FREE(s);
		ULIB_FREE(fullstr);
		return NULL;
	}
	ULIB_VA_END(vargs);
	s = string_init(s, fullstr);
	ULIB_FREE(fullstr);
	return s;
}

unsigned int string__length(string* s){
	return ULIB_STRLEN(s->str);
}

char* string__at(string* s, int j){
	if(abs(j) > (int)s->len) j = (int)s->len * j/abs(j);
	if(j < 0) j = (int)s->len + j;
	return (s->str + j);
}

char string__getc(string* s, int j){
	char *c = s->at(s, j);
	if(!c) return (char)0;
	return *c;
}

void string__print(string* s){
	ULIB_PRINTF("\"%s\"", s->str);
}

void string__free(string* s){
	if(!s) return;
	if(s->str) ULIB_FREE(s->str);
	ULIB_FREE(s);
}

string* string__copy(string* s){
	string *new;
	new = malloc(sizeof(string));
	if(!new) return NULL;
	ULIB_MEMCPY(new, s, sizeof(string));
	new->str = malloc(s->len+1);
	if(!new->str) return NULL;
	ULIB_MEMCPY(new->str, s->str, s->len+1);
	return new;
}

string* string__insert(string* s, const char* substr, int j){

	if(j < 0) j = (int)s->len + j + 1;
	if(j > (int)s->len || j < 0) return NULL;

	unsigned int sslength = ULIB_STRLEN(substr);
	char* insptr = s->str + j;

	char* newstr = realloc(s->str, (s->len + sslength + 1)*sizeof(char) );
	if(!newstr) return NULL;

	s->str = newstr;
	s->len += sslength;

	ULIB_MEMCPY(insptr + sslength, insptr, s->len - sslength - j);
	ULIB_MEMCPY(insptr, substr, sslength);
	*(s->str + s->len) = (char)0;

	return s;
}

string* string__append(string* s, const char* substr){
	return ( s->insert(s, substr, s->len) );
}

string* string__erase(string* s, int j, unsigned int n){
	if(j < 0) j = (int)s->len + j + 1;
	if(j > (int)s->len || j < 0) return NULL;
	if(j+(int)n > (int)s->len) n = s->len - j;

	ULIB_MEMCPY(s->str+j, s->str+j+n, s->len-j-n);

	char *newstr = NULL;
	newstr = realloc(s->str, s->len - n + 1 );
	if(!newstr) return NULL;

	s->str = newstr;
	s->len -= n;
	*(s->str + s->len) = (char)0;
	return s;
}

string* string__clear(string* s){
	return s->erase(s, 0, s->len+1);
}

string* string__slice(string* s, int j, int k){
	unsigned int n;
	j < 0 ? n = s->len+(unsigned int)j : (n = (unsigned int)j);
	if( s->erase(s, 0, n) == NULL ) return NULL;
	if( s->erase(s, k-j, s->len) == NULL) return NULL;
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

