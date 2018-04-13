/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 00:01:33 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/11 19:50:28 by mo0k             ###   ########.fr       */
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
	//OPEN_DEBUG();
	P_DEBUG_VARGS(LEVEL_1, "{LRED}FREE{EOC}\taddress:%p\n", ptr);
	//CLOSE_DEBUG();
	//return ;
	//P_DEBUG_VARGS(LEVEL_3, "\t\tSTART FREE ptr:%p\n", ptr);
	//t_memory	mem;
	t_free		free;
	//t_hdr_page	*page;
	//t_hdr_blk	*blk;

	if (ptr == 0)
	{
		P_DEBUG(LEVEL_3, "\t\tfree ptr == NULL\n");
		return ;
	}
	if (!(free.page = find_page(&g_data, ptr, &free.type)))
	{
		P_DEBUG(LEVEL_3, "\t\tfree page not found\n");
		return ;
	}
	if (free.type == LARGE)
	{
		//ft_printf("largeeeeeeeeee\n");
		del_page(free.page, LARGE);
		//show_alloc_mem();
		return ;
	}
	if (!(free.blk = find_blk(free.page, ptr)))
	{
		P_DEBUG(LEVEL_3, "\t\tfree no block found\n");
		return ;
	}
	create_free_blk(free.blk, free.page, free.type);
	show_alloc_mem();
}
