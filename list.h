#ifndef LIST_H
#define LIST_H

struct __attribute__((__packed__)) list__struct {
	struct list__struct* _next_ptr;
	struct list__struct* _prev_ptr;
	int size;
	void* data;
};
typedef struct list__struct list;

#endif /* LIST_H */



#ifdef LIST_IMPLEMENTATION

#endif /* LIST_IMPLEMENTATION */