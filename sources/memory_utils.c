/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 22:00:10 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_memory		*memory_by_type(t_data *data, enum e_types type)
{
	if (type == TINY)
		return (&data->mem_tiny);
	else if (type == SMALL)
		return (&data->mem_small);
	else
		return (&data->mem_large);
}

void			initialize_memory(t_memory *mem, enum e_types type, size_t size)
{
	unsigned int			pagesize;
	static pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

	(void)g_mutex;
	pagesize = type == LARGE ? LARGE_SIZE(size) : page_size(type);
	mem->type = type;
	initialize_page(&mem->page, 0, pagesize);
}
