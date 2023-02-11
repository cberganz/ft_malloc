/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:11:52 by cberganz          #+#    #+#             */
/*   Updated: 2023/02/10 23:50:41 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h> 

# define ALIGNEMENT	sizeof(size_t)
# define ALIGN(X)	(X-1)/ALIGNEMENT*ALIGNEMENT+ALIGNEMENT

typedef struct s_block	*block;
typedef struct s_heap	*heap;

struct s_block
{
	size_t	size;
	block	prev;
	block	next;
	bool	free;
	void	*ptr;		/* Pointer to data field */
	char	data[1];	/* Allows byte by byte pointer arithmetic */
};

struct s_heap
{
	size_t	size;
	size_t	free_space;
	size_t	largest_free;
	heap	prev;
	heap	next;
};

extern heap mem[3];

# define BLOCK_HEAD_SIZE	sizeof(struct s_block)
# define BLOCK_SHIFT(p)		((void *)p + BLOCK_HEAD_SIZE)
# define HEAP_HEAD_SIZE		sizeof(struct s_heap)
# define HEAP_SHIFT(p)		((void *)p + HEAP_HEAD_SIZE)

# define TINY_MAX_ALLOC		128
# define TINY_HEAP_FACTOR	100
# define TINY_HEAP_SIZE		(HEAP_HEAD_SIZE + (TINY_MAX_ALLOC + BLOCK_HEAD_SIZE) * TINY_HEAP_FACTOR - 1)	\
							/ getpagesize() * getpagesize() + getpagesize()
# define SMALL_MAX_ALLOC	512
# define SMALL_HEAP_FACTOR	100
# define SMALL_HEAP_SIZE	(HEAP_HEAD_SIZE + (SMALL_MAX_ALLOC + BLOCK_HEAD_SIZE) * SMALL_HEAP_FACTOR - 1)	\
							/ getpagesize() * getpagesize() + getpagesize()

# define HEAP_SIZE(size)		size <= TINY_MAX_ALLOC ? TINY_HEAP_SIZE : size <= SMALL_MAX_ALLOC ? SMALL_HEAP_SIZE : size;
# define HEAP_MAX_ALLOC(size)	size <= TINY_MAX_ALLOC ? TINY_MAX_ALLOC : size <= SMALL_MAX_ALLOC ? SMALL_MAX_ALLOC : 0;

void *malloc(size_t size);

#endif // MALLOC_H
