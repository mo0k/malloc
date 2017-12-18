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

int main(int ac, char **av)
{
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
	printf("ptr3:%p\n", ptr3);
	free1(ptr2);
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

void free1(void *ptr)
{
	if (!ptr)
		return ;
	//verifier si addr est valide
	if (*(unsigned long*)(ptr + *(size_t*)(ptr - BLOCK_SIZE)) == CHECKSUM)
	{
		*(unsigned char*)(ptr - BLOCK_SIZE - ADDR_SIZE - FLAG_SIZE) = 'F';
		*(size_t*)(*(unsigned long*)(ptr - BLOCK_SIZE - ADDR_SIZE) + (ADDR_SIZE * 2)) -= *(size_t*)(ptr - BLOCK_SIZE);
		//decrementer octect alloues avec addr
		//recalculer checksum et le modifier
	}
	else
	{
		//abort
		printf("ABORT\n");
		exit(1);
	}

}
void *malloc1(size_t size)
{
	static t_data		data;
	t_memory			*mem;
	enum e_types		type;
	//void				*tmp;
	//bzero(memory, sizeof(memory));
	printf("DEBUG | BEGIN MALLOC\n");
	printf("tiny:'%p'\n", &data.mem_tiny);
	printf("\troot:'%p'\n", data.mem_tiny.root);
	printf("\tcurrent:'%p'\n", data.mem_tiny.current);
	printf("small:'%p'\n", &data.mem_small);
	printf("\troot:'%p'\n", data.mem_small.root);
	printf("\tcurrent:'%p'\n", data.mem_small.current);
	printf("large:'%p'\n", &data.mem_large);
	printf("\troot:'%p'\n", data.mem_large.root);
	printf("\tcurrent:'%p'\n", data.mem_large.current);
	type = get_type(size);
	mem = get_memory_by_type(&data, type);
	if (mem->root == NULL)
	{
		size_t *ptr;
		mem->root = get_map(mem->root, type == LARGE ? size : get_page_size(type));
		mem->top_page = mem->root;
		mem->current = mem->root + HEADER_SIZE;
		//ptr = (size_t*)mem->current;
		//*ptr = get_page_size(type) - sizeof(unsigned long) - sizeof(size_t);
		//printf("page_size:%zd\t%zd\t%d\n", (size_t*)(*ptr), *(size_t*)(mem->current), get_page_size(type));
		//mem->current += sizeof(size_t);
		printf("DEBUG | NEW MAP mem:'%p'\n", mem);
		printf("DEBUG | NEW MAP mem:->root:'%p'\n", mem->root);
		printf("DEBUG | mem:->top:'%p'\n", mem->top_page);
		printf("DEBUG | NEW MAP mem:->current:'%p'\n", mem->current);
		//sleep(5);
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
		data.mem_ret = mem->current + FLAG_SIZE + ADDR_SIZE + BLOCK_SIZE;
		mem->current += STRUCT_BLOCK_SIZE + size;
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
			data.mem_ret = mem->current + FLAG_SIZE + ADDR_SIZE + BLOCK_SIZE;
			*(size_t*)(mem->top_page + (ADDR_SIZE * 2)) += size;

			//print_page(mem->top_page, type == LARGE ? size : get_page_size(type));
			mem->current += STRUCT_BLOCK_SIZE + size;
		//exit(0);
	}
	print_page(mem->top_page, type == LARGE ? size : get_page_size(type));
	return (data.mem_ret);
}
void 	*next_block(void *addr)
{
	size_t block_size;

	if (!addr)
		return (0);
	block_size = *(size_t*)(addr + FLAG_SIZE + ADDR_SIZE);
	printf("block size:%zu, %lu, %p, %zu\n", block_size, FLAG_SIZE + ADDR_SIZE, addr + FLAG_SIZE + ADDR_SIZE, *(size_t*)(addr + FLAG_SIZE + ADDR_SIZE));
	return (addr + STRUCT_BLOCK_SIZE + block_size);
}

int		available_space(t_memory *mem, void *addr, enum e_types mem_type, size_t size)
{
	printf("DEBUG available_space\n");
	size_t	sum;
	size_t	block_size;
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
		printf("infini => %d %c\n", *(unsigned char*)mem->current, *(unsigned char*)mem->current);
		if (*(unsigned char*)mem->current == 0)
		{
			if (mem->current + STRUCT_BLOCK_SIZE + size < mem->top_page + get_page_size(mem_type))
				return (1);
			else
			{
				printf("break\n");
				break;
			}
		}
		else if (*(unsigned char*)mem->current == 'M' && ((sum = 0) || 1))
		{
			printf("avant %p\n", mem->current);
			mem->current = next_block(mem->current);
			printf("apres %p\n", mem->current);
		}
		else if (*(unsigned char*)mem->current == 'F')
		{
			(sum == 0) ? ptr_current = mem->current : 0;
			sum += (sum == 0) ? 0 : STRUCT_BLOCK_SIZE;
			sum += *(size_t*)(mem->current + FLAG_SIZE + ADDR_SIZE);
			if (sum >= size)
			{
				mem->current = ptr_current;
				//if sum > size reajuster databack
				return (1);
			}
			mem->current = next_block(mem->current);
		}
	}
	printf("par la\n");
	if (printf("mem->top_page:%p\n", mem->top_page) && *(unsigned long*)(mem->top_page) != 0L)
	{
		//*(unsigned long*)mem->top_page = *(unsigned long*)(mem->top_page);
		mem->current = (void*)*((unsigned long*)(mem->top_page)) + HEADER_SIZE
		printf("PAR LA recursion\n");
		return (available_space(mem, (void*)*((unsigned long*)(mem->top_page)), mem_type, size));
	}
	printf("mem->current:%p\tmem->top_page:%p\n", mem->current, mem->top_page);
	mem->current = mem->top_page;
	return (0);
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
	unsigned char *flag; 

	if (begin == NULL)
		return ;
	*(unsigned char*)begin = 'M';
	begin += FLAG_SIZE;
	*(unsigned long*)begin = (unsigned long)root;
	begin += ADDR_SIZE;
	*(size_t*)begin = size;
	begin += BLOCK_SIZE + size;
	*(unsigned long*)begin = CHECKSUM;
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
