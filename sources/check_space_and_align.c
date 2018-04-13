/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_and_align.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/11 22:19:34 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int 		check_align(t_hdr_blk *new_blk, void *limit_end, size_t min_size)
{
	t_hdr_blk		*addr;

	if (!new_blk || !limit_end)
		return (ERROR_ARGS);
	//addr = BEGIN_BLK(new_blk);
	addr = (void*)new_blk + HDR_BLK_SIZE;
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk:%p\n", addr);
	new_blk->align = 0;
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk:%p\taddr:%p\tblk->size:%d\tblk->align:%d\n", new_blk, addr, new_blk->size, new_blk->align);
	P_DEBUG_VARGS(LEVEL_3, "\t\talign: new_blk:%p\tlimit_end:%p\taddr:%p\n", new_blk, limit_end, addr);
	while ((void*)addr + min_size + new_blk->align < limit_end && ALIGN(new_blk))
	{
		P_DEBUG_VARGS(LEVEL_3, "\t\talign addr:%p\n", addr);
		++new_blk->align;
		//addr = (void*)addr + 1;
	}
	if ((void*)addr + min_size + new_blk->align < limit_end)
		return (ALIGN);
	return (NO_ALIGN);
}

int 	check_space_and_align(t_hdr_page *page, t_hdr_blk *blk, enum e_types type)
{
	if (page == 0 || blk == 0)
		return (-1);
	while (AVAILABLE_BLK(blk, page) && ALIGN(blk))
		blk->align += 1;
	P_DEBUG_VARGS(LEVEL_3, "\t\tcheck_space..align block_size:%d\n",blk->size);
	if (AVAILABLE_BLK(blk, page))
	{
		P_DEBUG_VARGS(LEVEL_3, "\t\tpage:%p, page_end:%p, blk_end:%p\n", page, (void*)page + page->size, (void*)blk+blk->size+blk->align+HDR_BLK_SIZE);
		if (MIN_SIZE_REMAINING(blk, page, type))
		{
			blk->size += END_PAGE(page) - END_BLK(blk);
			P_DEBUG(LEVEL_3, "\t\textension blk_size\n");
		}
		P_DEBUG_VARGS(LEVEL_3, "\t\tgo creation blk : align:%hd\n", blk->align);
		return (CREATE_NEW_BLOCK);
	}
	return (CREATE_NEW_PAGE);
}