/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:19:13 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/23 16:50:47 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		display_tiny_small(t_hdr_page *page)
{
	t_hdr_blk	*free;
	t_hdr_blk	*blk;

	while (page)
	{
		if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 1);
		blk = FIRST_BLK(page);
		free = page->free;
		while (blk && blk->size)
		{
			if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
				kill_prog(CHECKSUM_CORRUPED, 1);
			if (free && blk == free &&
				ft_printf("\e[91mF\e[39m %X - %X % 5d octets\n"
					, BEGIN_BLK(blk), END_BLK(blk), blk->size))
				free = NEXT_FBLK(free);
			else
				ft_printf("\e[92mM\e[39m %X - %X % 5d octets\n"
					, BEGIN_BLK(blk), END_BLK(blk), blk->size);
			blk = NEXT_BLK(blk);
		}
		page = NEXT_PAGE(page);
	}
}

static void		display_large(t_hdr_page *page)
{
	t_hdr_blk	*blk;

	while (page)
	{
		if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 21);
		blk = FIRST_BLK(page);
		if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 22);
		ft_printf("\e[92mM\e[39m %p - %p % 5d octets\n"
							, BEGIN_BLK(blk), END_BLK(blk), blk->size);
		page = NEXT_PAGE(page);
	}
}

void			show_alloc_mem(void)
{
	if (g_data.mem_tiny.page)
	{
		ft_printf("TINY:%p\n", g_data.mem_tiny.page);
		display_tiny_small(g_data.mem_tiny.page);
	}
	if (g_data.mem_small.page)
	{
		ft_printf("SMALL:%p\n", g_data.mem_small.page);
		display_tiny_small(g_data.mem_small.page);
	}
	if (g_data.mem_large.page)
	{
		ft_printf("LARGE:%p\n", g_data.mem_large.page);
		display_large(g_data.mem_large.page);
	}
	ft_printf("\n");
}
