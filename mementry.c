#include "mementry.h"

// Memory space
static char myblock[memSize];

// Make head node
static MemEntry head;

// Custom malloc function
void *mymalloc(size_t size, char *file, size_t line)
{
	// Make newblock and traversal node
	MemEntry current, newblock;

	// Initialize
	if(!head)
	{
		printf("\n");

		// Make myblock into a mementry
		head = (MemEntry) myblock;

		// Set prev & next to 0
		head->prev = head->next = 0;

		// Allocate enough space for the head node
		head->size = memSize - sizeof(struct mementry);

		// Set it as a free block
		head->isFree = 1;
	}

	// Point to head
	current = head;

	do
	{
		//Traverse to find free node
		while(!current->isFree)
			current = current->next;

		// Try to merge blocks
		if(current->next != NULL && current->next->isFree)
			merge(current, size);

		// Space available, no need to make new block
		if(current->next != 0 && current->size >= size)
		{
			current->isFree = 0;
			printf(" Allocated memory:\t%p (%zu)\n", current, current->size);
			return (void *) current + sizeof(struct mementry);
		}
		else if(current->size >= size + sizeof(struct mementry))
		{
			// Add to end
			newblock = (MemEntry) ((void *)current + sizeof(struct mementry) + size);
			newblock->prev = current;
			newblock->next = current->next;
			newblock->size = current->size - sizeof(struct mementry) - size;
			newblock->isFree = 1;

			// Adjust links
			current->next = newblock;
			current->size = size;
			current->isFree = 0;

			printf(" Allocated memory:\t%p (%zu)\n", current, current->size);

			if(newblock->size <= sizeof(struct mementry))
				printf(" Space remaining:\t%zu\n", newblock->size);
			else
				printf(" Space remaining:\t%zu\n", newblock->size - sizeof(struct mementry));

			return (void *) current + sizeof(struct mementry);
		}

		// Go to next node if it never enters above statements
		current = current->next;

	} while(current != NULL);

	printf(" ** Error allocating space in %s:%zu\n", file, line);
	return NULL;
}

// Custom free function
void myfree(void *ptr, char *file, size_t line)
{
	MemEntry current = head;

	if(ptr != NULL)
	{
		// Get address of the pointer passed
		ptr = (MemEntry) (ptr - sizeof(struct mementry));

		// Traverse the memory to find address
		while(current != NULL && current != ptr)
			current = current->next;

		if(current != NULL)
		{
			// Check the address
			if(current->isFree)
			{
				printf(" ** Memory already freed in %s:%zu\n", file, line);
				return;
			}
			else if(current == ptr)
			{
				current->isFree = 1;
				printf(" Memory freed:\t\t%p (%zu)\n", current, current->size);
			 	return;
			}
		}
	}

	printf(" ** Error freeing memory in %s:%zu\n", file, line);
}

// Merge blocks
void merge(MemEntry current, size_t size)
{
	if(current->next != NULL && current->next->isFree)
	{
		//Merge adjacent nodes
		current->size += current->next->size;
		current->next = current->next->next;
	 	current->isFree = 1;

		// If size being asked for is bigger then merged block
		if(current->size < size)
			merge(current->next, size);
	}
}
