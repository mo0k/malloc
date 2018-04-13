/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/10 22:23:17 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 	display_hdr_page(t_hdr_page *hdr_page)
{
	if (!hdr_page)
		return ;
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page:%p\n", hdr_page);
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page->prev:%p\n", hdr_page->prev);
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page->next:%p\n", hdr_page->next);
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page->size:%d\n", hdr_page->size);
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page->last_blk(%p):%d\n", LAST_BLK(hdr_page), hdr_page->last_blk);
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page->free(%p):%d\n", FIRST_FREE(hdr_page), hdr_page->free);
	P_DEBUG_VARGS(LEVEL_3, "\t\thdr_page->nbr_blk:%hd\n", hdr_page->nbr_blk);
	P_DEBUG_VARGS(LEVEL_3, "\t\tchecksum:0x%02x 0x%02x\n", hdr_page->chkm[0], hdr_page->chkm[1]);
}

void 	print_page(void *page, size_t size)
{
	size_t i;
	unsigned char *ptr;

	ptr = (unsigned char*)page;
	i = 0;
	if (!page)
	return ;
	while (i < size)
	{
		ft_printf("index:%zu => %p(%c)(%d)(x%x)\n", i, &ptr[i], ptr[i], ptr[i], ptr[i]);
		i++;
	}
}

int 	page_size(enum e_types type)
{
	if (type == TINY)
		return (TINY_PAGE_SIZE);
	else if (type == SMALL)
		return (SMALL_PAGE_SIZE);
	return (-1);
}

void 		initialize_page(t_hdr_page **page, t_hdr_page *prev, unsigned int page_size)
{
	*page = NEW_PAGE(page_size);
	if (*page == NULL)
		return ;
	(*page)->size = page_size;
	(*page)->prev = prev;
	P_DEBUG_VARGS(LEVEL_2, "\t%10d-byte page created at %p\n", (*page)->size, *page);
	SET_CHKM(*page, OFFSET_CHKM(HDR_PAGE_SIZE));
}

static void	fix_first_page(t_hdr_page *page, enum e_types type)
{
	if (type == LARGE) 
		g_data.mem_large.page = page;
	else if (type == SMALL)
		g_data.mem_small.page = page;
	else 
		g_data.mem_tiny.page = page;
}

void	del_page(t_hdr_page *page, enum e_types type)
{
	t_hdr_page *prev = page->prev;
	t_hdr_page *next = page->next;
	
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
		perror("munmap");
}

static t_hdr_page	*select_page(t_hdr_page *page, void *ptr)
{
	if (!page)
		return (0);
	while (page)
	{
		if (page && CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 41);
		P_DEBUG_VARGS(LEVEL_3, "\t\tpage:%p, FIRST_BLK:%p, END_PAGE:%p, page->next:%p, page->prev:%p, page->size:%zd, NEXT_PAGE(page):%p\n"
		 							,page, FIRST_BLK(page), END_PAGE(page), page->next, page->prev, page->size, NEXT_PAGE(page));
		if (IN_PAGE(page, ptr))
		{
			P_DEBUG_VARGS(LEVEL_3, "next_page:%p\n", page->next);
			(page->next) ? P_DEBUG_VARGS(LEVEL_3, "next_page:%p\n", ((t_hdr_page*)(page->next))->next) : 0;
			return (page);
		}
		else
			page = page->next;
	}
	return (0);
}

t_hdr_page	*find_page(t_data *data, void *ptr, enum e_types *type)
{
	static t_hdr_page 		*page = NULL;

	if (!data)
		return (0);
	if (data->mem_tiny.page &&
		(page = select_page(data->mem_tiny.page, ptr)))
	{
		*type = TINY;
		return (page);
	}
	else if (data->mem_small.page &&
		(page = select_page(data->mem_small.page, ptr)))
	{
		*type = SMALL;
		return (page);
	}
	else if (data->mem_large.page &&
		(page = select_page(data->mem_large.page, ptr)))
	{
		*type = LARGE;
		return (page);
	}
	P_DEBUG(LEVEL_3, "\t\tpage = 0\n");
	*type = NO_TYPE;
	return (0);
}

