#ifndef DICT_H
#define DICT_H

#define DEFS_IMPLEMENTATION
#include "defs.h"

struct dict__struct {
	unsigned char** keys;
	unsigned char** values;
	int length;

	/* Functions */
	const char** (*get_keys)();
	const char* (*getv)(unsigned int ind);
	const char* (*get)(const char* key);
	const char* (*setv)(unsigned int ind, const char* value);
	const char* (*set)(const char* key, const char* value);
};
typedef struct dict__struct dict;


dict* dict_new();
void dict_free(dict* d);

dict* dict__add(dict* d, const char* key, void* data);
dict* dict__remove(dict* d, const char* key, void* data);
dict* dict__set(dict* d, const char* key, void* data);
int dict__has_key(dict* d, const char* key);

#endif /* DICT_H */

#ifdef DICT_IMPLEMENTATION

#endif /* DICT_IMPLEMENTATION */







