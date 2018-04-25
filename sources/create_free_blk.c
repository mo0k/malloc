/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_free_blk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:11:18 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/25 23:04:29 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
void 	display_hdr_page(t_hdr_page *hdr_page);
void 	display_hdr_blk(t_hdr_blk *hdr_blk);
/*
static void		join_prev(t_hdr_blk *blk, t_hdr_page *page)
{
	t_hdr_blk *prev;
	t_hdr_blk *next;

	P_DEBUG(LEVEL_3, "\t\tLINK PREV BLK FREE\n");
	if (!blk || !page)
		return ;
	prev = PREV_FBLK(blk);
	if (CHK_HEADER(prev, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 4);
	prev->fnext = blk->fnext ? prev->fnext + blk->fnext : 0;
	prev->bnext = blk->bnext ? prev->bnext + blk->bnext : 0;
	prev->size += blk->size + blk->align + HDR_BLK_SIZE;
	next = NEXT_FBLK(prev);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 5);
	(next) ? (next->fprev = prev->fnext) : 0;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
	next = NEXT_BLK(prev);
	P_DEBUG_VARGS(LEVEL_3, "\t\tprev:%p,bnext:%p\n", prev, next);
	P_DEBUG_VARGS(LEVEL_3, "\t\tprev->fnext(%p):%d\n", NEXT_FBLK(prev), prev->fnext);
	P_DEBUG_VARGS(LEVEL_3, "\t\tprev->bnext(%p):%d\n", NEXT_BLK(prev) ,prev->bnext);
	P_DEBUG_VARGS(LEVEL_3, "\t\tprev->size:%d\n", prev->size);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 6);
	(next) ? (next->bprev = prev->bnext) : 0;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
	SET_CHKM(prev, OFFSET_CHKM(HDR_BLK_SIZE));
	if (page->free > prev && (page->free = prev))
		SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	if (page->last_blk == blk && (page->last_blk = prev))
	{
		P_DEBUG_VARGS(LEVEL_2, "changement last_blk:{cyan}%p{eoc}\n", page->last_blk);
		//sleep(5);
		SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	}
	display_hdr_blk(prev);
}

static void		join_next(t_hdr_blk *blk, t_hdr_page *page)
{
	t_hdr_blk *next;

	P_DEBUG(LEVEL_3, "\t\tLINK NEXT BLK FREE\n");
	if (!blk || !page)
		return ;
	next = NEXT_FBLK(blk);
	if (CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 7);
	P_DEBUG_VARGS(LEVEL_3, "\t\tavant assign new blk:%p, free next:%p\n", blk, next);
	//display_hdr_blk(blk);
	//ft_printf("\nnext\n\n");
	//display_hdr_blk(next);

	if (page->last_blk == next && (page->last_blk = blk))
	{
		P_DEBUG_VARGS(LEVEL_2, "changement last_blk:{cyan}%p{eoc} next:%p\n", page->last_blk, next);
		//sleep(5);
		SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	}

	blk->fnext = next->fnext ? blk->fnext + next->fnext : 0;
	blk->bnext = next->bnext ? blk->bnext + next->bnext : 0;
	blk->size += next->size + next->align + HDR_BLK_SIZE;
	next = NEXT_FBLK(blk);
	P_DEBUG_VARGS(LEVEL_3, "\t\tapres assign new blk:%p, free next:%p\n", blk, next);
	//display_hdr_blk(blk);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 8);
	(next) ? (next->fprev = blk->fnext) : 0;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
	next = NEXT_BLK(blk);
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk:%p,bnext:%p\n", blk, next);
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk->fnext(%p):%d\n", NEXT_FBLK(blk), blk->fnext);
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk->bnext(%p):%d\n", NEXT_BLK(blk) ,blk->bnext);
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk->size:%d\n", blk->size);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 9);
	(next) ? next->bprev = blk->bnext : 0;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
	SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
	if (page->free > blk && (page->free = blk))
		SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
}
*/
void			create_free_blk(t_hdr_blk *blk, t_hdr_page *page, enum e_types type)
{
	int flag;

	flag = 0;
	P_DEBUG(LEVEL_3, "\t\tCREATE_FREE_BLOCK\n");
	if (page == 0 || blk == 0)
		return ;
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk:%p,page:%p\n", blk, page);
	if (page->free == 0)
	{
		P_DEBUG(LEVEL_3, "\t\tpage->free=0 go SET_FIRST_FREE\n");
		//SET_FIRST_FREE(page, blk);
		page->free = blk;
	}
	//(DEBUG == 3) ? display_hdr_blk(FIRST_FREE(page)) : 0;
	P_DEBUG_VARGS(LEVEL_3, "\t\tpage->free:%p\n", page->free);
	place_free_blk(blk, page->free, page);
	if (--page->nbr_blk == 0)
	{
		P_DEBUG(LEVEL_3, "\t\tgo mummap\n");
		del_page(page, type);
		return ;
	}
	P_DEBUG_VARGS(LEVEL_3, "\t\tnbr_blk:%d\n", page->nbr_blk);
	SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
	//if (blk->fprev && blk->fprev == blk->bprev && (flag = 1))
	//	join_prev(blk, page);
	//if (blk->fnext && blk->fnext == blk->bnext)
	//	join_next(flag ? PREV_BLK(blk) : blk, page);
	
	//display_hdr_page(page);

	/*
	//DEBUG LIST
	t_hdr_blk *tmp = FIRST_BLK(page);
	P_DEBUG_VARGS(LEVEL_3, "\t\ttmp:%p\n", tmp);
	while(DEBUG && tmp)
	{
		if (tmp->size)
		{
			if (tmp && CHK_HEADER(tmp, OFFSET_CHKM(HDR_BLK_SIZE)))
			{
				P_DEBUG(LEVEL_3, "\t\tEXIT PRG ERROR CHK 10xxxxxxxxxxxxxxxxxxxxxx\n");
				break ;
			}
			display_hdr_blk(tmp);
		}
		P_DEBUG(LEVEL_3, "\t\tnext\n");
		tmp = NEXT_BLK(tmp);
	}
	(DEBUG == 3) ? display_hdr_page(page) : 0;*/
}