/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 21:59:37 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void				join_blk(t_hdr_page *page, t_hdr_blk *free, \
											t_hdr_blk *next, t_hdr_blk *prev)
{
	if ((next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
		|| (prev && CHK_HEADER(prev, OFFSET_CHKM(HDR_BLK_SIZE))))
		kill_prog(CHECKSUM_CORRUPED, 16);
	if (!prev)
	{
		if (!next)
			page->free = 0;
		else
			next->fprev = 0;
		if (page->free == free)
			page->free = next;
	}
	else if (!next)
	{
		ISSUE(page, free);
	}
	else
	{
		if (page->free == free)
			page->free = prev;
		prev->fnext = OFFSET(next, prev);
		next->fprev = prev->fnext;
	}
}

static void				fix_header(t_hdr_page *page, t_hdr_blk *free, \
											t_hdr_blk *next, t_hdr_blk *prev)
{
	free->fnext = 0;
	free->fprev = 0;
	++page->nbr_blk;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
	(prev) ? SET_CHKM(prev, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
	SET_CHKM(free, OFFSET_CHKM(HDR_BLK_SIZE));
	SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	g_data.mem_ret = BEGIN_BLK(free);
}

int						manage_free_block(t_hdr_page *page, t_hdr_blk *free, \
														size_t blk_sz)
{
	t_hdr_blk *next;
	t_hdr_blk *prev;

	if (!free || !page)
		return (ERROR_ARGS);
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 14);
	while (free)
	{
		if (CHK_HEADER(free, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 15);
		if ((size_t)free->size >= blk_sz)
		{
			blk_sz += ((size_t)free->size > blk_sz) ? free->size - blk_sz : 0;
			next = NEXT_FBLK(free);
			prev = PREV_FBLK(free);
			join_blk(page, free, next, prev);
			free->size = blk_sz;
			fix_header(page, free, next, prev);
			return (FREE_USED);
		}
		else
			free = NEXT_FBLK(free);
	}
	return (FREE_NO_USED);
}
