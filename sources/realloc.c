/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 23:49:34 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/14 14:25:21 by mo0k             ###   ########.fr       */
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

void	expand_blk(t_hdr_blk *blk, size_t size)
{
	P_DEBUG_VARGS(LEVEL_2, "\t\tSTART expand_blk blk:%p, size:%zd\n", blk, size);
	if (!blk)
		return ;
	blk->size += size;
	blk->bnext += size;
	SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
}

int 	is_free_blk(t_hdr_page *page, t_hdr_blk *blk)
{
	t_hdr_blk 	*free;

	if (!page || !blk)
		return (ERROR_ARGS);
	free = FIRST_FREE(page);
	while (free && free <= blk)
	{
		if (CHK_HEADER(free, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 35);
		if (free == blk)
			return (TRUE);
		else
			free = NEXT_FBLK(free);
	}
	return (FALSE);

}
void 	expand_blk_in_freeblk(t_hdr_blk *blk, t_hdr_blk *free, size_t size, t_hdr_page *page, size_t min_size)
{
	unsigned int diff;

	diff = free->size - size;
	P_DEBUG_VARGS(LEVEL_2, "\t\tsize a recuperer:%zd, diff:%d, blk:%p\n", size, diff, blk);
	if (diff < HDR_BLK_SIZE + min_size)
		size += diff;
	else
	{

		P_DEBUG_VARGS(LEVEL_2, "\t\tplace suffisante pour 2 bloc si align ok : min_size:%zd\n", min_size);
		void *end = END_BLK(free);
		t_hdr_blk tmp;
		ft_memmove(&tmp, free, sizeof(t_hdr_blk));
		ft_memset((void*)free + size, 0, HDR_BLK_SIZE);

		if (check_align((void*)free + size, end, min_size) == ALIGN)
		{
			P_DEBUG(LEVEL_2, "\t\tcreation 2eme block free\n");
			//crer deuxieme block free
			t_hdr_blk *new_blk;

			//new_blk = END_BLK(free);
			//new_blk = (void*)free + free->align + HDR_BLK_SIZE + size; // a voir
			new_blk = (void*)free + size; // a voir
			new_blk->size = diff - HDR_BLK_SIZE - new_blk->align;
			new_blk->bnext = tmp.bnext ? tmp.bnext - OFFSET(new_blk, free) : 0;
			new_blk->bprev = OFFSET(new_blk, blk); 
			new_blk->fnext = tmp.fprev ? tmp.fnext - LEN_BLK(&tmp) : 0;
			new_blk->fprev = tmp.fprev ? tmp.fprev + LEN_BLK(&tmp) : 0; 
			//display_hdr_blk(new_blk);
			SET_CHKM(new_blk, OFFSET_CHKM(HDR_BLK_SIZE));
			//free->bnext = new_blk->bprev;
			//free->fnext = new_blk->fprev;
			if (page->free == OFFSET(free, page) && SET_FIRST_FREE(page, new_blk))
				SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
			if (OFFSET(new_blk, page) > page->last_blk)
			{
				P_DEBUG(LEVEL_2, "\t\tchangement last_blk\n");
				page->last_blk = OFFSET(new_blk, page);
				SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
			}
		}
		else
		{
			size += diff;
			//ft_printf("No align => size += diff : %zd\n", size);
		}
	}
	blk->size += size;
	blk->bnext += size;
	SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
	//taille a ajouter au blk
}

void *realloc(void *ptr, size_t size)
{
	//return (malloc(size));
	//return ((ptr = malloc(size)));
	//ft_printf("realloc\n");
	//OPEN_DEBUG();
	P_DEBUG_VARGS(LEVEL_1, "{LGREEN}REALLOC{EOC}\taddress:%-8p\tsize:%zd octets\n", ptr, size);
	if (ptr && size == 0)
	{
		P_DEBUG(LEVEL_2, "\t\tGet_min_object\n");
		//CLOSE_DEBUG();
		return (get_min_objet(ptr));
	}
	if (!ptr)
	{
		P_DEBUG_VARGS(LEVEL_2, "\t\tptr NULL go malloc(%lu)\n", size > 0 ? size : MIN_SIZE_OBJ);
		//CLOSE_DEBUG();
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
		{
			//t_hdr_blk *blk;
			//blk = FIRST_BLK(page);
			FIRST_BLK(page)->size = size;
			//blk->size = size;
			SET_CHKM(FIRST_BLK(page), OFFSET_CHKM(HDR_BLK_SIZE));	
			//CLOSE_DEBUG();
			return (BEGIN_BLK(FIRST_BLK(page)));

		}
		else
		{
			//CLOSE_DEBUG();
			return (get_min_objet(ptr));
		}
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
		if (type_block(blk->size) < type_block(size))
		{
			//changement de type de block
			P_DEBUG(LEVEL_2, "\t\ttype_block(blk->size) < type_block(size)\n");

			//free(ptr);
			//return(new = malloc(size));
			new = malloc(size);
			ft_memmove(new, BEGIN_BLK(blk), blk->size);
			//ft_printf("__fin malloc\n");
			free(ptr);
			//ft_printf("__fin freem\n");

			//ptr = new;
			//CLOSE_DEBUG();
			return (new);
		}	
		else
		{
			//t_hdr_blk *free;
			//creation sur meme page
			if (!NEXT_BLK(blk))
				P_DEBUG(LEVEL_2, "\t\tNEXT_BLK(blk) == 0\n");
			P_DEBUG_VARGS(LEVEL_2, "\t\tblk->bnext:%hd\t((t_hdr_blk*)(NEXT_BLK(blk)))->size:%hd\tret_chkm:%d\n", blk->bnext, (NEXT_BLK(blk)) ? ((t_hdr_blk*)(NEXT_BLK(blk)))->size : 0, (NEXT_BLK(blk)) ? CHK_HEADER(NEXT_BLK(blk), OFFSET_CHKM(HDR_BLK_SIZE)) : 0);
			if (END_PAGE(page) - size - blk->size >= END_BLK(blk) && (blk->bnext == 0
				|| (blk->bnext && LAST_BLK(page) == blk)))
			{
				//(blk->bnext && !CHK_HEADER(NEXT_BLK(blk), OFFSET_CHKM(HDR_BLK_SIZE))
				//	&& ((t_hdr_blk*)(NEXT_BLK(blk)))->size == 0)))
				expand_blk(blk, size - blk->size);
			}
			else if (is_free_blk(page, NEXT_BLK(blk)) == TRUE
				&& ((size_t)(blk->size + LEN_BLK((t_hdr_blk*)NEXT_BLK(blk))) >= size
					|| LAST_BLK(page) == blk)) // si dernier bloc
				expand_blk_in_freeblk(blk, NEXT_BLK(blk), size - blk->size, page, MIN_SIZE(type));
			else
			{
				P_DEBUG_VARGS(LEVEL_2, "\t\tnew malloc size:%zd, blk->size:%hd\n", ((t_hdr_blk*)(ptr))->size, blk->size);
				new = malloc(size);
				ft_memmove(new, BEGIN_BLK(blk), blk->size);
				free(ptr);
				//CLOSE_DEBUG();
				return (new);
			}
			//CLOSE_DEBUG();
			(DEBUG <= 4) ? display_hdr_blk(blk) : 0;
	show_alloc_mem();
			
			return(BEGIN_BLK(blk));
		}
	}
	//if (type_block(size) < type)



	//if (ptr->bnext)
	//CLOSE_DEBUG();
	return (ptr);
}