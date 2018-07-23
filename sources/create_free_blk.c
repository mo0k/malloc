/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_free_blk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 22:11:18 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 23:10:45 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		create_free_blk(t_hdr_blk *blk, t_hdr_page *page, enum e_types type)
{
	int		flag;

	flag = 0;
	if (page == 0 || blk == 0)
		return ;
	if (page->free == 0)
		page->free = blk;
	if (--page->nbr_blk == 0)
	{
		del_page(page, type);
		return ;
	}
	place_free_blk(blk, page->free, page); //*OK => a inverser avec condition ci-dessous
	SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
	SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
}
