
/*
#define LIST_IMPLEMENTATION
#include "../list.h"
*/

#include "../ulib.h"

struct test{
	int a;
};

#include <stdio.h>

int main(){

	list* l = list_new();

	int x = 99;
	l->append(l, TYPE_INT, &x);

	double y = 3.14159265;
	l->append(l, TYPE_DOUBLE, &y);

	float z = 3.14159265;
	l->append(l, TYPE_FLOAT, &z);

	char c = 'X';
	l->append(l, TYPE_CHAR, &c);

	char* s = "Hello World!";
	l->append(l, TYPE_STR_20, s);

	struct test t;
	t.a = 42;
	printf("Test structure has size %d\n", (int)sizeof(struct test));

	l->append(l, TYPE_OTHER+sizeof(t), &t);

	list__debug(l);

	struct test* t2 = (struct test*)(l->end(l)->data);
	printf("Recovered value = %d\n", t2->a );

	printf("Total size is %u bytes\n", l->bytes(l));


	list__free(l);

	return 0;
}
