#include <malloc.h>

static void 	analyse_map_tiny_small(void *addr, size_t size)
{
	unsigned char *ptr;
	size_t		blk_size;
	ptr = (unsigned char*)addr+HEADER_SIZE;
	//printf("start analyse_block ptr(%p):%c %d\n", ptr, *ptr, *ptr);
	while (ptr)
	{
		//printf("(void*)ptr(%p)\taddr(%p) + size(%zd):(%p)(%c)\n", (void*)ptr, addr, size, addr + size, *ptr);
		if (*ptr == 'M')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				printf("ABORT - analyse_block - M\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			printf("\e[92mM\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
			 					ptr + STRUCT_BLK_SIZE + blk_size - 1, blk_size);
		}
		else if (*ptr == 'F')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				printf("ABORT - analyse_block - F\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			printf("\e[91mF\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
									ptr + STRUCT_BLK_SIZE + blk_size, blk_size);
		}
		else
			return ;
		ptr = next_block(ptr, addr, size);
		//printf("ptr:%p\n", ptr);
	}
	
}

static void	show_alloc_mem_tiny_small(void *root, enum e_types type)
{
	void *map;
	void *current;

	map = root;
	printf("1 map(%p)\n", map);
		while (map)
		{
			printf("2 map(%p)\n", map);
			if (!verif_checksum(map, HEADER_SIZE - CHECKSUM_SIZE))
			{
				printf("ABORT - show_alloc_mem tiny small header page\n");
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
	//printf("start analyse_block ptr(%p):%c %d\n", ptr, *ptr, *ptr);
	if (*ptr == 'M')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				printf("ABORT - analyse_block - M\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			printf("\e[92mM\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
			 					ptr + STRUCT_BLK_SIZE + blk_size - 1, blk_size);
		}
		else if (*ptr == 'F')
		{
			if (!verif_checksum(ptr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				printf("ABORT - analyse_block - F\n");
				exit_abort(ptr + STRUCT_BLK_SIZE);
			}
			blk_size = *(size_t*)(ptr + FLAG_SIZE + ADDR_SIZE);
			printf("\e[91mF\e[39m %p - %p : %zd octects\n", ptr + STRUCT_BLK_SIZE,
									ptr + STRUCT_BLK_SIZE + blk_size, blk_size);
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
		printf("2 map(%p)\n", map);
		if (!verif_checksum(map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			printf("ABORT - show_alloc_mem large header page\n");
			exit_abort(map);
		}
		/*current = map + HEADER_SIZE;
		if (!verif_checksum(current, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
		{
			printf("ABORT - show_alloc_mem large block\n");
			exit_abort(current + STRUCT_BLK_SIZE);
		}*/
		analyse_map_large(map);
		map = (void*)(*(unsigned long*)map);
	}	
}

void	show_alloc_mem(void)
{
	printf("DEBUG - BEGIN show_alloc_mem\n");
	//void *map;
	//void *current;

	if (g_data.mem_tiny.root)
	{
		//map = g_data.mem_tiny.root;
		printf("TINY:\n");
		show_alloc_mem_tiny_small(g_data.mem_tiny.root, g_data.mem_tiny.type);
		
	}
	if (g_data.mem_small.root)
	{
		printf("SMALL:\n");
		show_alloc_mem_tiny_small(g_data.mem_small.root, g_data.mem_small.type);	
	}
	if (g_data.mem_large.root)
	{
		printf("LARGE:\n");
		show_alloc_mem_large(&g_data.mem_large);
	}
}