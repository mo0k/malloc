/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:49:34 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/22 00:56:02 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define MIN_SIZE_OBJ 1
#define MIN_OBJECT() malloc(MIN_SIZE_OBJ) 

static void *get_min_objet(void *ptr)
{
	void *ret;

	if ((ret = malloc(MIN_SIZE_OBJ)))
		return (0);
	ft_memmove(ret, ptr, MIN_SIZE_OBJ);
	free(ptr);
	return (ret);
}

t_hdr_page *expand_page(t_hdr_page *page, size_t size)
{
	t_hdr_page	*new;
	t_hdr_page *prev = page->prev;
	t_hdr_page *next = page->next;

	if (!page || !size)
		return (0);
	initialize_page(&new, 0, LARGE_SIZE(size));
	//ft_memmove(FIRST_BLK(new), FIRST_BLK(page), FIRST_BLK(page)->size);
	ft_memmove(new, page, page->size > new->size ? new->size : page->size);
	SET_CHKM(new, OFFSET_CHKM(HDR_PAGE_SIZE));
	FIRST_BLK(page)->size = size;
	SET_CHKM(FIRST_BLK(page), OFFSET_CHKM(HDR_BLK_SIZE));	
	DEL_PAGE(page);
	if (prev && CHK_HEADER(prev, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 31);
	if (next && CHK_HEADER(next, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 32);
	if (!prev)
	{
		g_data.mem_large.page = new;
		//fix_first_page(next, type);
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


void *realloc(void *ptr, size_t size)
{
	P_DEBUG_VARGS(LEVEL_1, "{LGREEN}REALLOC{EOC}\taddress:%-8p\tsize:%zd octets\n", ptr, size);
	if (ptr && size == 0)
	{
		P_DEBUG(LEVEL_2, "\t\tGet_min_object\n");
		return (get_min_objet(ptr));
	}
	if (!ptr)
	{
		P_DEBUG_VARGS(LEVEL_2, "\t\tptr NULL go malloc(%lu)\n", size > 0 ? size : MIN_SIZE_OBJ);
		return (malloc(size > 0 ? size : MIN_SIZE_OBJ));
	}

	//rechercher page puis blk
	//si bnext == 0 possible extand
	//sinon fnext == 0 possible extend si taille suffisante
	//sinon new pointer et ft_memmove et frre ancien 
	t_hdr_page	*page;
	t_hdr_blk	*blk;
	enum e_types type;

	if (!(page = find_page(&g_data, ptr, &type)))
	{
		//CLOSE_DEBUG();
		return (ptr); // or NULL
	}
	P_DEBUG_VARGS(LEVEL_2, "\t\tfind page:%p\tend page:%p\n", page, END_PAGE(page));

	if (type == LARGE && type_block(size) == LARGE && (size_t)FIRST_BLK(page)->size < size)
	{
		P_DEBUG(LEVEL_2, "\t\tgo expand_page\n");
		if ((page = expand_page(page, size)))
			return (BEGIN_BLK(FIRST_BLK(page)));
		else
			return (get_min_objet(ptr));
	}
	if (!(blk = find_blk(page, ptr)))
	{
		//CLOSE_DEBUG();
		return (ptr); // or NULL
	}
	P_DEBUG_VARGS(LEVEL_2, "\t\tfind blk:%p, blk->size:%d\n", blk, blk->size);
	if (size <= (size_t)blk->size) // new_size <= old_size
	{
		//CLOSE_DEBUG();
		P_DEBUG(LEVEL_2, "\t\tsize <= (size_t)blk->size\n");
		(DEBUG <= 4) ? display_hdr_blk(blk) : 0;
		return (ptr);
	}
	else
	{

		P_DEBUG(LEVEL_2, "\t\tICI 1\n");
		void *new;
		
		new = malloc(size);
		ft_memmove(new, BEGIN_BLK(blk), blk->size);
			//ft_printf("__fin malloc\n");
		free(ptr);
			//ft_printf("__fin freem\n");

			//ptr = new;
			//CLOSE_DEBUG();
		//show_alloc_mem();
		return (new);
	}
}