#include "malloc.h"

heap mem[3] = { 0, 0, 0 };

# define ZONE(size) mem[(size > TINY_MAX_ALLOC) + (size > SMALL_MAX_ALLOC)]

block get_matching_block(size_t size)
{
	heap	h;
	block	b;

	h = ZONE(size);
	while (h)
	{
		b = HEAP_SHIFT(h);
		while (b)
		{
			if (b->free && b->size >= size)
				return b;
			b = b->next;
		}
		h = h->next;
	}
	return NULL;
}

block new_heap(size_t size)
{
	heap	h;
	block	b;
	size_t	heap_size;

	heap_size = HEAP_SIZE(size);
	h = (heap)mmap(NULL,
				   heap_size,
				   PROT_READ | PROT_WRITE,
				   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (h == MAP_FAILED)
		return NULL;
	h->next = ZONE(size);
	if (h->next)
		h->next->prev = h;
	h->size = heap_size;
	h->free_space = heap_size - HEAP_HEAD_SIZE - BLOCK_HEAD_SIZE - size;
	h->largest_free = HEAP_MAX_ALLOC(size)
	ZONE(size) = h;
	b = HEAP_SHIFT(h);
	b->size = size;
	b->prev = NULL;
	b->next = NULL;
	b->free = false;
	b->ptr = b->data;
	return BLOCK_SHIFT(b);
}

void split_block(block b, size_t size)
{
	block new;
	new = (block)(b->data + size);
	new->size = b->size - size - BLOCK_HEAD_SIZE;
	new->next = b->next;
	new->free = true;
	b->size = size;
	b->next = new;
}

void *malloc(size_t size)
{
	block	b;

	size = ALIGN(size);
	if (ZONE(size) && size < SMALL_MAX_ALLOC)
	{
		b = get_matching_block(size);
		if (b)
		{
			if ((b->size - size) >= (BLOCK_HEAD_SIZE + 4))
				split_block(b, size);
			b->free = false;
		}
		else
			return new_heap(size);
	}
	else
		return new_heap(size);
	return b->data;
}
