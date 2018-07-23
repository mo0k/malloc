/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/23 16:22:33 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*malloc(size_t size)
{
	t_memory			*mem;
	enum e_types		type;

	DEBUGV("%s call malloc(%d)\n"
				, get_progname("_")
				, size);
	type = typ_blk(size);
	mem = memory_by_type(&g_data, type);
	if (mem->page == NULL)
		initialize_memory(mem, type, size);
	pthread_mutex_lock(&g_mutex);
	(type == LARGE) ? manage_large(mem->page, size)
					: manage_tiny_small(mem->page, size, mem->type);
	pthread_mutex_unlock(&g_mutex);
	return (g_data.mem_ret);
}
