/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 09:44:27 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/12 17:17:51 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_memory *get_memory_by_type(t_data *data, enum e_types type)
{
	if (type == TINY)
		return (&data->mem_tiny);
	else if (type == SMALL)
		return (&data->mem_small);
	else
		return (&data->mem_large);
}

static void	manage_tiny_small(t_memory *mem, size_t size)
{
	int 	ret;
	size_t 	map_size;

	if (!mem)
		return ;
	map_size = get_map_size(mem->type);
	//mem->current = mem->free ? mem->free : mem->current;
	//mem->current = mem->free < mem->next_zero ? mem->free : mem->next_zero;
	mem->current = mem->root + HEADER_SIZE;
	if ((ret = memory_manager(mem, mem->root, &size, map_size) == 1))
		create_block(mem, size, get_map_size(mem->type));
	else if (ret == 0)
	{
		ft_printf("exit 1 => mem->map(%p)\tmem->current(%p)\n", mem->map, mem->current);
		ft_printf("DEBUG | CREER SET NEW MAP\n");
		set_next_map(mem->map, map_size);
		ft_printf("%p\n", (void*)*((unsigned long*)mem->map));
		mem->map = (void*)*((unsigned long*)mem->map);
		mem->current = mem->map + HEADER_SIZE;
		ft_printf("apres:%p\n", mem->current);
		create_block(mem, size, map_size);
	}
}

static void	fix_map(void **map)
{
	int 	ret;

	if (!map || !*map)
		return ;
	while ((ret = verif_checksum(*map, HEADER_SIZE - CHECKSUM_SIZE)) && *(unsigned long*)(*map))
		*map = (void*)*(unsigned long*)(*map);
	if (!ret)
	{
		ft_printf("ABORT fix map\n");
		exit_abort(*map);
	}
}

static void	manage_large(t_memory *mem, size_t size)
{
	static int i;
	//int ret;

	ft_printf("2 size:%zd\n", size);
	if (!mem)
		return ;
	mem->current = mem->root + HEADER_SIZE;
	if (i++ == 0 && *(unsigned long *)mem->root == 0)
		create_block(mem, size, size);
	else
	{
		fix_map(&mem->map);
		ft_printf("mem->map(%p)\tmem->current(%p)\n", mem->map, mem->current);
		ft_printf("DEBUG | CREER NEW MAP\n");
		set_next_map(mem->map, size + HEADER_SIZE + STRUCT_BLK_SIZE);
		ft_printf("%p\n", (void*)*((unsigned long*)mem->map));
		mem->map = (void*)*((unsigned long*)mem->map);
		mem->current = mem->map + HEADER_SIZE;
		ft_printf("apres:%p\n", mem->current);
		create_block(mem, size, size);
	}
	i = (i >= 1) ? 1 : 0;
}

void *malloc(size_t size)
{
	ft_printf("printf MALLOC\n");
	write(1, "MALLOC\n", 7);
	t_memory			*mem;
	enum e_types		type;

	//#ifndef NDEBUG
		ft_printf("DEBUG | BEGIN MALLOC\n");
		ft_printf("size:'%zd'\n", size);
		ft_printf("tiny:'%p'\n", &g_data.mem_tiny);
		ft_printf("\troot:'%p'\n", g_data.mem_tiny.root);
		ft_printf("\tcurrent:'%p'\n", g_data.mem_tiny.current);
		ft_printf("small:'%p'\n", &g_data.mem_small);
		ft_printf("\troot:'%p'\n", g_data.mem_small.root);
		ft_printf("\tcurrent:'%p'\n", g_data.mem_small.current);
		ft_printf("large:'%p'\n", &g_data.mem_large);
		ft_printf("\troot:'%p'\n", g_data.mem_large.root);
		ft_printf("\tcurrent:'%p'\n", g_data.mem_large.current);
	//#endif
	type = get_type_block(size);
	mem = get_memory_by_type(&g_data, type);
	write(1, "MALLOC2\n", 8);
	if (mem->root == NULL)
	{
		//size_t *ptr;
		mem->root = get_map(mem->root, type == LARGE ? 
			size + HEADER_SIZE + STRUCT_BLK_SIZE : get_map_size(type));
		mem->map = mem->root;
		mem->current = mem->root + HEADER_SIZE;
		mem->type = type;
		checksum(mem->root, HEADER_SIZE - CHECKSUM_SIZE, (unsigned char *)(mem->current - CHECKSUM_SIZE));
		//#ifndef NDEBUG
			ft_printf("DEBUG | NEW MAP mem:'%p'\n", mem);
			ft_printf("DEBUG | NEW MAP mem:->root:'%p'\n", mem->root);
			ft_printf("DEBUG | mem:->top:'%p'\n", mem->map);
			ft_printf("DEBUG | NEW MAP mem:->current:'%p'\n", mem->current);
			ft_printf("%x%x\n", *(unsigned char *)(mem->current - CHECKSUM_SIZE), *(unsigned char *)(mem->current - CHECKSUM_SIZE + 1));
			//sleep(5);
		//#endif
	}
	/*
	#ifndef NDEBUG
		dprintf(1, "DEBUG | mem:'%p'\n", mem);
		dprintf(1, "DEBUG | mem:->root:'%p'\n", mem->root);
		dprintf(1, "DEBUG | mem:->top:'%p'\n", mem->map);
		dprintf(1, "DEBUG | mem:->current:'%p'\n", mem->current);
		dprintf(1, "octect alloc:%zd\t%d\t%zd\n", *(size_t*)(mem->root + ADDR_SIZE * 2), get_map_size(type), size);
		//sleep(1);
	#endif
		*/
	//printf("1 size:%zd\n", size);
		write(1, "MID MALLOC\n", 11);
	(type == LARGE) ? manage_large(mem, size) : manage_tiny_small(mem, size); 
	//print_map(mem->map, mem->type == LARGE ? size : get_map_size(mem->type));
	//print_map(mem->current, STRUCT_BLK_SIZE + size);
	show_alloc_mem();
	write(1, "FIN MALLOC\n", 11);
	return (g_data.mem_ret);
}
