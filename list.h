

/*

	####################
	#      List.h      #
	####################

	Doubly linked list implementation in C89.

	Structs
	-------

	list -> head, curr 

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
	list->insert()
	list->pop()
	list->remove()
	list->clear()

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

typedef struct list__node_struct list_node;
struct list__node_struct {
	list_node* next;
	list_node* prev;
	unsigned int type, size;
	void* data;
};

typedef struct list__methods_struct list;
struct list__methods_struct {
	list_node* curr;
	list_node* head;
	/* Methods */
	unsigned int (*length) (list*);
	list_node*   (*begin)  (list*);
	list_node*   (*end)    (list*);
	list_node*   (*next)   (list*);
	list_node*   (*prev)   (list*);
	list_node*   (*at)     (list*, unsigned int);
	list_node*   (*set)    (list*, unsigned int, unsigned int, void*);
	void*        (*get)    (list*, unsigned int, unsigned int*);
	int          (*empty)  (list*);
	unsigned int (*bytes)  (list*);
	list*        (*append) (list*, unsigned int, void*);
	list*        (*insert) (list*, unsigned int, unsigned int, void*);
	list*        (*pop)    (list*);
	list*        (*remove) (list*, unsigned int);
	list*        (*clear)  (list*);
	void         (*free)   (list*);
};


/* Function Definitions */

list* list_new();

unsigned int list__length(list* lst);
list_node* list__begin(list* lst);
list_node* list__end(list* lst);
list_node* list__next(list* lst);
list_node* list__prev(list* lst);
list_node* list__at(list* lst, unsigned int where);
int list__empty(list* lst);
unsigned int list__bytes(list* lst);
list_node* list__set(struct list__methods_struct* lst, unsigned int where, unsigned int type, void* data);
void* list__get(struct list__methods_struct* lst, unsigned int where, unsigned int* ret_type);
list* list__append(list* lst, unsigned int type, void* data);
list* list__insert(list* lst, unsigned int where, unsigned int type, void* data);
list* list__pop(list* lst);
list* list__remove(list* lst, unsigned int where);
list* list__clear(list* lst);

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
	lst->at = list__at;
	lst->set = list__set;
	lst->get = list__get;
	lst->bytes = list__bytes;
	lst->append = list__append;
	lst->insert = list__insert;
	lst->pop = list__pop;
	lst->remove = list__remove;
	lst->clear = list__clear;
	lst->free = list__free;
	return lst;
}

/* Returns the first item on the list */
list_node* list__begin(list* lst){
	lst->curr = lst->head;
	return lst->head;
}

/* Returns the last item in the list */
list_node* list__end(list* lst){
	list_node* c = lst->head;
	if(!c) return NULL;
	while(c->next) c = c->next;
	lst->curr = c;
	return c;
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

list_node* list__at(list* lst, unsigned int where){
	unsigned int i=0;
	list_node* c = lst->head;
	while(i!=where && c!=NULL){
		c = c->next;
		i++;
	}
	return c;
}

unsigned int list__length(list* lst){
	if (lst->head == NULL) return 0;
	unsigned int i = 0;
	list_node* b = lst->begin(lst);
	while(b){
		b = b->next;
		i++;
	}
	lst->curr = lst->head; /* REMOVE */
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

list_node* list__set(struct list__methods_struct* lst, unsigned int where, unsigned int type, void* data){
	/* seek item */
	list_node* n = lst->at(lst, where);
	if(!n) return NULL;
	/* calculate memory */
	unsigned int size;
	if(type > TYPE_OTHER){
		size = type - TYPE_OTHER;
		type = TYPE_OTHER;
	}
	else size = types__sizes[type];
	/* request new memory */
	void* ndata = ULIB_REALLOC(n->data, size);
	if(!ndata) return NULL;
	/* save new data in node */
	n->data = ndata;
	n->size = size;
	n->type = type;
	ULIB_MEMCPY(n->data, data, n->size);
	return n;
}

void* list__get(struct list__methods_struct* lst, unsigned int where, unsigned int* ret_type){
	list_node* n = lst->at(lst, where);
	if(!n) return NULL;
	*ret_type = n->type;
	return n->data;
}

list* list__append(list* lst, unsigned int type, void* data){	
	/* list->insert at the end of the list */
	unsigned int len = lst->length(lst);
	return lst->insert(lst, len, type, data);
}


list* list__insert(list* lst, unsigned int where, unsigned int type, void* data){
	/* seeking neighbour nodes */
	list_node* n = lst->at(lst, where);
	list_node *p;
	if(n) p = n->prev;
	else  p = lst->end(lst);
	/* creating new node */
	list_node* c = ULIB_MALLOC(sizeof(list_node));
	if(!c) return NULL;
	/* re-linking */
	c->next = n;
	c->prev = p;
	if(p) p->next = c;
	else lst->head = c;
	if(n) n->prev = c;
	/* saving data */
	c->data = NULL;
	if( lst->set(lst,where,type,data) == NULL ) return NULL;
	return lst;
}


list* list__pop(list* lst){
	return list__remove(lst, lst->length(lst)-1);
}

list* list__remove(list* lst, unsigned int where){
	/* seek item */
	list_node* c = lst->at(lst, where);
	if(!c) return NULL;
	/* unlink */
	list_node *p = c->prev;
	list_node *n = c->next;
	if(p) p->next = n;
	else lst->head = n;
	if(n) n->prev = p;

	free(c->data);
	free(c);
	return lst;
}

list* list__clear(list* lst){
	while(lst->head) lst->pop(lst);
	return lst;
}


void list__debug(list* lst){
	ULIB_PRINTF(" ----- LIST DEBUG -----\n");
	ULIB_PRINTF(" Size: %u bytes\n", lst->bytes(lst));
	unsigned int i=0, len=lst->length(lst);
	ULIB_PRINTF(" Length: %u items\n", len);
	list_node* c = lst->head;
	while(c){
		ULIB_PRINTF(" %03u) %13s -> ", i++, types__names[c->type]);
		types__print(c->type, c->data);
		ULIB_PRINTF("\n");
		c = c->next;
	}
	ULIB_PRINTF(" ----------------------\n");
	return;
}

void list__free(list* lst){
	if (lst->head == NULL){
		ULIB_FREE(lst);
		return;
	}
	list_node* c = lst->end(lst);
	while(c->prev){
		ULIB_FREE(c->data);
		c = c->prev;
		ULIB_FREE(c->next);
	}
	ULIB_FREE(c);
	ULIB_FREE(lst);
}

#endif /* LIST_IMPLEMENTATION */