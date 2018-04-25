/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/25 22:48:21 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//	return NEW_PAGE
//	return FREE
//	return CREATE_BLOCK 


int				manage_free_block(t_hdr_page *page, t_hdr_blk *free, size_t blk_size, size_t min_size)
{
	P_DEBUG_VARGS(LEVEL_3, "\t\tmanage_free_block blk_size:%zd\n", blk_size);
	(void)min_size;
	if (!free || !page)
		return (ERROR_ARGS);
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 14);
	while (free)
	{
		P_DEBUG_VARGS(LEVEL_3, "\t\tfree:%p, free->size:%d\n", free, free->size);
		//checksum free blk
		if (CHK_HEADER(free, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 15);
		if ((size_t)free->size >= blk_size) //place suffisante pour block
		{
			if ((size_t)free->size > blk_size)
				blk_size += free->size - blk_size;
			/*if ((size_t)free->size > blk_size)
			{
				unsigned int diff;

				diff = free->size - blk_size;
				P_DEBUG_VARGS(LEVEL_3, "\t\tdiff:%d\n", diff);
				if (diff < HDR_BLK_SIZE + min_size)
					blk_size += diff;
				else
				{
					P_DEBUG(LEVEL_3, "\t\tplace suffisante pour 2 bloc si align ok\n");
					if (check_align(BEGIN_BLK(free) + blk_size, END_BLK(free), min_size) == ALIGN)
					{
						P_DEBUG(LEVEL_3, "\t\tcreation 2eme block free\n");
						//crer deuxieme block free
						t_hdr_blk *new_blk;
						t_hdr_blk *next;

						//new_blk = END_BLK(free);
						new_blk = (void*)free + free->align + HDR_BLK_SIZE + blk_size;
						new_blk->bnext = free->bnext ? free->bnext - OFFSET(new_blk, free) : 0;
						new_blk->bprev = OFFSET(new_blk, free); 
						//new_blk->fnext = free->fnext;
						new_blk->fnext = free->fnext ? free->fnext - OFFSET(new_blk, free) : 0;
						new_blk->fprev = new_blk->bprev; 
						new_blk->size = diff - HDR_BLK_SIZE - new_blk->align;
						SET_CHKM(new_blk, OFFSET_CHKM(HDR_BLK_SIZE));
						free->bnext = new_blk->bprev;
						free->fnext = new_blk->fprev;
						next = NEXT_FBLK(new_blk);
						(next) ? (next->fprev = OFFSET(next, new_blk) - new_blk->align) : 0;
						(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
						//(next) ? sleep(5) : 0;
						if (OFFSET(new_blk, page) > page->last_blk)
						{
							P_DEBUG_VARGS(LEVEL_3, "\t\tchangement last_blk:{cyan}%p{eoc}\n\n", (void*)page+page->last_blk);
							//sleep(2);
							page->last_blk = OFFSET(new_blk, page);
						}
						//sleep(2);
					}
					else
						blk_size += diff;
					//check si 2eme bloc peut etre aligner
					//fragmenter bloc en deux et le relier
				}
			}*/
		//leave free list
			display_hdr_blk(free);
			//sleep(1);
			t_hdr_blk *next;
			t_hdr_blk *prev;

			next = NEXT_FBLK(free);
			prev = PREV_FBLK(free);
			P_DEBUG_VARGS(LEVEL_3, "\t\tprev:{green}%p{eoc}\n\t\tnext:{green}%p{eoc}\n", prev,next);

			if ((next && CHK_HEADER(next, OFFSET_CHKM(HDR_BLK_SIZE)))
				|| (prev && CHK_HEADER(prev, OFFSET_CHKM(HDR_BLK_SIZE))))
				kill_prog(CHECKSUM_CORRUPED, 16);
			if (!prev) //premier elem
			{
				P_DEBUG(LEVEL_3, "\t\tpremier elem\n");
				if (!next)
					page->free = 0;
				else
					next->fprev = 0;
				if (page->free == free)
					page->free = next;
			}
			else if (!next)
			{
				P_DEBUG(LEVEL_3, "\t\tdernier elem\n");
				if (!prev)
					page->free = 0;
				else
					prev->fnext = 0;
			}
			else
			{
				P_DEBUG(LEVEL_3, "\t\tmiddle elem\n");

				if (page->free == free)
				{
					P_DEBUG_VARGS(LEVEL_3, "\t\tchange page->free = %ld\n", prev);
					page->free = prev;

				}
				P_DEBUG_VARGS(LEVEL_3, "\t\tOFFSET(next, prev):%d", OFFSET(next, prev));
				P_DEBUG_VARGS(LEVEL_3, "\t\tOFFSET(next, prev):%hd sizeof(short int):%zd", OFFSET(next, prev), sizeof(short int));
				prev->fnext = OFFSET(next, prev);
				next->fprev = prev->fnext;
			}
			free->fnext = 0;
			free->fprev = 0;
			free->size = blk_size;
			++page->nbr_blk;
			(next) ? SET_CHKM(next, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
			(prev) ? SET_CHKM(prev, OFFSET_CHKM(HDR_BLK_SIZE)) : 0;
			(prev) ? display_hdr_blk(prev): 0;
			(next) ? display_hdr_blk(next): 0;
			SET_CHKM(free, OFFSET_CHKM(HDR_BLK_SIZE));
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
			g_data.mem_ret = BEGIN_BLK(free);
			//display_hdr_page(page);
			display_hdr_blk(free);
			g_debugging = 0;
			return (FREE_USED);
		}
		else
			free = NEXT_FBLK(free);
	}

	//set checksum
	P_DEBUG(LEVEL_3, "\t\tFREE_NO_USED\n");
	return (FREE_NO_USED);
}

t_ret_manager	*memory_manager(t_hdr_page *page, size_t blk_size, enum e_types type, t_ret_manager *ret, int count)
{
	t_hdr_blk 		*blk;
	t_hdr_blk 		*free;
	//int 		ret;
	P_DEBUG_VARGS(LEVEL_3, "\t\tstart memory_manager page(%p) count:%d\n",page, ++count);
	if (page == 0)
	{
		ret->value = CREATE_NEW_PAGE;
		P_DEBUG_VARGS(LEVEL_3, "\t\tCREATE NEW PAGE %d\n", CREATE_NEW_PAGE);
		return (ret);
		//return (CREATE_NEW_PAGE);
	}
	ret->page = page;
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 1);
	//free = FIRST_FREE(page);
	free = page->free;
	if (page->free && manage_free_block(page, free, blk_size, MIN_SIZE(type)) == FREE_USED)
	{
		//blk = manage_free_block(free, blk_size);

		ret->value = FREE_USED;
		return (ret);
	}
	if (page->last_blk != 0)
	{
		if (CHK_HEADER(page->last_blk, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 2);
		if ((blk = NEXT_BLK(page->last_blk)) == 0)
		{
			//*page = (*page)->next;
			//return(memory_manager(page, blk_size, type));
			return(memory_manager(page->next, blk_size, type, ret, count));
		}
		P_DEBUG_VARGS(LEVEL_3, "\t\tLAST_BLK:{magenta}%p{eoc}\n", page->last_blk);
		P_DEBUG_VARGS(LEVEL_3, "\t\tLAST_BLK:{magenta}%p{eoc}\n", blk);
		//sleep(5);
		blk->bprev = OFFSET(blk, page->last_blk);

	}
	else
		blk = FIRST_BLK(page);
	blk->size = blk_size;
	P_DEBUG_VARGS(LEVEL_3, "\t\tblk->size:%zd\n", blk->size);
	if ((ret->value = check_space_and_align(page, blk, type)) == CREATE_NEW_BLOCK)
	{
		P_DEBUG(LEVEL_3, "\t\treturn CREATE_NEW_BLOCK\n");
		return (ret);
	}
	else if (ret->value == CREATE_NEW_PAGE)
	{
		P_DEBUG_VARGS(LEVEL_3, "\t\tpour free blk blk->size:%zd, align:%d\n", blk->size, blk->align);
		if (check_align(blk, END_PAGE(page), type == TINY ? 1 : TINY_MAX + 1) == ALIGN)
		{
			blk->size = END_PAGE(page) - NEXT_BLK(page->last_blk) - HDR_BLK_SIZE - blk->align;
			page->nbr_blk++;
			blk->bnext = 0;
			SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE)); //ADD DEBUG
			create_free_blk(blk, page, type);
			//SET_LAST_BLK(page, blk);
			page->last_blk = blk;
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));

			display_hdr_blk(PREV_FBLK(blk));
			P_DEBUG(LEVEL_3, "\n");
			display_hdr_blk(blk);
		}
		return (ret);
	}
	P_DEBUG(LEVEL_3, "\t\tERROR_MEMORY_MANAGER\n");
	ret->page = 0;
	ret->value = ERROR_MEMORY_MANAGER;
	return (ret);
}