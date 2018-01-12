#include <malloc.h>

static int		analyze_memory(t_memory *mem, size_t *size, size_t map_size, size_t *sum)
{
	if (*(unsigned char*)mem->current == 0)
		return (mem->current + STRUCT_BLK_SIZE + *size < mem->map + map_size \
				? 1 : -1);
	else if (*(unsigned char*)mem->current == 'M' && ((sum = 0) || 1))
		return ((mem->current = next_block(mem->current, mem->map, map_size)) \
				? 0 : -1);
	else if (*(unsigned char*)mem->current == 'F')
		return (manage_block_free(mem, size, map_size, sum));
	else
	{
		//changer pour exit_abort ou return (1);
		return (1);
		return (-1);
	}
}

int		memory_manager(t_memory *mem, void *addr, size_t *size, size_t map_size)
{
	ft_printf("DEBUG memory_manager\n");
	size_t	sum;
	int 	ret;

	if (!mem || !size)
		return (-1);
	sum = 0;
	//ft_printf("mem->map:%p\taddr:%p\n", mem->map, addr);
	mem->map = addr;
	print_map(mem->current, 50);
	while (mem->current < mem->map + map_size)
	{
		//ft_printf("fix mem->current:%p(%c)\n", mem->current, *(unsigned char*)mem->current);
		if ((ret = analyze_memory(mem, size, map_size, &sum)) == -1)
			break ;
		else if (ret == 1)
			return (1);
	}
	ft_printf("mem->map:%p\t*mem->map:%lu\n", mem->map, *(unsigned long*)(mem->map));
	if (*(unsigned long*)(mem->map) != 0L)
	{
		if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			ft_printf("ABORT memory_manager\n");
			exit_abort(mem->map);
		}
		ft_printf("PAR LA recursion\n");
		mem->current = (void*)*((unsigned long*)(mem->map)) + HEADER_SIZE;
		return (memory_manager(mem, (void*)*((unsigned long*)(mem->map)), size, map_size));
	}
	ft_printf("mem->current:%p\tmem->map:%p\n", mem->current, mem->map);
	mem->current = mem->map;
	return (0);
}

int 	manage_block_free(t_memory *mem, size_t *size, size_t map_size, size_t *sum)
{
	static void	*ptr_current;

	if (!verif_checksum(mem->current, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
	{
		ft_printf("ABORT manage_block_free\n");
		exit_abort(mem->current + STRUCT_BLK_SIZE);
	}
	(*sum == 0) ? ptr_current = mem->current : 0;
	*sum += (*sum == 0) ? 0 : STRUCT_BLK_SIZE;
	*sum += *(size_t*)(mem->current + FLAG_SIZE + ADDR_SIZE);
	if (*sum >= *size)
	{
		//mem->current = ptr_current;
		if (*sum > *size)
		{
			ft_printf("*sum:%zd\tsize:%zd\tstruct_size:%lu\n", *sum, *size, STRUCT_BLK_SIZE);
			if (*sum - *size >= STRUCT_BLK_SIZE + 
								(mem->type == SMALL ? TINY_SIZE + 1: 1))
			{
				size_t size_temp = (*sum - *size) - STRUCT_BLK_SIZE;
					ft_printf("place suffisante pour new block => size_temp:%zd\n", size_temp);
				if (size_temp <= (mem->type == SMALL ? SMALL_SIZE : TINY_SIZE))
				{
					mem->current = ptr_current;
					forge_block(mem->current + *size + STRUCT_BLK_SIZE, size_temp,
					mem->current + *size + (STRUCT_BLK_SIZE * 2) + size_temp, 'F');
					return (1);
				}
				
			}
			else
			{
				ft_printf("place insuffisante pour new block\n");
				//optimiser en regardant next
				//if (*size + (*sum - *size) <= (mem->type == SMALL ? TINY_SIZE + 1: 1))
				//if (*size + (*sum - *size) <= (mem->type == SMALL ? SMALL_SIZE : TINY_SIZE))
				void *next = next_block(mem->current, mem->map, map_size);
				if (next && !verif_checksum(next, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
				{
					ft_printf("abort manage_block_free fusion\n");
					exit_abort(next + STRUCT_BLK_SIZE);
				}
				ft_printf("diff:%zd\n", *size + (*sum - *size));
				if (!next || (*(unsigned char*)next == 'M' &&
					*size + (*sum - *size) <= (mem->type == SMALL ? SMALL_SIZE : TINY_SIZE)))//taille inferieur a min / type))
				{
					*size += *sum - *size;
					return (1);
				}
				else
				{
					ft_printf("BREAKKKKKKKKKKKKK\n");
				}
			}
			//sleep(5);
		}
		else if (*sum == *size)
			return (1);
		//sum = 0;
		//return (1);
	}
	mem->current = next_block(mem->current, mem->map, map_size);
	ft_printf("PAR LA quand meme current:%p(%c)\n", mem->current, *(unsigned char*)mem->current);
	//sleep(5);
	//if (mem->current == mem->map + map_size)
	if (!mem->current)
	{
		ft_printf("par la 1234\n");
		*sum = 0;
		//break ;
		return (-1);
	}
	return (0);
}
