/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 23:13:58 by mo0ky             #+#    #+#             */
/*   Updated: 2017/12/16 00:07:14 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

void print_page(void *page, size_t size);
enum e_types get_type(size_t size);
void *get_map(void *addr, size_t size);
void forge_block(void *addr_begin, size_t size, void *root);
void set_next_map(void *addr, enum e_types type);
int	available_space(t_memory *mem, void *addr, enum e_types mem_type, size_t size);
void calcul_checksum(void *addr, unsigned char *checksum);

int main(int ac, char **av)
{
	/*
	char *ptr;
	int i = 0;
	while (++i < 200)
	{
		ptr = malloc1(16);
		if (!ptr)
		{
			printf("i:%d\n", i);
			exit(127);
			printf("malloc ok\n");
		}
		else
		{
			strcpy(ptr, "coco");
			printf("Copye de 'coco' at %p => %s\n", ptr, 	ptr);
			//sleep(2);
		}
	}
	*/
	char *ptr1;
	char *ptr2;
	char *ptr3;
	char *ptr4;
	char *ptr5;

	ptr1 = malloc1(2); 	
	printf("ptr1:%p\n", ptr1);
	ptr2 = malloc1(8);
	printf("ptr2:%p\n", ptr2);
	ptr3 = malloc1(8);
	printf("ptr3:%p, ptr2 - 4:%p, char:%c\n", ptr3, ptr2 - 4, *(ptr2 - (STRUCT_BLK_SIZE - CHECKSUM_SIZE)));
	sleep(5);
	*(ptr2 - (STRUCT_BLK_SIZE - CHECKSUM_SIZE)) = 'F';
	free1(1024);
	free1(ptr3);
	ptr4 = malloc1(16);
	printf("ptr4:%p\n", ptr4);
	ptr5 = malloc1(16);
	printf("ptr4:%p\n", ptr5);
	/*int i = 0;
	while (++i)
	{
		ptr1 = malloc1(16);
		if (!ptr1)
		{
			printf("i:%d\n", i);
			exit(127);
			printf("malloc ok\n");
		}
		else
		{
			strcpy(ptr1, "coco");
			printf("Copye de 'coco' at %p => %s\n", ptr1, 	ptr1);
			sleep(2);
		}
	}*/
	return (0);
}

t_memory *get_memory_by_type(t_data *data, enum e_types type)
{
	if (type == TINY)
		return (&data->mem_tiny);
	else if (type == SMALL)
		return (&data->mem_small);
	else
		return (&data->mem_large);
}

int get_page_size(enum e_types type)
{
	if (type == TINY)
		return (TINY_PAGE_SIZE);
	else if (type == SMALL)
		return (SMALL_PAGE_SIZE);
	return (-1);
}
t_memory 	*check_pointer(t_data *data, void *ptr)
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
	unsigned char 	checksum[2];
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
	if (ptr + size + CHECKSUM_SIZE > mem->top_page + get_page_size(mem->type))
	{
		printf("ABORT 1\n");
		exit(1);
	}
	calcul_checksum(ptr - BLK_SIZE - ADDR_SIZE - FLAG_SIZE, checksum);
	//#ifndef DEBUG
		printf("checksum[0]:%x\n", checksum[0]);
		printf("checksum[1]:%x\n", checksum[1]);
		printf("checksum_blk[0]:%x\t%p\n", *(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE)), (unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE)));
		printf("checksum_blk[1]:%x\t%p\n", *(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE) + 1), (unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE) + 1));
		sleep(5);
	//#endif
	if (*(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE)) == checksum[0]
		&& *(unsigned char*)(ptr + *(size_t*)(ptr - BLK_SIZE) + 1) == checksum[1])
	{
		*(unsigned char*)(ptr - BLK_SIZE - ADDR_SIZE - FLAG_SIZE) = 'F';
		//recalculer checksum et le modifier
		calcul_checksum(ptr - (STRUCT_BLK_SIZE + CHECKSUM_SIZE), ptr + *(size_t*)(ptr - BLK_SIZE));
		//*(size_t*)(*(unsigned long*)(ptr - BLK_SIZE - ADDR_SIZE) + (ADDR_SIZE * 2)) -= *(size_t*)(ptr - BLK_SIZE);
		*(size_t*)(mem->top_page + HEADER_SIZE - OCTET_ALLOC) -= *(size_t*)(ptr - BLK_SIZE);
		//si octect malloc == 0 alors mummap et raccorder les autres pages; 
	}
	else
	{
		//abort
		printf("ABORT 2\n");
		exit(1);
	}

}
void *malloc1(size_t size)
{
	//static t_data		data;
	t_memory			*mem;
	enum e_types		type;
	//void				*tmp;
	//bzero(memory, sizeof(memory));
	#ifndef DEBUG
		printf("DEBUG | BEGIN MALLOC\n");
		printf("tiny:'%p'\n", &g_data.mem_tiny);
		printf("\troot:'%p'\n", g_data.mem_tiny.root);
		printf("\tcurrent:'%p'\n", g_data.mem_tiny.current);
		printf("small:'%p'\n", &g_data.mem_small);
		printf("\troot:'%p'\n", g_data.mem_small.root);
		printf("\tcurrent:'%p'\n", g_data.mem_small.current);
		printf("large:'%p'\n", &g_data.mem_large);
		printf("\troot:'%p'\n", g_data.mem_large.root);
		printf("\tcurrent:'%p'\n", g_data.mem_large.current);
		sleep(5);
	#endif
	type = get_type(size);
	mem = get_memory_by_type(&g_data, type);
	if (mem->root == NULL)
	{
		size_t *ptr;
		mem->root = get_map(mem->root, type == LARGE ? size : get_page_size(type));
		mem->top_page = mem->root;
		mem->current = mem->root + HEADER_SIZE;
		mem->type = type;
		printf("DEBUG | NEW MAP mem:'%p'\n", mem);
		printf("DEBUG | NEW MAP mem:->root:'%p'\n", mem->root);
		printf("DEBUG | mem:->top:'%p'\n", mem->top_page);
		printf("DEBUG | NEW MAP mem:->current:'%p'\n", mem->current);
		sleep(5);
	}
	else
		printf("DEJA MMAP\n");
	printf("DEBUG | mem:'%p'\n", mem);
	printf("DEBUG | mem:->root:'%p'\n", mem->root);
	printf("DEBUG | mem:->top:'%p'\n", mem->top_page);
	printf("DEBUG | mem:->current:'%p'\n", mem->current);
	printf("octect alloc:%zd\t%d\n", *(size_t*)(mem->root + ADDR_SIZE * 2), get_page_size(type));
	//sleep(1);
	int ret;
	mem->current = mem->root + HEADER_SIZE;
	if ((ret = available_space(mem, mem->root, type, size) == 1))
	{
		forge_block(mem->current, size, mem->top_page);
		*(size_t*)(mem->top_page + (ADDR_SIZE * 2)) += size;
		g_data.mem_ret = mem->current + FLAG_SIZE + ADDR_SIZE + BLK_SIZE;
		mem->current += STRUCT_BLK_SIZE + size;
	}
	else if (ret == 0)
	{
		printf("exit 1 => mem->top_page(%p)\tmem->top_page(%p)\n", mem->top_page, mem->current);
			printf("DEBUG | CREER NEW MAP\n");
			set_next_map(mem->current, type);
			printf("%p\n", (void*)*((unsigned long*)mem->current));
			//printf("%p\n", (void*)*test2);
			mem->top_page = (void*)*((unsigned long*)mem->current);
			mem->current = mem->top_page + HEADER_SIZE;
			printf("apres:%p\n", mem->current);
			//sleep(1);
			forge_block(mem->current, size, mem->top_page);
			*(size_t*)(mem->top_page + (ADDR_SIZE * 2)) += size;
			g_data.mem_ret = mem->current + FLAG_SIZE + ADDR_SIZE + BLK_SIZE;
			mem->current += STRUCT_BLK_SIZE + size;

			//print_page(mem->top_page, type == LARGE ? size : get_page_size(type));
		//exit(0);
	}
	print_page(mem->top_page, type == LARGE ? size : get_page_size(type));
	return (g_data.mem_ret);
}
void 	*next_block(void *addr)
{
	size_t blk_size;

	if (!addr)
		return (0);
	blk_size = *(size_t*)(addr + FLAG_SIZE + ADDR_SIZE);
	printf("block size:%zu, %lu, %p, %zu\n", blk_size, FLAG_SIZE + ADDR_SIZE, addr + FLAG_SIZE + ADDR_SIZE, *(size_t*)(addr + FLAG_SIZE + ADDR_SIZE));
	return (addr + STRUCT_BLK_SIZE + blk_size);
}

int		available_space(t_memory *mem, void *addr, enum e_types mem_type, size_t size)
{
	printf("DEBUG available_space\n");
	size_t	sum;
	size_t	blk_size;
	void	*ptr_current;

	if (!mem)
		return (-1);
	sum = 0;
	ptr_current = mem->current;
	printf("mem->top_page:%p\taddr:%p\n", mem->top_page, addr);
	mem->top_page = addr;
	while (*(unsigned char*)mem->current == 'F' 
			|| *(unsigned char*)mem->current == 'M'
			|| *(unsigned char*)mem->current == 0)
	{
		//printf("infini => %d %c\n", *(unsigned char*)mem->current, *(unsigned char*)mem->current);
		if (*(unsigned char*)mem->current == 0)
		{
			if (mem->current + STRUCT_BLK_SIZE + size < mem->top_page + get_page_size(mem_type))
				return (1);
			else
			{
				printf("break\n");
				break;
			}
		}
		else if (*(unsigned char*)mem->current == 'M' && ((sum = 0) || 1))
		{
			//printf("avant %p\n", mem->current);
			mem->current = next_block(mem->current);
			//printf("apres %p\n", mem->current);
		}
		else if (*(unsigned char*)mem->current == 'F')
		{
			(sum == 0) ? ptr_current = mem->current : 0;
			sum += (sum == 0) ? 0 : STRUCT_BLK_SIZE;
			sum += *(size_t*)(mem->current + FLAG_SIZE + ADDR_SIZE);
			if (sum >= size)
			{
				mem->current = ptr_current;
				//if sum > size reajuster databack
				if (sum > size)
				{
					if (sum - size > STRUCT_BLK_SIZE)
						printf("place suffisante\n");
					else
						printf("place insuffisante\n");
					sleep(5);
				}
				return (1);
			}
			mem->current = next_block(mem->current);
		}
	}
	printf("par la\n");
	if (printf("mem->top_page:%p\n", mem->top_page) && *(unsigned long*)(mem->top_page) != 0L)
	{
		//*(unsigned long*)mem->top_page = *(unsigned long*)(mem->top_page);
		mem->current = (void*)*((unsigned long*)(mem->top_page)) + HEADER_SIZE;
		printf("PAR LA recursion\n");
		return (available_space(mem, (void*)*((unsigned long*)(mem->top_page)), mem_type, size));
	}
	printf("mem->current:%p\tmem->top_page:%p\n", mem->current, mem->top_page);
	mem->current = mem->top_page;
	return (0);
}

void calcul_checksum(void *addr, unsigned char *checksum)
{
	int		i;
	int		j;
	int		sum1;
	int		sum2;

	if (!addr)
		return ;
	i = 0;
	j = 0;
	sum1 = 0;
	sum2 = 0;
	while (i < STRUCT_BLK_SIZE - CHECKSUM_SIZE)
	{
		sum1 += *(unsigned char*)(addr + i);
		sum2 += *(unsigned char*)(addr + i) * ++j;
		++i;
	}
	checksum[0] = sum1 & 0xFF;
	checksum[1] = sum2 & 0xFF;
	#ifndef DEBUG
		printf("sum1:%x\tsum2:%x\nsum1 & 0xFF:%x\tsum2 & 0xFF:%x\n",sum1, sum2, sum1 & 0xFF, sum2 & 0xFF);
		sleep (4);
	#endif
}
void set_next_map(void *addr, enum e_types type)
{
	void			*new;
	size_t			size;
	unsigned long	*ptr_addr;
	size_t			*ptr_size;

	size = get_page_size(type);
	new = get_map(addr, size);
	//ptr_size = new + sizeof(unsigned long);
	//*ptr_size = size;
	ptr_addr = (unsigned long*)addr;
	*ptr_addr = (unsigned long)new;
	new += ADDR_SIZE;
	*(unsigned long*)new = (unsigned long)addr;
	printf("PREV PAGE:%p\n", (void*)*(unsigned long*)new);
}

void forge_block(void *begin, size_t size, void *root)
{
	printf("Start forge_block : size:%zu\n", size);
	void *addr;
	unsigned char checksum[2];
	//unsigned char *flag; 

	if (begin == NULL)
		return ;
	addr = begin;
	*(unsigned char*)addr = 'M';
	addr += FLAG_SIZE;
	*(unsigned long*)addr = (unsigned long)root;
	addr += ADDR_SIZE;
	*(size_t*)addr = size;
	addr += BLK_SIZE + size;
	calcul_checksum(begin, (unsigned char*)addr);
	//*(unsigned long*)addr = CHECKSUM;
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

enum e_types get_type(size_t size)
{
	if (size <= TINY_SIZE)
		return (TINY);
	else if (size > TINY_SIZE && size <= SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

void print_page(void *page, size_t size)
{
	int i;
	unsigned char *ptr;

	ptr = (unsigned char*)page;
	i = 0;
	if (!page)
	return ;
	while (i < 100)
	{
	printf("index:%d => %p(%c)(%d)\n", i, &ptr[i], ptr[i], ptr[i]);
	i++;
	}
}
