/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/09 21:38:29 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void	kill_prog(int flag, int count)
{
	//clear data
	if (flag == CHECKSUM_CORRUPED)
	{
		P_DEBUG_VARGS(LEVEL_1, "CHECKSUM_CORRUPED Numero:%d\n", count);
	}
	kill(0, SIGABRT);
}

void	manage_large(t_hdr_page *page, size_t size)
{
	t_hdr_blk	*blk;
	P_DEBUG_VARGS(LEVEL_3, "\t\tmanage_large => size:%zd\n", size);
	if (!page)
		return ;
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 18);
	blk = FIRST_BLK(page);
	if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
			kill_prog(CHECKSUM_CORRUPED, 19);
	if (blk->size == 0)
	{
		P_DEBUG_VARGS(LEVEL_3, "\t\tmanage_large => avant creation de block : size:%zd\n", size);
		blk->size = size;
		create_new_block(blk, page);
		SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
		g_data.mem_ret = BEGIN_BLK(blk);
	}
	else
	{
		if (!page->next)
		{
			initialize_page((t_hdr_page**)&page->next,page, LARGE_SIZE(size));
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
		}
		return(manage_large(page->next, size));
	}
}

void 	*malloc(size_t size)
{
	//ft_printf("FD:%d\n", g_fd);
	//OPEN_DEBUG();
	//ft_dprintf(g_fd, "FD:%d\n", g_fd);
	P_DEBUG_VARGS(LEVEL_1, "{GREEN}MALLOC{EOC}\tsize:%d octets\n", size);
	//CLOSE_DEBUG();
	t_memory			*mem;
	enum e_types		type;

	type = type_block(size);
	mem = memory_by_type(&g_data, type);
	if (mem->page == NULL)
		initialize_memory(mem, type, size);
	//manage_tiny_small(mem->page, size, mem->type);
	(type == LARGE) ? manage_large(mem->page, size)
					: manage_tiny_small(mem->page, size, mem->type);
	//(DEBUG) ? show_alloc_mem() : 0;
	P_DEBUG_VARGS(LEVEL_1, "\tblock created at %p\n", g_data.mem_ret);
	//CLOSE_DEBUG();
	return (g_data.mem_ret);
}

int		main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	int i = 0;
	int x = 120;
	void *ptr[x];
	while (i < x)//7875)
		ptr[i++] = malloc(15);
	i = 0;
	while (i < x)//7875)
		free(ptr[i++]);

	//malloc(16);
	i = 0;
	while (i < x)//7875)
		ptr[i++] = malloc(1024);
	i = 0;
	while (i < x)//7875)
		free(ptr[i++]);
	ptr[1] = malloc(1023);
	ptr[1] = realloc(ptr[1], 16);
	ft_printf("ptr:%p\n", ptr[1]);
	show_alloc_mem();
	ptr[1] = realloc(ptr[1], 1023);
	ft_printf("ptr:%p\n", ptr[1]);
	show_alloc_mem();
	ptr[1] = realloc(ptr[1], 1025);
	ft_printf("ptr:%p\n", ptr[1]);
	show_alloc_mem();
	ptr[2] = malloc(16);
	ptr[2] = realloc(ptr[2], 1020);
	ft_printf("ptr:%p\n", ptr[2]);
	show_alloc_mem();
	ptr[3] = malloc(8);
	ptr[3] = realloc(ptr[3], 9);
	ft_printf("ptr:%p\n", ptr[3]);
	show_alloc_mem();
	free(malloc(14));
	free(malloc(15));
	show_alloc_mem();
	//return (1);

	ptr[4] = malloc(15);
	//changer 3 par 4
	ptr[4] = realloc(ptr[4], 16);
	ft_printf("ptr:%p\n", ptr[4]);
	show_alloc_mem();
	return (0);
	//free(malloc(15));
	/*malloc(1024);
	malloc(1024);
	malloc(1024);
	malloc(1024);
	show_alloc_mem();
	ptr[0] = malloc(1024);
	malloc(1024);

	free(ptr[0]);*/
	/*ptr[0] = malloc(15);
	ptr[1] = malloc(15);
	ptr[2] = malloc(15);
	ptr[3] = malloc(15);
	ptr[4] = malloc(15);
	free(ptr[1]);

	free(ptr[2]);
	free(ptr[0]);
	free(ptr[3]);
	free(ptr[4]);*/


	//ptr[1] = malloc(15);
	//ptr[1] = malloc(15);

	//free(ptr[2]);

	return 0;
}