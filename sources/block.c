/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 23:10:33 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			display_hdr_blk(t_hdr_blk *hdr_blk)
{
	if (!hdr_blk)
		return ;
	DEBUGV("\t\thdr_blk:%p\n", hdr_blk);
	DEBUGV("\t\thdr_blk->block_prev(%p):%hd\n"
		, PREV_BLK(hdr_blk), hdr_blk->bprev);
	DEBUGV("\t\thdr_blk->block_next(%p):%hd\n"
		, NEXT_BLK(hdr_blk), hdr_blk->bnext);
	DEBUGV("\t\thdr_blk->free_prev(%p):%hd\n"
		, PREV_FBLK(hdr_blk), hdr_blk->fprev);
	DEBUGV("\t\thdr_blk->free_next(%p):%hd\n"
		, NEXT_FBLK(hdr_blk), hdr_blk->fnext);
	DEBUGV("\t\thdr_blk->size:%hd\n", hdr_blk->size);
	DEBUGV("\t\thdr_blk->align:%hd\n", hdr_blk->align);
	DEBUGV("\t\tchecksum:0x%02x 0x%02x\n"
		, hdr_blk->chkm[0], hdr_blk->chkm[1]);
	DEBUGV("\t\taddr ret:%p\n"
		, (void*)hdr_blk + HDR_BLK_SIZE + hdr_blk->align);
}

enum e_types	type_block(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	else if (size > TINY_MAX && size <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}

void			create_new_block(t_hdr_blk *block, t_hdr_page *page)
{
	if (!block)
		return ;
	if (END_PAGE(page) > END_BLK(block))
		block->bnext = END_BLK(block) - (void*)block;
	else
		block->bnext = 0;
	block->fnext = 0;
	block->fprev = 0;
	SET_CHKM(block, OFFSET_CHKM(HDR_BLK_SIZE));
}

t_hdr_blk		*find_blk(t_hdr_page *page, void *ptr)
{
	static t_hdr_blk	*blk;

	if (!page || !ptr)
		return (0);
	blk = FIRST_BLK(page);
	while (blk)
	{
		if (page && CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 51);
		if (BEGIN_BLK(blk) == ptr)
			return (blk);
		else
			blk = NEXT_BLK(blk);
	}
	return (0);
}
