#include <malloc.h>

static t_memory 	*check_pointer(t_data *data, void *ptr)
{
	t_memory *mem;
	int i = 1;
	if (!data)
		return (NULL);
	if (data->mem_tiny.root)
	{
		printf("DEBUG | in check_pointer tiny\n");
		mem = &data->mem_tiny;
		mem->top_page = mem->root;
		if (mem->top_page + HEADER_SIZE + (STRUCT_BLK_SIZE - CHECKSUM_SIZE) < ptr
			&& mem->top_page + TINY_PAGE_SIZE >= ptr)
			return (mem);
		while (*(unsigned long*)mem->top_page)
		{
			printf("boucle index:%d, %p\n", i++, (void*)(*(unsigned long*)mem->top_page));
			mem->top_page = (void*)(*(unsigned long*)mem->top_page);
			if (mem->top_page + HEADER_SIZE + (STRUCT_BLK_SIZE - CHECKSUM_SIZE) < ptr
				&& mem->top_page + TINY_PAGE_SIZE >= ptr)
				return (mem);
			printf("new top_page:%p\n", (void*)(*(unsigned long*)mem->top_page));
		}
	}
	return (NULL);
	if (data->mem_small.root)
	{
		
	}
	if (data->mem_large.root)
	{
		
	}
}

void free1(void *ptr)
{
	unsigned char 	chkm[2];
	t_memory 		*mem;
	size_t 			size;
	printf("DEBUG | BEGIN FREE => ptr:%p\n", ptr);
	if (!ptr)
		return ;
	//verifier si addr est valide
	if (!(mem = check_pointer(&g_data, ptr)))
	{
		printf("addr non valide\n");
		exit(1);
	}
	size = *(size_t*)(ptr - BLK_SIZE);
	if (ptr + size + CHECKSUM_SIZE > mem->top_page + get_map_size(mem->type))
	{
		printf("ABORT 1\n");
		exit(1);
	}
	checksum(ptr - BLK_SIZE - ADDR_SIZE - FLAG_SIZE, STRUCT_BLK_SIZE - CHECKSUM_SIZE, chkm);
	//#ifndef NDEBUG
		printf("checksum[0]:%x\n", chkm[0]);
		printf("checksum[1]:%x\n", chkm[1]);
		printf("checksum_blk[0]:%x\t%p\n", *(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE)), (unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE)));
		printf("checksum_blk[1]:%x\t%p\n", *(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE) + 1), (unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE) + 1));
		//sleep(5);
	//#endif
	if (*(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE)) == chkm[0]
		&& *(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE) + 1) == chkm[1])
	{
		if (*(unsigned char*)(ptr - BLK_SIZE - ADDR_SIZE - FLAG_SIZE) == 'F')
		{
			printf("DOUBLE FREE\n");
			exit(1);
		}
		*(unsigned char*)(ptr - BLK_SIZE - ADDR_SIZE - FLAG_SIZE) = 'F';
		//recalculer checksum et le modifier
		checksum(ptr - (STRUCT_BLK_SIZE - CHECKSUM_SIZE), STRUCT_BLK_SIZE - CHECKSUM_SIZE, ptr + *(size_t*)(ptr - BLK_SIZE));
		//*(size_t*)(*(unsigned long*)(ptr - BLK_SIZE - ADDR_SIZE) + (ADDR_SIZE * 2)) -= *(size_t*)(ptr - BLK_SIZE);
		*(size_t*)(mem->top_page + HEADER_SIZE - OCTET_ALLOC) -= *(size_t*)(ptr - BLK_SIZE);
		//if (*(size_t*)(mem->top_page + HEADER_SIZE - OCTET_ALLOC) == 0)
			//si octect malloc == 0 alors mummap et raccorder les autres pages; 
	}
	else
	{
		//abort
		printf("ABORT 2\n");
		exit(1);
	}

}