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

static void				set_info(t_info *info_mem, t_hdr_page *page, \
										t_hdr_blk *blk, enum e_types type)
{
	info_mem->page = page;
	info_mem->blk = blk;
	info_mem->type = type;
}

static t_ret_manager	*find_and_place_blk(t_ret_manager *ret, \
											t_info *info_mem, size_t blk_size)
{
	info_mem->blk->size = blk_size;
	if ((ret->value = check_space_and_align(info_mem->page, \
							info_mem->blk, info_mem->type)) == CREATE_NEW_BLK)
		return (ret);
	else if (ret->value == CREATE_NEW_PAGE)
	{
		if (check_align(info_mem->blk, END_PAGE(info_mem->page)
						, info_mem->type == TINY ? 1 : TINY_MAX + 1) == ALIGN)
		{
			info_mem->blk->size = END_PAGE(info_mem->page) - \
								NEXT_BLK(info_mem->page->last_blk) - \
								HDR_BLK_SIZE - info_mem->blk->align;
			info_mem->page->nbr_blk++;
			info_mem->blk->bnext = 0;
			SET_CHKM(info_mem->blk, OFFSET_CHKM(HDR_BLK_SIZE));
			create_free_blk(info_mem->blk, info_mem->page, info_mem->type);
			info_mem->page->last_blk = info_mem->blk;
			SET_CHKM(info_mem->page, OFFSET_CHKM(HDR_PAGE_SIZE));
		}
		return (ret);
	}
	ret->page = 0;
	ret->value = ERROR_MEMORY_MANAGER;
	return (ret);
}

t_ret_manager			*memory_manager(t_hdr_page *page, size_t blk_size, \
									enum e_types type, t_ret_manager *ret)
{
	t_hdr_blk		*blk;
	t_hdr_blk		*free;
	t_info			tmp;

	if (page == 0 && (ret->value = CREATE_NEW_PAGE))
		return (ret);
	ret->page = page;
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 1);
	free = page->free;
	if (page->free && manage_free_block(page, free, blk_size) == FREE_USED
			&& (ret->value = FREE_USED))
		return (ret);
	if (page->last_blk != 0)
	{
		if (CHK_HEADER(page->last_blk, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 2);
		if ((blk = NEXT_BLK(page->last_blk)) == 0)
			return (memory_manager(page->next, blk_size, type, ret));
		blk->bprev = OFFSET(blk, page->last_blk);
	}
	else
		blk = FIRST_BLK(page);
	set_info(&tmp, page, blk, type);
	return (find_and_place_blk(ret, &tmp, blk_size));
}
