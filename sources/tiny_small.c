/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/30 18:48:28 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	manage_tiny_small(t_hdr_page *page, size_t size, enum e_types type)
{
	t_ret_manager 	ret;

	if (!page)
		return ;
	if ((ret = *memory_manager(page, size, type, &ret)).value == CREATE_NEW_BLOCK)
	{
		t_hdr_blk	*blk;

		blk = ret.page->last_blk ? NEXT_BLK(ret.page->last_blk) : FIRST_BLK(ret.page);
		create_new_block(blk, ret.page);
		ret.page->last_blk = blk;
		++ret.page->nbr_blk;
		SET_CHKM(ret.page, OFFSET_CHKM(HDR_PAGE_SIZE));
		g_data.mem_ret = BEGIN_BLK(blk);
		
	}
	else if (ret.value == CREATE_NEW_PAGE)
	{
		t_hdr_blk	*blk;

		initialize_page((t_hdr_page**)&ret.page->next, ret.page, ret.page->size);
		SET_CHKM(ret.page, OFFSET_CHKM(HDR_PAGE_SIZE));
		ret.page = ret.page->next;
		blk = FIRST_BLK(ret.page);
		blk->size = size;
		check_space_and_align(ret.page, blk, type);
		create_new_block(blk, ret.page);
		ret.page->last_blk = blk;
		++ret.page->nbr_blk;
		SET_CHKM(ret.page, OFFSET_CHKM(HDR_PAGE_SIZE));
		g_data.mem_ret = BEGIN_BLK(blk);
	}
}