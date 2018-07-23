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

	P_DEBUG_FILE_VARGS(LEVEL_1
						, "%s call free(%p)\n"
						, get_progname("_")
						, ptr);
	if (ptr == 0)
		return ;
	if (!(free.page = find_page(&g_data, ptr, &free.type)))
		return ;
	if (free.type == LARGE)
	{
		del_page(free.page, LARGE);
		return ;
	}
	if (!(free.blk = find_blk(free.page, ptr)))
		return ;
	create_free_blk(free.blk, free.page, free.type);
}
