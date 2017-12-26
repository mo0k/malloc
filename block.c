#include <malloc.h>

void 	forge_block(void *begin, size_t size, void *next, unsigned char flag)
{
	printf("Start forge_block : size:%zu\n", size);
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
	printf("new checksum[0]:%x\n", *(unsigned char*)(begin + STRUCT_BLK_SIZE - CHECKSUM_SIZE));
	printf("new checksum[1]:%x\n", *(unsigned char*)(begin + STRUCT_BLK_SIZE - CHECKSUM_SIZE + 1));
	printf("END of forge_block\n");
	//*(unsigned long*)addr = CHECKSUM;
}

void	create_block(t_memory *mem, size_t size, int page_size)
{
	void 	*next;
	//unsigned char chkm[2];

	if (mem->current + size + (STRUCT_BLK_SIZE  * 2) + 1 > mem->top_page + page_size)
		next = NULL;
	else
		next = mem->current + STRUCT_BLK_SIZE + size;
	size += next ? 0 : (mem->top_page + page_size) - (mem->current + size + STRUCT_BLK_SIZE);
	printf("DEBUG | current:%p\tnext:%p\n",mem->current, next);
	printf("size:%zd\n", size);
	forge_block(mem->current, size, next, 'M');
	printf("avant verif_checksum HEADER_PAGE\n");
	if (!verif_checksum(mem->top_page, HEADER_SIZE - CHECKSUM_SIZE))
	{
		printf("ABORT create_blk\n");
		exit(1);
	}
	*(size_t*)(mem->top_page + (ADDR_SIZE * 2)) += size;
	checksum(mem->top_page, HEADER_SIZE - CHECKSUM_SIZE, (unsigned char*)(mem->top_page + HEADER_SIZE - CHECKSUM_SIZE));
	printf("create_block new checksum[0]:%x\n", *(unsigned char*)(mem->top_page + HEADER_SIZE - CHECKSUM_SIZE));
	printf("create_block new checksum[1]:%x\n", *(unsigned char*)(mem->top_page + HEADER_SIZE - CHECKSUM_SIZE + 1));

	//g_data.mem_ret = mem->current + FLAG_SIZE + ADDR_SIZE + BLK_SIZE;
	g_data.mem_ret = mem->current + STRUCT_BLK_SIZE;
	printf("addr ret = %p\n", g_data.mem_ret);
	mem->current += (mem->current + STRUCT_BLK_SIZE + size >= mem->top_page + page_size) ? 0 : STRUCT_BLK_SIZE + size;
	//mem->current += STRUCT_BLK_SIZE + size;
	printf("DEBUG | fin create_blk, mem->current:%p\n", mem->current);
}

void 	*next_block(void *addr, void *root_page, int page_size)
{
	//unsigned char chkm[2];
	size_t			size;

	if (!addr)
		return (0);
	printf("avant verif_checksum HEADER_BLOCK\n");
	if (!verif_checksum(addr, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
	{
		printf("ABORT next_block\n");
		exit(1);
	}
	size = *(size_t*)(addr + FLAG_SIZE + ADDR_SIZE);
	printf("size:%zd\n", size);
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