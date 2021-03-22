

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_IMPLEMENTATION
#include "../string.h"


void string_debug(string* s){
	printf("\n\n\n DEBUG String\n");

	printf(" Allocated %d bytes, from 0x%p to 0x%p\n", (int)sizeof(string), s, s+sizeof(string));
	printf(" Str: allocated %d bytes, from 0x%p to 0x%p\n", (int)strlen(s->str)+1, s->str, s->str+strlen(s->str)+1 );

	printf(" str = '%s'\n", s->str);
	printf(" length = '%lu'\n", s->length);
	printf(" strlen = '%d'\n", (int)strlen(s->str));

}


int main(){

	string* s = string_new("Hello World!");
	s->print(s);

	printf("The last character is '%c'\n", s->getc(s,-1));

	printf(" -> Insertion:\n");
	s->insert(s, " I've just inserted this sentence at the end.", -1);
	s->append(s, " But you can simply append too.");
	s->print(s);

	printf(" -> Deletion:\n");
	s->erase(s, 0, 12);
	s->print(s);

	printf(" -> Slicing:\n");
	s->slice(s, 20, 33);
	s->print(s);

	printf(" -> Clearing the string:\n");
	s->clear(s);
	s->print(s);

	s->free(s);

	return 0;
}
