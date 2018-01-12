/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 09:42:37 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/12 11:43:30 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void 	analyse_map_tiny_small(void *addr, size_t size)
{
	unsigned char *ptr;
	size_t		blk_size;
	ptr = (unsigned char*)addr+HEADER_SIZE;
	//ft_printf("start analyse_block ptr(%p):%c %d\n", ptr, *ptr, *ptr);
	while (ptr)
	{
		//ft_printf("(void*)ptr(%p)\taddr(%p) + size(%zd):(%p)(%c)\n", (void*)ptr, addr, size, addr + size, *ptr);
		if (*ptr == 'M')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				ft_printf("ABORT - analyse_block - M\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			ft_printf("\e[92mM\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
			 					ptr + STRUCT_BLK_SIZE + blk_size - 1, blk_size);
		}
		else if (*ptr == 'F')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				ft_printf("ABORT - analyse_block - F\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			ft_printf("\e[91mF\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
									ptr + STRUCT_BLK_SIZE + blk_size - 1, blk_size);
		}
		else
			return ;
		ptr = next_block(ptr, addr, size);
		//ft_printf("ptr:%p\n", ptr);
	}
	
}

static void	show_alloc_mem_tiny_small(void *root, enum e_types type)
{
	void *map;
	//void *current;

	map = root;
	ft_printf("1 map(%p)\n", map);
		while (map)
		{
			ft_printf("2 map(%p)\n", map);
			if (!verif_checksum(map, HEADER_SIZE - CHECKSUM_SIZE))
			{
				ft_printf("ABORT - show_alloc_mem tiny small header page\n");
				exit_abort(map);
			}
			//current = map + HEADER_SIZE;
			analyse_map_tiny_small(map, get_map_size(type));
			map = (void*)(*(unsigned long*)map);
		}	
}

static void 	analyse_map_large(void *addr)
{
	unsigned char *ptr;
	size_t		blk_size;
	ptr = (unsigned char*)addr+HEADER_SIZE;
	//ft_printf("start analyse_block ptr(%p):%c %d\n", ptr, *ptr, *ptr);
	if (*ptr == 'M')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				ft_printf("ABORT - analyse_block - M\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			ft_printf("\e[92mM\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
			 					ptr + STRUCT_BLK_SIZE + blk_size - 1, blk_size);
		}
		else if (*ptr == 'F')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				ft_printf("ABORT - analyse_block - F\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			ft_printf("\e[91mF\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
									ptr + STRUCT_BLK_SIZE + blk_size - 1, blk_size);
		}
		else
			return ;	
}

static void show_alloc_mem_large(t_memory *mem)
{
	void *map;
	//void *current;

	if (!mem)
		return ;
	map = mem->root;
	while (map)
	{
		ft_printf("2 map(%p)\n", map);
		if (!verif_checksum(map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			ft_printf("ABORT - show_alloc_mem large header page\n");
			exit_abort(map);
		}
		/*current = map + HEADER_SIZE;
		if (!verif_checksum(current, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
		{
			ft_printf("ABORT - show_alloc_mem large block\n");
			exit_abort(current + STRUCT_BLK_SIZE);
		}*/
		analyse_map_large(map);
		map = (void*)(*(unsigned long*)map);
	}	
}

void	show_alloc_mem(void)
{
	ft_printf("DEBUG - BEGIN show_alloc_mem\n");
	//void *map;
	//void *current;

	if (g_data.mem_tiny.root)
	{
		//map = g_data.mem_tiny.root;
		ft_printf("TINY:\n");
		show_alloc_mem_tiny_small(g_data.mem_tiny.root, g_data.mem_tiny.type);
		
	}
	if (g_data.mem_small.root)
	{
		ft_printf("SMALL:\n");
		show_alloc_mem_tiny_small(g_data.mem_small.root, g_data.mem_small.type);	
	}
	if (g_data.mem_large.root)
	{
		ft_printf("LARGE:\n");
		show_alloc_mem_large(&g_data.mem_large);
	}
}