

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_IMPLEMENTATION
#include "string.h"



int main(){

	string *str = string_new("Hello, World!");
	str->print(str);
	printf("%c\n", str->getc(str,-1));
	printf("%s\n", str->at(str,-1));

	str->insert(str, "CHEESE! ", 0);
	str->print(str);

	str->insert(str, " What a wonderful morning. ", str->length);
	str->print(str);

	str->erase(str, 0, str->length+1);
	str->print(str);

	str->free(str);

	return 0;
}
