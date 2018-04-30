/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_free_blk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:11:18 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/29 11:43:46 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
void 	display_hdr_page(t_hdr_page *hdr_page);
void 	display_hdr_blk(t_hdr_blk *hdr_blk);

void			create_free_blk(t_hdr_blk *blk, t_hdr_page *page, enum e_types type)
{
	int flag;

	flag = 0;
	if (page == 0 || blk == 0)
		return ;
	if (page->free == 0)
		page->free = blk;
	place_free_blk(blk, page->free, page); //a inverser avec condition ci-dessous
	if (--page->nbr_blk == 0)
	{
		del_page(page, type);
		return ;
	}
	SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
}