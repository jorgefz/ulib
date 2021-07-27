

/*

	####################
	#      List.h      #
	####################

	Doubly linked list implementation in C89.

	Objects
	-------

	list

	list_node


	Methods
	-------
	new_list()
	list->begin()
	list->end()
	list->next()
	list->prev()
	list->empty()
	list->length()
	list->append()

	To-Do
	list->insert() : Generalizes append
	list->


*/


#ifndef LIST_H
#define LIST_H


#ifndef TYPES_IMPLEMENTATION
#define TYPES_IMPLEMENTATION
#include "types.h" /* types.h already includes defs.h */
#endif

struct list__node_struct {
	struct list__node_struct* next;
	struct list__node_struct* prev;
	unsigned int type, size;
	void* data;
};
typedef struct list__node_struct list_node;

struct list__methods_struct {
	list_node* curr;
	list_node* head;
	/* Methods */
	unsigned int (*length)(struct list__methods_struct*);
	list_node* (*begin)(struct list__methods_struct*);
	list_node* (*end)(struct list__methods_struct*);
	list_node* (*next)(struct list__methods_struct*);
	list_node* (*prev)(struct list__methods_struct*);
	int (*empty)(struct list__methods_struct*);
	unsigned int (*bytes)(struct list__methods_struct*);
	struct list__methods_struct* (*append)(struct list__methods_struct*, unsigned int, void*);
};
typedef struct list__methods_struct list;



/* Function Definitions */

list* list_new();

unsigned int list__length(list* lst);
list_node* list__begin(list* lst);
list_node* list__end(list* lst);
list_node* list__next(list* lst);
list_node* list__prev(list* lst);
int list__empty(list* lst);
unsigned int list__bytes(list* lst);

list* list__init_head(list* lst, unsigned int type, void* data);

list* list__append(list* lst, unsigned int type, void* data);

/*
list* list__insert(list* lst, unsigned int where, int type, void* data);
list* list__set(list* lst, unsigned int where, int type, void* data);
void* list__get(list* lst, unsigned int where, int* ret_type);

list* list__is_empty(list* lst);

*/

void list__free(list* lst);

void list__debug(list* lst);

#endif /* LIST_H */



#ifdef LIST_IMPLEMENTATION

list* list_new(){
	list* lst = ULIB_MALLOC(sizeof(list));
	if(!lst) return NULL;

	/* Start with no nodes */
	lst->head = NULL;
	lst->curr = NULL;

	/* Function pointers */
	lst->begin = list__begin;
	lst->end = list__end;
	lst->next = list__next;
	lst->prev = list__prev;
	lst->length = list__length;
	lst->empty = list__empty;
	lst->bytes = list__bytes;
	lst->append = list__append;

	return lst;
}

/* Returns the first item on the list */
list_node* list__begin(list* lst){
	return lst->head;
}

/* Returns the last item in the list */
list_node* list__end(list* lst){
	if (lst->head == NULL) return NULL;
	while(lst->curr->next) lst->curr = lst->curr->next;
	return lst->curr;
}

list_node* list__next(list* lst){
	if(lst->curr->next == NULL) return NULL;
	lst->curr = lst->curr->next;
	return lst->curr;
}

list_node* list__prev(list* lst){
	if(lst->curr->prev == NULL) return NULL;
	lst->curr = lst->curr->prev;
	return lst->curr;
}

unsigned int list__length(list* lst){
	if (lst->head == NULL) return 0;
	unsigned int i = 0;
	lst->curr = lst->begin(lst);
	while(lst->curr){
		lst->curr = lst->curr->next;
		i++;
	}
	lst->curr = lst->head;
	return i;
}

int list__empty(list* lst){
	return lst->head ? 0 : 1;
}

unsigned int list__bytes(list* lst){
	unsigned int size = sizeof(list);
	list_node *n = lst->head;
	while(n){
		size += sizeof(list_node);
		size += n->size;
		n = n->next;
	}
	return size;
}

list* list__init_head(list* lst, unsigned int type, void* data){
	/* allocate node */
	list_node* new_node = ULIB_MALLOC(sizeof(list_node));
	if(!new_node) return NULL;

	/* linking */
	new_node->prev = NULL;
	new_node->next = NULL;
	lst->head = new_node;
	lst->curr = lst->head;

	/* get size from bytes */
	new_node->type = type;
	if(type > TYPE_OTHER) new_node->size = type - TYPE_OTHER;
	else new_node->size = types__sizes[type];

	/* save data */
	new_node->data = ULIB_MALLOC(new_node->size);
	if(!new_node->data){
		free(new_node);
		return NULL;
	}
	ULIB_MEMCPY(new_node->data, data, new_node->size);
	return lst;
}


list* list__append(list* lst, unsigned int type, void* data){

	/* seek last item */
	lst->curr = lst->end(lst);

	/* allocate new item */
	list_node* new_node = ULIB_MALLOC(sizeof(list_node));
	if(!new_node) return NULL;

	/* linking */
	new_node->prev = lst->curr;
	new_node->next = NULL;
	if (lst->head == NULL){
		lst->head = new_node;
		lst->curr = lst->head;
	}
	else lst->curr->next = new_node;

	/* writing data */
	new_node->type = type;
	if(type > TYPE_OTHER){
		new_node->size = type - TYPE_OTHER;
		new_node->type = TYPE_OTHER;
	}
	else new_node->size = types__sizes[type];
	new_node->data = ULIB_MALLOC(new_node->size);
	if(!new_node->data){
		free(new_node);
		return NULL;
	}
	ULIB_MEMCPY(new_node->data, data, new_node->size);
	return lst;
}


void list__debug(list* lst){
	ULIB_PRINTF(" --- LIST DEBUG ---\n");
	ULIB_PRINTF(" Size: %u bytes\n", (unsigned int)sizeof(list));
	unsigned int i, len=lst->length(lst);
	ULIB_PRINTF(" Length: %u items\n", len);
	lst->curr = lst->head;
	for(i=0; i!=len; ++i){
		ULIB_PRINTF(" %u) %s -> ", i, types__names[lst->curr->type]);
		types__print(lst->curr->type, lst->curr->data);
		printf("\n");
		lst->curr = lst->curr->next;
	}
	lst->curr = lst->head;
	return;
}

void list__free(list* lst){
	if (lst->head == NULL){
		free(lst);
		return;
	}
	lst->curr = lst->end(lst);
	while(lst->curr->prev){
		free(lst->curr->data);
		lst->curr = lst->curr->prev;
		free(lst->curr->next);
	}
	free(lst->curr);
	free(lst);
}

#endif /* LIST_IMPLEMENTATION */