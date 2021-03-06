/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_free_blk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:38:57 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 22:00:49 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int		last_place(t_hdr_blk *new_last, t_hdr_blk *old_last)
{
	if (!new_last || !old_last)
		return (ERROR_ARGS);
	new_last->fprev = OFFSET(new_last, old_last);
	new_last->fnext = 0;
	old_last->fnext = new_last->fprev;
	SET_CHKM(old_last, OFFSET_CHKM(HDR_BLK_SIZE));
	SET_CHKM(new_last, OFFSET_CHKM(HDR_BLK_SIZE));
	return (BLOCK_FREE_PLACED);
}

static int		mid_place(t_hdr_blk *prev, t_hdr_blk *mid, t_hdr_blk *next)
{
	if (!prev || !mid || !next)
		return (ERROR_ARGS);
	mid->fprev = OFFSET(mid, prev);
	mid->fnext = OFFSET(next, mid);
	prev->fnext = mid->fprev;
	next->fprev = mid->fnext;
	SET_CHKM(prev, OFFSET_CHKM(HDR_BLK_SIZE));
	SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE));
	return (BLOCK_FREE_PLACED);
}

static int		first_place(t_hdr_blk *new_first, t_hdr_blk *old_first)
{
	if (!new_first || !old_first)
		return (ERROR_ARGS);
	new_first->fprev = 0;
	new_first->fnext = OFFSET(old_first, new_first);
	old_first->fprev = new_first->fnext;
	SET_CHKM(old_first, OFFSET_CHKM(HDR_BLK_SIZE));
	SET_CHKM(new_first, OFFSET_CHKM(HDR_BLK_SIZE));
	return (BLOCK_FREE_PLACED);
}

int				place_free_blk(t_hdr_blk *blk, t_hdr_blk *free \
												, t_hdr_page *page)
{
	t_hdr_blk	*next;

	if (!blk || !free)
		return (ERROR_ARGS);
	while (free)
	{
		if (CHK_HEADER(free, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 3);
		next = NEXT_FBLK(free);
		if (blk > free && next && blk < next)
			return (mid_place(free, blk, next) == BLOCK_FREE_PLACED);
		else if (blk > free && next == 0)
			return (last_place(blk, free) == BLOCK_FREE_PLACED);
		else if (blk < free && first_place(blk, free) == BLOCK_FREE_PLACED)
		{
			page->free = blk;
			return (BLOCK_FREE_PLACED);
		}
		free = next;
	}
	return (BLOCK_FREE_NOPLACED);
}
