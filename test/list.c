
/*
#define LIST_IMPLEMENTATION
#include "../list.h"
*/

#include "../ulib.h"

struct test{
	int a,b,c;
	char s[99];
};

#include <stdio.h>

list* populate_list(list* l){
	list* r;

	int x = 99;
	r = l->append(l, TYPE_INT, &x);
	if(!r) return r;

	double y = 3.14159265;
	l->append(l, TYPE_DOUBLE, &y);
	if(!r) return r;

	float z = 1e5;
	l->append(l, TYPE_FLOAT, &z);
	if(!r) return r;

	char c = 'X';
	l->append(l, TYPE_CHAR, &c);
	if(!r) return r;

	l->append(l, TYPE_STR_20, "Hello World!");
	if(!r) return r;

	struct test t;
	t.a = 42;
	l->append(l, TYPE_OTHER+sizeof(t), &t);
	if(!r) return r;

	return l;
}


list* test_new_list(){
	list* l = list_new();
	if(!l){
		fprintf(stderr, "New list: FAILED\n");
		exit(1);
	}
	fprintf(stderr, "New list: PASSED\n");
	return l;
}

void test_append(list *l){
	if (!populate_list(l)){
		fprintf(stderr, "Append: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Append: PASSED\n");
}

void test_length(list *l){
	if(l->length(l) != 6){
		fprintf(stderr, "Length: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Length: PASSED\n");
}

void test_get(list* l){
	unsigned int len = l->length(l);
	unsigned int dtype, i;

	unsigned int dtype_expected[] = {
		TYPE_INT, TYPE_DOUBLE, TYPE_FLOAT,
		TYPE_CHAR, TYPE_STR_20, TYPE_OTHER
	};

	for(i=0; i!=len; ++i){
		void* obj = l->get(l, i, &dtype);
		if(obj && dtype == dtype_expected[i]) continue;
		fprintf(stderr, "Get: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Get: PASSED\n");
}

void test_set(list* l){
	unsigned int len = l->length(l);
	char *s = "There's a snake in my boot!";

	l->set(l, len-1, TYPE_STR_50, s);
	unsigned int dtype;
	char* data = l->get(l, len-1, &dtype);

	if(dtype != TYPE_STR_50 || ULIB_STRCMP(data, s) != 0){
		fprintf(stderr, "Set: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Set: PASSED\n");
}


void test_insert(list* l){

	int x = 123456, y = 420, z = 911, r = 0;
	list* lr = NULL;
	unsigned int len = l->length(l), dtype;

	/* Add in the middle */
	lr = l->insert(l, 3, TYPE_INT, &x);
	r = *(int*)l->get(l, 3, &dtype);
	if(!lr || dtype!=TYPE_INT || r!=x || l->length(l)!=len+1){
		fprintf(stderr, "Insert: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Insert middle: PASSED\n");

	/* Add at the head */
	lr = l->insert(l, 0, TYPE_INT, &y);
	r = *(int*)l->get(l, 0, &dtype);
	if(!lr || dtype!=TYPE_INT || r!=y || l->length(l)!=len+2){
		fprintf(stderr, "Insert: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Insert head: PASSED\n");

	/* Add at the end */
	lr = l->insert(l, l->length(l), TYPE_INT, &z);
	r = *(int*)l->get(l, l->length(l)-1, &dtype);
	if(!lr || dtype!=TYPE_INT || r!=z || l->length(l)!=len+3){
		fprintf(stderr, "Insert end: FAILED\n");
		if(!lr) printf("return ptr is NULL\n");
		if(!dtype!=TYPE_INT) printf("read type is not correct\n");
		if(r!=z) printf("value is not correct\n");
		if(l->length(l)!=len-3) printf("wrong length\n");
		exit(-1);
	}
	fprintf(stderr, "Insert end: PASSED\n");

	fprintf(stderr, "Insert: PASSED\n");
}

void test_list_integrity(list* l){
	unsigned int i, len = l->length(l);
	list_node* c = l->head;
	printf("\nLIST INTEGRITY TOOL\n");
	printf("i) prev->curr->next\n");
	printf("-------------------\n");
	for(i=0; i!=len; ++i){
		printf("%u) ", i);
		if(c->prev) printf("data");
		else printf("NULL");
		if(c) printf("<-data->");
		else printf("<-NULL->");
		if(c->next) printf("data");
		else printf("NULL");
		printf("\n");
		c = c->next;
	}
}

void test_remove(list* l){
	unsigned int len = l->length(l);
	l->remove(l, 4);
	l->remove(l, 0);
	l->remove(l, l->length(l)-1);
	l->remove(l, 10000);
	l->remove(l, -1);

	if(l->length(l) != len-3){
		fprintf(stderr, "Remove: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Remove: PASSED\n");
}

void test_pop(list* l){
	l->clear(l);
	l->pop(l);
	l->pop(l);
	if(l->length(l) != 0){
		fprintf(stderr, "Pop: FAILED\n");
		exit(-1);
	}
	fprintf(stderr, "Pop: PASSED\n");
}

int main(){
	printf("\n");

	list* l = test_new_list();

	test_append(l);
	test_length(l);
	test_get(l);
	test_set(l);
	test_insert(l);

	list__debug(l);

	test_remove(l);
	test_pop(l);
	test_list_integrity(l);
	
	printf("\n\n\n");
	list__debug(l);

	l->free(l);

	printf("\nDone!\n");
	return 0;
}
