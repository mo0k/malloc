/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:19:13 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/09 21:37:28 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		display_tiny_small(t_hdr_page *page)
{
	t_hdr_blk	*free;
	t_hdr_blk	*blk;

	while (page)
	{
		//ft_printf("page:%p\n", page);
		if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 1);
		blk = FIRST_BLK(page);
		free = FIRST_FREE(page);
		//while (blk && blk->size)
		//ft_printf("last_blk:%p\n", LAST_BLK(page));
		//display_hdr_blk(LAST_BLK(page));
		while (blk && blk->size)
		{
			//ft_printf("debut boucle blk:%p\n",blk);
			if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
				kill_prog(CHECKSUM_CORRUPED, 1);
			if (free && blk == free)
			{
				ft_printf("\e[91mF\e[39m %p - %p % 5d octets\talign:%hd\n", BEGIN_BLK(blk), END_BLK(blk), blk->size, blk->align);
				free = NEXT_FBLK(free);
			}
			else
				ft_printf("\e[92mM\e[39m %p - %p % 5d octets\talign:%hd\n", BEGIN_BLK(blk), END_BLK(blk), blk->size, blk->align);
			blk = NEXT_BLK(blk);
			//ft_printf("next blk:%p\n", blk);
		}
		ft_printf("\n");
		page = NEXT_PAGE(page);
	}
}

static void		display_large(t_hdr_page *page)
{
	t_hdr_blk	*blk;

	while (page)
	{
		//ft_printf("show_alloc_mem() page:%p\n", page);
		if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 21);
		//ft_printf("apre chk page\n");
		blk = FIRST_BLK(page);
		if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 22);
		ft_printf("\e[92mM\e[39m %p - %p % 5d octets\n", BEGIN_BLK(blk), END_BLK(blk), blk->size);
		page = NEXT_PAGE(page);
		//ft_printf("show_alloc_mem() page->next:%p\n", page);

	}
}

void			show_alloc_mem(void)
{
	P_DEBUG(LEVEL_3, "\t\tshow show_alloc_mem\n");
	if (g_data.mem_tiny.page && ft_printf("TINY:%p\n", g_data.mem_tiny.page))
	{
		display_tiny_small(g_data.mem_tiny.page);	
	}
	if (g_data.mem_small.page && ft_printf("SMALL:\n"))
	{
		display_tiny_small(g_data.mem_small.page);	
	}
	if (g_data.mem_large.page && ft_printf("LARGE:\n"))
	{
		display_large(g_data.mem_large.page);	
	}
	ft_printf("\n");
}