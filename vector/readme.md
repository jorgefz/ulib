
# Vector.h

*Useful functions for the C Programming Language*

Includes a new structure, vector, that allows
to create dynamic arrays that can be resized easily
and hold any data type or structure.

## Vector functions
### Vector creation
Initialises a new vector with members of size 'bytes' and returns a pointer to it.
```c
vector *vnew(size_t bytes);
```

### Vector deletion
Frees the allocated memory of a vector 'v'.
```c
void vfree(vector *v);
```

### Vector size
Retrieves the number of members in an input vector 'v'.
```c
size_t vsize(vector *v);
```

### Vector data type size
Retrieves the size in bytes of the data type of individual members of a vector 'v'.
```c
size_t vdtype(vector *v);
```

### Insert member
Inserts a new vector member 'ptr' at index 'i'.
It returns a pointer to the input vector 'v',
and NULL on fail.
```c
vector *vinsert(vector *v, size_t j, void *new);
```

### Remove member
Removes a member from a vector 'v' at index 'i'.
```c
vector *vdelete(vector *v, size_t i);
```

### Resize
Changes the size of a vector 'v' to an input value 's'. If the size is increased, new empty members are added. On the other hand, if the size is reduced, members at the end of the vector are lost. 
```c
vector *vresize(vector *v, size_t s);
```

### Fill
Fills the whole vector with an input member 'ptr'. Existing member data is overwritten.
```c
vector *vfill(vector *v, void *ptr);
```