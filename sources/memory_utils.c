/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/29 11:52:07 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_memory 		*memory_by_type(t_data *data, enum e_types type)
{
	if (type == TINY)
		return (&data->mem_tiny);
	else if (type == SMALL)
		return (&data->mem_small);
	else
		return (&data->mem_large);
}

void 			initialize_memory(t_memory *mem, enum e_types type, size_t size)
{
	unsigned int	pagesize;

	pagesize = type == LARGE ? LARGE_SIZE(size) : page_size(type);
	mem->type = type;
	initialize_page(&mem->page, 0, pagesize);
}
