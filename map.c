#include <malloc.h>

//void set_next_map(void *addr, enum e_types type)
void 	set_next_map(void *addr, size_t size)
{
	void			*new;
	//size_t			size;
	unsigned long	*ptr_addr;
	size_t			*ptr_size;

	//size = get_map_size(type);
	if (!verif_checksum(addr, HEADER_SIZE - CHECKSUM_SIZE))
	{
		printf("ABORT set_next_map\n");
		exit(1);
	}
	new = get_map(addr, size);
	//ptr_size = new + sizeof(unsigned long);
	//*ptr_size = size;
	ptr_addr = (unsigned long*)addr;
	*ptr_addr = (unsigned long)new;
	checksum(addr, HEADER_SIZE - CHECKSUM_SIZE, (unsigned char*)(addr + ADDR_SIZE * 2 + ALLOC_SIZE));
	//new += ADDR_SIZE;
	*(unsigned long*)(new + ADDR_SIZE) = (unsigned long)addr;
	checksum(new, HEADER_SIZE - CHECKSUM_SIZE, (unsigned char*)(new + ADDR_SIZE * 2 + ALLOC_SIZE));
	printf("new checksum[0]:%x\n", *(unsigned char*)(new + HEADER_SIZE - CHECKSUM_SIZE));
	printf("new checksum[1]:%x\n", *(unsigned char*)(new + HEADER_SIZE - CHECKSUM_SIZE + 1));
	printf("NEXT PAGE:%p\n", (void*)*(unsigned long*)new);
	printf("PREV PAGE:%p\n", (void*)*(unsigned long*)(new+sizeof(void*)));
}


void	*get_map(void *addr, size_t size)
{
	if ((addr = mmap(NULL, size, PROT_WRITE | PROT_READ,\
			MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
	perror("Allocate page error");
	return (NULL);
	}
	//mem->current = mem->root + sizeof(unsigned long);
	return (addr);
}

int 	get_map_size(enum e_types type)
{
	if (type == TINY)
		return (TINY_PAGE_SIZE);
	else if (type == SMALL)
		return (SMALL_PAGE_SIZE);
	return (-1);
}

void 	print_map(void *page, size_t size)
{
	int i;
	unsigned char *ptr;

	ptr = (unsigned char*)page;
	i = 0;
	if (!page)
	return ;
	while (i < size)
	{
	printf("index:%d => %p(%c)(%d)(x%x)\n", i, &ptr[i], ptr[i], ptr[i], ptr[i]);
	i++;
	}
}
