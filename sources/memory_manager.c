/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 23:25:30 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"


//static void		join_blk()

int				manage_free_block(t_hdr_page *page, t_hdr_blk *free, size_t blk_size, size_t min_size)
{
	(void)min_size;
	if (!free || !page)
		return (ERROR_ARGS);
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 14);
	while (free)
	{
		if (CHK_HEADER(free, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 15);
		if ((size_t)free->size >= blk_size) //place suffisante pour block
		{
			if ((size_t)free->size > blk_size)
				blk_size += free->size - blk_size;

			t_hdr_blk *next;
			t_hdr_blk *prev;

			next = NEXT_FBLK(free);
			prev = PREV_FBLK(free);
			if ((next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
				|| (prev && CHK_HEADER(prev, OFFSET_CHKM(HDR_BLK_SIZE))))
				kill_prog(CHECKSUM_CORRUPED, 16);
			if (!prev) //premier elem
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
				if (!prev)
					page->free = 0;
				else
					prev->fnext = 0;
			}
			else
			{
				if (page->free == free)
					page->free = prev;
				prev->fnext = OFFSET(next, prev);
				next->fprev = prev->fnext;
			}
			free->fnext = 0;
			free->fprev = 0;
			free->size = blk_size;
			++page->nbr_blk;
			(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
			(prev) ? SET_CHKM(prev, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
			(prev) ? display_hdr_blk(prev): 0;
			(next) ? display_hdr_blk(next): 0;
			SET_CHKM(free, OFFSET_CHKM(HDR_BLK_SIZE));
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
			g_data.mem_ret = BEGIN_BLK(free);
			return (FREE_USED);
		}
		else
			free = NEXT_FBLK(free);
	}

	//set checksum
	P_DEBUG(LEVEL_3, "\t\tFREE_NO_USED\n");
	return (FREE_NO_USED);
}

t_ret_manager	*memory_manager(t_hdr_page *page, size_t blk_size, enum e_types type, t_ret_manager *ret)
{
	t_hdr_blk 		*blk;
	t_hdr_blk 		*free;

	if (page == 0)
	{
		ret->value = CREATE_NEW_PAGE;
		return (ret);
	}
	ret->page = page;
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 1);
	free = page->free;
	if (page->free && manage_free_block(page, free, blk_size, MIN_SIZE(type)) == FREE_USED)
	{
		ret->value = FREE_USED;
		return (ret);
	}
	if (page->last_blk != 0)
	{
		if (CHK_HEADER(page->last_blk, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 2);
		if ((blk = NEXT_BLK(page->last_blk)) == 0)
			return(memory_manager(page->next, blk_size, type, ret));
		blk->bprev = OFFSET(blk, page->last_blk);
	}
	else
		blk = FIRST_BLK(page);
	blk->size = blk_size;
	if ((ret->value = check_space_and_align(page, blk, type)) == CREATE_NEW_BLK)
		return (ret);
	else if (ret->value == CREATE_NEW_PAGE)
	{
		if (check_align(blk, END_PAGE(page), type == TINY ? 1 : TINY_MAX + 1) == ALIGN)
		{
			blk->size = END_PAGE(page) - NEXT_BLK(page->last_blk) - HDR_BLK_SIZE - blk->align;
			page->nbr_blk++;
			blk->bnext = 0;
			SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
			create_free_blk(blk, page, type);
			page->last_blk = blk;
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
		}
		return (ret);
	}
	ret->page = 0;
	ret->value = ERROR_MEMORY_MANAGER;
	return (ret);
}