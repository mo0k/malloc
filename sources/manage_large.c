/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_large.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 20:57:38 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	manage_large(t_hdr_page *page, size_t size)
{
	t_hdr_blk	*blk;

	if (!page)
		return ;
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 18);
	blk = FIRST_BLK(page);
	if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 19);
	if (blk->size == 0)
	{
		blk->size = size;
		create_new_block(blk, page);
		SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
		g_data.mem_ret = BEGIN_BLK(blk);
	}
	else
	{
		if (!page->next)
		{
			initialize_page((t_hdr_page**)&page->next, page, LARGE_SIZE(size));
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
		}
		return (manage_large(page->next, size));
	}
}
