/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:49:34 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/23 04:43:39 by jmoucade         ###   ########.fr       */
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

void			*realloc(void *ptr, size_t size)
{
	t_hdr_page		*page;
	t_hdr_blk		*blk;
	enum e_types	type;

	pthread_mutex_lock(&g_mutex);
	DEBUGV("%s call realloc(%p, %zd)\n", get_progname("_"), ptr, size);
	if (ptr && size == 0)
		return (get_min_objet(ptr));
	if (!ptr && pthread_mutex_unlock(&g_mutex))
		return (malloc(size > 0 ? size : MIN_SIZE_OBJ));
	if (!(page = find_page(&g_data, ptr, &type))
		&& pthread_mutex_unlock(&g_mutex))
		return (ptr);
	if (type == LARGE && type_block(size) == LARGE
						&& (size_t)FIRST_BLK(page)->size < size)
	{
		if ((page = expand_page(page, size)))
			return (BEGIN_BLK(FIRST_BLK(page)));
		else
			return (get_min_objet(ptr));
	}
	blk = find_blk(page, ptr);
	pthread_mutex_unlock(&g_mutex);
	return (blk == 0 ? NULL : realloc_end(ptr, size, blk));
}
