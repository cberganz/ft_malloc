#include "../includes/malloc.h"

static t_block mem = NULL;

t_block get_matching_block(t_block *last, size_t size)
{
	t_block	b = mem;
	while (b && !(b->free && b->size >= size))
	{
		*last = b;
		b = b->next;
	}
	return b;
}

t_block extend_heap(t_block last, size_t size)
{
	t_block	b = (t_block)mmap(NULL, size + BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (b == MAP_FAILED)
		return NULL;
	b->size = size;
	b->next = mem;
	if (last)
		last->next = b;
	b->free = false;
	return b;
}

void split_block(t_block b, size_t s)
{
	t_block new;
	new = (t_block)(b->data + s);
	new->size = b->size - s - BLOCK_SIZE;
	new->next = b->next;
	new->free = true;
	b->size = s;
	b->next = new;
}

void *malloc(size_t size)
{
	t_block	b, last;
	size_t	s;

	s = ALIGN(size);
	if (mem)
	{
		last = mem;
		b = get_matching_block(&last, s);
		if (b)
		{
			if ((b->size - s) >= (BLOCK_SIZE + 4))
				split_block(b, s);
			b->free = false;
		}
		else
		{
			b = extend_heap(last, s);
			if (!b)
				return NULL;
		}
	}
	else
	{
		b = extend_heap(NULL, s);
		if (!b)
			return NULL;
		mem = b;
	}
	return b->data;
}
