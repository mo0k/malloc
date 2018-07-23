/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 00:01:33 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 23:10:47 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free(void *ptr)
{
	t_free		free;

	DEBUGV("%s call free(%p)\n", get_progname("_"), ptr);
	pthread_mutex_lock(&g_mutex);
	if (ptr == 0)
		return ;
	if (!(free.page = find_page(&g_data, ptr, &free.type)))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (free.type == LARGE)
	{
		del_page(free.page, LARGE);
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (!(free.blk = find_blk(free.page, ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	create_free_blk(free.blk, free.page, free.type);
	pthread_mutex_unlock(&g_mutex);
}
