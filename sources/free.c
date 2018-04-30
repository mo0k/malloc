/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 00:01:33 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/29 23:29:17 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

typedef struct	s_free
{
	t_hdr_page		*page;
	t_hdr_blk		*blk;
	enum e_types 	type;
}					t_free;

void	free(void *ptr)
{
	P_DEBUG_FILE_VARGS(LEVEL_1, "%s call free(%p)\n", get_progname("_"), ptr);
	t_free		free;

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
