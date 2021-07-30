


/*
#define ULIB_DEBUG
*/
#define STRING_IMPLEMENTATION
#include "../string.h"

#include <stdio.h>
#include <string.h>


void string_debug(string* s){
	printf("\n\n\n DEBUG String\n");

	printf(" Allocated %d bytes, from 0x%p to 0x%p\n", (int)sizeof(string), s, s+sizeof(string));
	printf(" Str: allocated %d bytes, from 0x%p to 0x%p\n", (int)strlen(s->str)+1, s->str, s->str+strlen(s->str)+1 );

	printf(" str = '%s'\n", s->str);
	printf(" length = '%u'\n", (unsigned int)s->length(s));
	printf(" strlen = '%d'\n", (int)strlen(s->str));
}


void test_getc(string* s){
	if(s->getc(s,0) != s->str[0]){
		ULIB_FPRINTF(stderr, "Getc: FAILED (0)\n");
		exit(1);
	}
	if(s->getc(s,-1) != s->str[s->length(s)-1]){
		ULIB_FPRINTF(stderr, "Getc: FAILED (-1)\n");
		exit(1);
	}
	ULIB_FPRINTF(stderr, "Getc: PASSED\n");
}

void test_insert(string* s){
	unsigned int len = s->length(s);
	string* r = NULL;

	r = s->insert(s, "INSERT", -1);
	if(!r || s->length(s) != len + ULIB_STRLEN("INSERT")){
		ULIB_FPRINTF(stderr, "Insert: FAILED\n");
		exit(1);
	}
	if(ULIB_STRCMP(s->str+len, "INSERT")!=0){
		ULIB_FPRINTF(stderr, "Insert: FAILED\n");
		exit(1);	
	}
	len = s->length(s);
	
	r = s->append(s, "-TEST");
	if(!r || s->length(s) != len + ULIB_STRLEN("-TEST")){
		ULIB_FPRINTF(stderr, "Append: FAILED\n");
		exit(1);
	}
	if(ULIB_STRCMP(s->str+len, "-TEST")!=0){
		ULIB_FPRINTF(stderr, "Append: FAILED\n");
		exit(1);
	}
	ULIB_FPRINTF(stderr, "Insert: PASSED\n");
}

void test_delete(string* s){
	string* r = NULL;
	unsigned int len = s->length(s);
	
	r = s->erase(s, 0, 5);
	if(!r || s->length(s) != len-5){
		ULIB_FPRINTF(stderr, "Delete: FAILED (0,5b)\n");
		exit(1);
	}

	len = s->length(s);
	r = s->erase(s, -6, 5);
	if(!r || s->length(s) != len-5){
		ULIB_FPRINTF(stderr, "Delete: FAILED (-6, 5b)\n");
		exit(1);
	}
	
	ULIB_FPRINTF(stderr, "Delete: PASSED\n");
}

void test_slice(string* s){
	string* r = NULL;
	if(s->length(s) < 21) return;

	r = s->slice(s, 10, 20);
	if(!r || s->length(s) != 20-10){
		ULIB_FPRINTF(stderr, "Slice: FAILED (10,20)\n");
		exit(1);
	}
	
	r = s->slice(s, -10, -7);
	if(!r || s->length(s) != 10-7){
		ULIB_FPRINTF(stderr, "Slice: FAILED (-10,-7)\n");
		exit(1);
	}

	ULIB_FPRINTF(stderr, "Slice: PASSED\n");
}

void test_clear(string* s){
	string* r = NULL;
	r = s->clear(s);
	if(!r || s->length(s) != 0){
		ULIB_FPRINTF(stderr, "Clear: FAILED\n");
		exit(1);
	}
	ULIB_FPRINTF(stderr, "Clear: PASSED\n");
}

void test_substr(string* s){
	string* r = NULL;
	/* re-filling string */
	s->clear(s);
	s->append(s, "Look again at that dot. That's here. That's home. That's us.");

	r = s->substr(s, 0, 4);
	if(!r || ULIB_STRCMP(r->str, "Look") != 0){
		ULIB_FPRINTF(stderr, "Substr: FAILED\n");
		exit(1);
	}
	r->free(r);
	ULIB_FPRINTF(stderr, "Substr: PASSED\n");
}

string* test_new(){
	string* s = NULL;
	char buff[200] = {0};

	s = string_new(NULL);
	if(!s || s->length(s) != 0){
		ULIB_FPRINTF(stderr, "New: FAILED (null)\n");
		if(s) s->free(s);
		exit(1);
	}
	s->free(s);

	s = string_new("Hello %% World! %d %.3f %.8g %10s 0x%X", 10, 3.1415f, 3.14159265, "cheese", 0xFF);
	ULIB_SPRINTF(buff, "Hello %% World! %d %.3f %.8g %10s 0x%X", 10, 3.1415f, 3.14159265, "cheese", 0xFF);
	if(!s || ULIB_STRCMP(s->str,buff) != 0){
		ULIB_FPRINTF(stderr, "New: FAILED (fmt)\n");
		if(s) s->free(s);
		exit(1);
	}
	
	ULIB_FPRINTF(stderr, "New: PASSED\n");
	return s;
}


int main(){

	string*s = test_new();
	
	test_getc(s);
	test_insert(s);
	test_delete(s);
	test_slice(s);
	test_clear(s);
	test_substr(s);

	s->free(s);

	ULIB_PRINTF("Done!");
	return 0;
}
