/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 09:39:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/12 10:28:28 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void 	forge_block(void *begin, size_t size, void *next, unsigned char flag)
{
	ft_printf("Start forge_block : size:%zu\n", size);
	void *addr;
	//unsigned char *flag; 

	if (begin == NULL)
		return ;
	addr = begin;
	*(unsigned char*)addr = flag;
	addr += FLAG_SIZE;
	*(unsigned long*)addr = (unsigned long)next;
	addr += ADDR_SIZE;
	*(size_t*)addr = size;
	//addr += BLK_SIZE + size;
	addr += BLK_SIZE;
	checksum(begin, STRUCT_BLK_SIZE - CHECKSUM_SIZE, (unsigned char*)addr);
	ft_printf("new checksum[0]:%x\n", *(unsigned char*)(begin + STRUCT_BLK_SIZE - CHECKSUM_SIZE));
	ft_printf("new checksum[1]:%x\n", *(unsigned char*)(begin + STRUCT_BLK_SIZE - CHECKSUM_SIZE + 1));
	ft_printf("END of forge_block\n");
	//*(unsigned long*)addr = CHECKSUM;
}

void	create_block(t_memory *mem, size_t size, int page_size)
{
	void 	*next;
	//unsigned char chkm[2];

	//;odifier +1 en function du type
	//if (mem->current + size + (STRUCT_BLK_SIZE  * 2) + 1 > mem->map + page_size)
	ft_printf("STRUCT_BLK_SIZE:%lu\t+block min:%d\n", STRUCT_BLK_SIZE, (mem->type == TINY ? 1 : TINY + 1));
	if (mem->current + size + (STRUCT_BLK_SIZE  * 2) + (mem->type == TINY ? 1 : TINY_SIZE + 1) > mem->map + page_size)
		next = NULL;
	else
		next = mem->current + STRUCT_BLK_SIZE + size;
	size += next || mem->type == LARGE ? 0 : (mem->map + page_size) - (mem->current + size + STRUCT_BLK_SIZE);
	ft_printf("DEBUG | current:%p\tnext:%p\n",mem->current, next);
	ft_printf("size:%zd\n", size);
	forge_block(mem->current, size, next, 'M');
	ft_printf("avant verif_checksum HEADER_PAGE\n");
	if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
	{
		ft_printf("ABORT create_blk\n");
		exit_abort(mem->map);
	}
	*(size_t*)(mem->map + (ADDR_SIZE * 2)) += size;
	checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE, (unsigned char*)(mem->map + HEADER_SIZE - CHECKSUM_SIZE));
	ft_printf("create_block HEADER new checksum[0]:%x\n", *(unsigned char*)(mem->map + HEADER_SIZE - CHECKSUM_SIZE));
	ft_printf("create_block HEADER new checksum[1]:%x\n", *(unsigned char*)(mem->map + HEADER_SIZE - CHECKSUM_SIZE + 1));

	//g_data.mem_ret = mem->current + FLAG_SIZE + ADDR_SIZE + BLK_SIZE;
	g_data.mem_ret = mem->current + STRUCT_BLK_SIZE;
	ft_printf("addr ret = %p\n", g_data.mem_ret);
	//mem->current += (mem->current + STRUCT_BLK_SIZE + size >= mem->map + page_size) ? 0 : STRUCT_BLK_SIZE + size;
	//mem->current += STRUCT_BLK_SIZE + size;
	ft_printf("DEBUG | fin create_blk, mem->current:%p\n", mem->current);
}

void 	*next_block(void *addr, void *root_page, int page_size)
{
	//unsigned char chkm[2];
	//ft_printf("NEXT BLOCK\n");
	size_t			size;

	if (!addr)
		return (0);
	//ft_printf("avant verif_checksum HEADER_BLOCK\n");
	if (!verif_checksum(addr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
	{
		ft_printf("ABORT next_block\n");
		exit_abort(addr + STRUCT_BLK_SIZE);
	}
	size = *(size_t*)(addr + FLAG_SIZE + ADDR_SIZE);
	//ft_printf("next block size:%zd\n", size);
	//ft_printf("root_page(%p) + page_size(%d)\n", root_page, page_size);
	//ft_printf("root_page + page_size:%p\naddr + STRUCT_BLK_SIZE + size:%p\n", root_page + page_size, addr + STRUCT_BLK_SIZE + size);
	return ((addr + STRUCT_BLK_SIZE + size < root_page + page_size) ? addr + STRUCT_BLK_SIZE + size : 0);
}

enum e_types get_type_block(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size > TINY_SIZE && size <= SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}