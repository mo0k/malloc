/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/25 22:51:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	manage_tiny_small(t_hdr_page *page, size_t size, enum e_types type)
{
	t_ret_manager 	ret;

	if (!page)
		return ;
	if ((ret = *memory_manager(page, size, type, &ret, 0)).value == CREATE_NEW_BLOCK)
	{

		t_hdr_blk	*blk;
		P_DEBUG_VARGS(LEVEL_3, "\t\tpage:%p\n", page);
		blk = ret.page->last_blk ? NEXT_BLK(ret.page->last_blk) : FIRST_BLK(ret.page);
		P_DEBUG_VARGS(LEVEL_3, "\t\tcreate block(%p)\n", blk);
		create_new_block(blk, ret.page);
		P_DEBUG_VARGS(LEVEL_3, "\t\t1.1 create page->last_blk:%d\n", ret.page->last_blk);
		//SET_LAST_BLK(ret.page, blk);
		ret.page->last_blk = blk;
		++ret.page->nbr_blk;
		P_DEBUG_VARGS(LEVEL_3, "\t\t1.2 create page->last_blk:%d\n", ret.page->last_blk);
		SET_CHKM(ret.page, OFFSET_CHKM(HDR_PAGE_SIZE));
		(DEBUG >= 4) ? display_hdr_blk(blk) : 0;
		(DEBUG >= 3) ? display_hdr_page(page) : 0;
		g_data.mem_ret = BEGIN_BLK(blk);
		P_DEBUG_VARGS(LEVEL_2, "\t\t%d-byte block created at %p\n", blk->size, BEGIN_BLK(blk));
		display_hdr_blk(blk);
		
	}
	else if (ret.value == CREATE_NEW_PAGE)
	{
		t_hdr_blk	*blk;

		(DEBUG == 3) ? display_hdr_page(ret.page) : 0;
		P_DEBUG_VARGS(LEVEL_3, "\t\tcreate new map et create new block => ret.page:%p\n", ret.page);
		initialize_page((t_hdr_page**)&ret.page->next, ret.page, ret.page->size);
		//ret.page->next = initialize_page2(ret.page, ret.page->size);
		SET_CHKM(ret.page, OFFSET_CHKM(HDR_PAGE_SIZE));
		(DEBUG == 3) ? display_hdr_page(ret.page) : 0;
		ret.page = ret.page->next;
		blk = FIRST_BLK(ret.page);
		blk->size = size;
		P_DEBUG_VARGS(LEVEL_3, "\t\tblk:%p\n", blk);
		check_space_and_align(ret.page, blk, type);
		create_new_block(blk, ret.page);
		P_DEBUG_VARGS(LEVEL_3, "\t\t2.1 create page->last_blk:%d\n", ret.page->last_blk);
		ret.page->last_blk = blk;
		//SET_LAST_BLK(ret.page, blk);
		P_DEBUG_VARGS(LEVEL_3, "\t\t2.2 create page->last_blk:%d\n", ret.page->last_blk);
		++ret.page->nbr_blk;
		SET_CHKM(ret.page, OFFSET_CHKM(HDR_PAGE_SIZE));
		(DEBUG >= 3) ? display_hdr_blk(blk) : 0;
		g_data.mem_ret = BEGIN_BLK(blk);
		P_DEBUG_VARGS(LEVEL_2, "\t\t%d-byte block created at %p\n", blk->size, BEGIN_BLK(blk));
	display_hdr_blk(blk);
	}
	//print_page((void*)mem->page, 4096);
	P_DEBUG(LEVEL_3, "\t\t\n");

	/*t_hdr_blk *tmp = FIRST_BLK(page);
	P_DEBUG_VARGS(LEVEL_2, "tmp:%p\n", tmp);
	while(DEBUG && tmp)
	{
		if (tmp->size)
			display_hdr_blk(tmp);
		P_DEBUG_VARGS(LEVEL_2, "next\n");
		tmp = NEXT_BLK(tmp);
	}
	(DEBUG) ? display_hdr_page(page) : 0;*/
}