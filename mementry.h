#ifndef MEMENTRY_H
#define MEMENTRY_H

#include <stdio.h>
#include <stdlib.h>

#define memSize 5000
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

struct mementry
{
	// Used to link nodes
	struct mementry *prev;
	struct mementry *next;

	// Hold size of block
	size_t size;

	// Check if block is free
	// 0 = not free | 1 = free
	short isFree;
};
typedef struct mementry *MemEntry;

// Methods
void *mymalloc(size_t, char *, size_t);
void myfree(void *, char *, size_t);

void merge(MemEntry, size_t);

#endif
