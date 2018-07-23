/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-lieg <sle-lieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:49:34 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/23 16:32:03 by sle-lieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*get_min_objet(void *ptr)
{
	void			*ret;

	pthread_mutex_unlock(&g_mutex);
	if ((ret = malloc(MIN_SIZE_OBJ)))
		return (0);
	ft_memmove(ret, ptr, MIN_SIZE_OBJ);
	free(ptr);
	return (ret);
}

static void		*fix_page(t_hdr_page *new, t_hdr_page *next, t_hdr_page *prev)
{
	if (!prev)
	{
		g_data.mem_large.page = new;
		(next) ? next->prev = new : 0;
	}
	else
	{
		prev->next = new;
		(next) ? next->prev = new : 0;
	}
	(prev) ? SET_CHKM(prev, OFFSET_CHKM(HDR_PAGE_SIZE)) : 0;
	(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_PAGE_SIZE)) : 0;
	return (new);
}

t_hdr_page		*expand_page(t_hdr_page *page, size_t size)
{
	t_hdr_page		*new;
	t_hdr_page		*prev;
	t_hdr_page		*next;

	prev = page->prev;
	next = page->next;
	if (!page || !size)
		return (0);
	initialize_page(&new, 0, LARGE_SIZE(size));
	ft_memmove(new, page, page->size > new->size ? new->size : page->size);
	SET_CHKM(new, OFFSET_CHKM(HDR_PAGE_SIZE));
	FIRST_BLK(page)->size = size;
	SET_CHKM(FIRST_BLK(page), OFFSET_CHKM(HDR_BLK_SIZE));
	DEL_PAGE(page);
	if (prev && CHK_HEADER(prev, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 31);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 32);
	fix_page(new, next, prev);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}

void			*realloc_end(void *ptr, size_t size, t_hdr_blk *blk)
{
	void			*new;

	pthread_mutex_lock(&g_mutex);
	if (size <= (size_t)blk->size)
	{
		pthread_mutex_unlock(&g_mutex);
		return (ptr);
	}
	else
	{
		pthread_mutex_unlock(&g_mutex);
		new = malloc(size);
		ft_memmove(new, BEGIN_BLK(blk), blk->size);
		free(ptr);
		return (new);
	}
}

void			*realloc(void *ptr, size_t sz)
{
	t_hdr_page		*p;
	t_hdr_blk		*blk;
	enum e_types	t;

	pthread_mutex_lock(&g_mutex);
	DEBUGV("%s call realloc(%p, %zd)\n", get_progname("_"), ptr, sz);
	if (ptr && sz == 0)
		return (get_min_objet(ptr));
	if (!ptr)
	{
		pthread_mutex_unlock(&g_mutex);
		return (malloc(sz > 0 ? sz : MIN_SIZE_OBJ));
	}
	if (!(p = find_page(&g_data, ptr, &t)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (ptr);
	}
	if (t == LARGE && typ_blk(sz) == LARGE && (size_t)FIRST_BLK(p)->size < sz)
		return ((p = expand_page(p, sz)) ? BEGIN_BLK(FIRST_BLK(p)) \
										: get_min_objet(ptr));
		blk = find_blk(p, ptr);
	pthread_mutex_unlock(&g_mutex);
	return (blk == 0 ? NULL : realloc_end(ptr, sz, blk));
}
