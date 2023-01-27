/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:11:52 by cberganz          #+#    #+#             */
/*   Updated: 2023/01/27 13:12:00 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/mman.h>

# define ALIGNEMENT sizeof(size_t)
# define ALIGN(X) (X-1)/ALIGNEMENT*ALIGNEMENT+ALIGNEMENT

# define BLOCK_SIZE sizeof(struct s_block)

typedef struct s_block* t_block;

struct s_block
{
	size_t	size;
	t_block	next;
	bool	free;
	char	data[1];
};

void *malloc(size_t size);

#endif // MALLOC_H
