#include <malloc.h>
#include <signal.h>

static t_memory 			*is_valid_tiny_small(t_memory *mem, void *ptr, int start_limit, int end_limit)
{
	//int i = 1;

	if (!mem || !ptr)
		return (NULL);
	mem->map = mem->root;
	//printf("top_page:%p\t+start:%p\t+end:%p\tptr:%p\n", mem->map, mem->map + start_limit,  mem->map + end_limit, ptr);
	if (mem->map + start_limit <= ptr
		&& mem->map + end_limit > ptr)
		return (mem);
	while (*(unsigned long*)mem->map)
	{
		//printf("boucle index:%d, %p contient %p\n", i++, mem->map, (void*)(*(unsigned long*)mem->map));
		if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			//printf("ABORT free => is_valid\n");
			exit_abort(mem->map);
		}
		//verif_checksum
		mem->map = (void*)(*(unsigned long*)mem->map);
		//printf("new top_page:%p\n", mem->map);
		if (mem->map + start_limit <= ptr
			&& mem->map + end_limit > ptr)
			return (mem);
	}
	//printf("is_valid_tiny_small return NULL\n");
	return (NULL);
}

static t_memory 			*is_valid_large(t_memory *mem, void *ptr)
{
	//int i = 1;

	if (!mem || !ptr)
		return (NULL);
	//mem = &data->mem_large;
	mem->map = mem->root;
	if (mem->map + HEADER_SIZE + STRUCT_BLK_SIZE == ptr)
		return (mem);
	while (*(unsigned long*)mem->map)
	{
		//printf("boucle index:%d, %p\n", i++, (void*)(*(unsigned long*)mem->map));
		//verif_checksum
		if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			//printf("ABORT free for large\n");
			exit_abort(mem->map);
		}
		mem->map = (void*)(*(unsigned long*)mem->map);
		if (mem->map + HEADER_SIZE + STRUCT_BLK_SIZE == ptr)
			return (mem);
		//printf("new top_page:%p\n", (void*)(*(unsigned long*)mem->map));
	}
	return (NULL);
}
static t_memory 	*check_pointer(t_data *data, void *ptr)
{
	//printf("check pointer\n");
	t_memory *mem;
	//int i = 1;

	if (!data)
		return (NULL);
	if (data->mem_tiny.root)
	{
		if ((mem = is_valid_tiny_small(&data->mem_tiny, ptr, HEADER_SIZE + STRUCT_BLK_SIZE,
			TINY_PAGE_SIZE)))
			return (mem);
		/*
		//printf("DEBUG | in check_pointer tiny\n");
		mem = &data->mem_tiny;
		mem->map = mem->root;
		if (mem->map + HEADER_SIZE + (STRUCT_BLK_SIZE - CHECKSUM_SIZE) < ptr
			&& mem->map + TINY_PAGE_SIZE >= ptr)
			return (mem);
		while (*(unsigned long*)mem->map)
		{
			//printf("boucle index:%d, %p\n", i++, (void*)(*(unsigned long*)mem->map));
			mem->map = (void*)(*(unsigned long*)mem->map);
			if (mem->map + HEADER_SIZE + (STRUCT_BLK_SIZE - CHECKSUM_SIZE) < ptr
				&& mem->map + TINY_PAGE_SIZE >= ptr)
				return (mem);
			//printf("new top_page:%p\n", (void*)(*(unsigned long*)mem->map));
		}
		*/
	}
	if (data->mem_small.root)
	{
		if ((mem = is_valid_tiny_small(&data->mem_small, ptr, HEADER_SIZE + STRUCT_BLK_SIZE,
			SMALL_PAGE_SIZE)))
			return (mem);
	}
	if (data->mem_large.root)
	{
		if ((mem = is_valid_large(&data->mem_large, ptr)))
			return (mem);
	}
	return (NULL);
}

void	clear_data(t_data *data)
{
	//printf("clear_data BEGIN\n");
	//void 	*next;
	void *map;

	if (data->mem_tiny.root)
	{
		data->mem_tiny.map = data->mem_tiny.root;
		//printf("next:%s\n", (void*)*(unsigned long*)(data->mem_tiny.map) );
		//while ((next = (void*)*(unsigned long*)(data->mem_tiny.map) ))
		while (*(unsigned long*)(data->mem_tiny.map))
		{
			if (!verif_checksum(data->mem_tiny.map, HEADER_SIZE - CHECKSUM_SIZE))
				break;
			map = (void*)*(unsigned long*)(data->mem_tiny.map);
			munmap(data->mem_tiny.map, TINY_PAGE_SIZE);
			//printf("suppression page\n");
			data->mem_tiny.map = map;
		}
		munmap(data->mem_tiny.root, TINY_PAGE_SIZE);
		//printf("suppression page root\n");
		//memset(&data->mem_tiny, sizeof(t_memory), 0);
	}
	if (data->mem_small.root)
	{

	}
	if (data->mem_large.root)
	{

	}
	//printf("%c\n", *(unsigned char*)data->mem_tiny.root);
	//printf("end clear_data\n");
}

void exit_abort(void *ptr)
{
	if (ptr)
		ft_printf("malloc: *** error for object %p: pointer being freed was not allocated\n", ptr);
	clear_data(&g_data);
	//kill(0, SIGABRT);
}

void free(void *ptr)
{
	//write(1, "FREE\n", 5);
	ft_printf("FREE\n");
	//sleep(2);
	//unsigned char 	chkm[2];
	t_memory 		*mem;
	//size_t 			size;
	ft_printf("DEBUG | BEGIN FREE => ptr:%p\n", ptr);
	if (!ptr)
	{

		ft_printf("return\n");
		return ;
	}
	//printf("apres\n");
	//write(1, "gooo\n", 5);
	//verifier si addr est valide
	if (!(mem = check_pointer(&g_data, ptr)))
	{
		ft_printf("ABORT free check_pointer\n");
		return(exit_abort(ptr));
	}
	if (!verif_checksum(ptr - STRUCT_BLK_SIZE, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
	{
		//printf("ABORT free checksum block error\n");
		return(exit_abort(ptr));
	}
	if (*(unsigned char*)(ptr - STRUCT_BLK_SIZE) == 'F')
	{
		//printf("DOUBLE FREE\n");
		return(exit_abort(ptr));
	}
	*(unsigned char*)(ptr - STRUCT_BLK_SIZE) = 'F';
	checksum(ptr - STRUCT_BLK_SIZE, STRUCT_BLK_SIZE - CHECKSUM_SIZE, ptr - CHECKSUM_SIZE);
	if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
	{
		//printf("ABORT free checksum map error \n");
		return(exit_abort(ptr));
	}
	//(!mem->free) ? (mem->free = ptr - STRUCT_BLK_SIZE) : 0;
	//mem->free = (mem->free > ptr - STRUCT_BLK_SIZE) ? ptr - STRUCT_BLK_SIZE : mem->free;
	//mem->current = mem->free;
	//printf("mem->current:%p\n", mem->current);
	//printf("OCTECTS RESTANT 1:%zd\n", *(size_t*)(mem->map + ADDR_SIZE * 2));
	*(size_t*)(mem->map + ADDR_SIZE * 2) -= *(size_t*)(ptr - BLK_SIZE - CHECKSUM_SIZE);
	checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE, mem->map + HEADER_SIZE - CHECKSUM_SIZE);
	//printf("OCTECTS RESTANT 2:%zd\n", *(size_t*)(mem->map + ADDR_SIZE * 2));
	if (*(size_t*)(mem->map + ADDR_SIZE * 2) == 0)
	{
		//remplacer free = NULL par function get_next_free
		//mem->free = NULL;
		//printf("GO MUNMAP\n");
		//si octect malloc == 0 alors mummap et raccorder les autres pages; 
		void *prev;
		void *next;

		prev = (void*)*(unsigned long*)(mem->map + ADDR_SIZE);
		next = (void*)*(unsigned long*)mem->map;
		if (!prev)
		{
			//printf("PREV == NULL => mem->root = next(%p)\troot(%p);\n", next, mem->root);
			if ((mem->root = next))
			{
				if (!verif_checksum(next, HEADER_SIZE - CHECKSUM_SIZE))
				{
					//printf("ABORT free munmap next and prev==NULL\n");
					return(exit_abort(ptr));
				}
				*(unsigned long*)(next + ADDR_SIZE) = (unsigned long)prev;
				checksum(next, HEADER_SIZE - CHECKSUM_SIZE, next + ADDR_SIZE * 2 + ALLOC_SIZE);
			}	
		}
		else
		{
			if (next)
			{
				//printf("PREV(%p) && NEXT(%p)\n", prev, next);
				if (!verif_checksum(next, HEADER_SIZE - CHECKSUM_SIZE) || !verif_checksum(prev, HEADER_SIZE- CHECKSUM_SIZE))
				{
					//printf("ABORT free munmap join next and prev page\n");
					return(exit_abort(ptr));
				}
				*(unsigned long*)(next + ADDR_SIZE) = (unsigned long)prev;
				checksum(next, HEADER_SIZE - CHECKSUM_SIZE, next + ADDR_SIZE * 2 + ALLOC_SIZE);
			}
			else
			{
				//printf("PREV(%p) && NEXT == NULL\n", prev);
				if (!verif_checksum(prev, HEADER_SIZE- CHECKSUM_SIZE))
				{
					//printf("ABORT free munmap join prev page\n");
					return(exit_abort(ptr));
				}
			}
			*(unsigned long*)(prev) = (unsigned long)next;
			checksum(prev, HEADER_SIZE - CHECKSUM_SIZE, prev + ADDR_SIZE * 2 + ALLOC_SIZE);
		}
		munmap(mem->map, get_map_size(mem->type));
		mem->current = mem->root + HEADER_SIZE;
		mem->map = mem->root;
	}
	show_alloc_mem();
}
