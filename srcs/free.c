#include <malloc.h>

t_block fusion(t_block b)
{
	if (b->next && b->next->free)
	{
		b->size += b->next->size + BLOCK_SIZE;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
	}
	return b;
}

t_block get_block(void *p)
{
	char *c = p;
	return p = c -= BLOCK_SIZE;
}

bool valid_for_free(void *p)
{
	return mem && p == get_block(p)->ptr;
}

void free(void *p)
{
	if (!valid_for_free(p))
		return;
	t_block b = get_block(p);
	b->free = true;
	if (b->prev && b->prev->free)
		b = fusion(b->prev);
	if (b->next)
		fusion(b);
	else
	{
		if (b->prev)
			b->prev->next = NULL;
		else
			mem = NULL;
		munmap(b, b->size + sizeof(t_block));
	}
}
