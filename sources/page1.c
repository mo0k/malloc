/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 22:00:20 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void				initialize_page(t_hdr_page **page, t_hdr_page *prev \
													, unsigned int page_size)
{
	*page = NEW_PAGE(page_size);
	if (*page == NULL)
		return ;
	(*page)->size = page_size;
	(*page)->prev = prev;
	SET_CHKM(*page, OFFSET_CHKM(HDR_PAGE_SIZE));
}

static void			fix_first_page(t_hdr_page *page, enum e_types type)
{
	if (type == LARGE)
		g_data.mem_large.page = page;
	else if (type == SMALL)
		g_data.mem_small.page = page;
	else
		g_data.mem_tiny.page = page;
}

void				del_page(t_hdr_page *page, enum e_types type)
{
	t_hdr_page *prev;
	t_hdr_page *next;

	prev = page->prev;
	next = page->next;
	if (prev && CHK_HEADER(prev, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 31);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 32);
	if (!prev)
	{
		fix_first_page(next, type);
		(next) ? next->prev = 0 : 0;
	}
	else
	{
		prev->next = next;
		(next) ? next->prev = prev : 0;
	}
	(prev) ? SET_CHKM(prev, OFFSET_CHKM(HDR_PAGE_SIZE)) : 0;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_PAGE_SIZE)) : 0;
	if (DEL_PAGE(page) == -1)
		kill_prog(CHECKSUM_CORRUPED, 132);
}
