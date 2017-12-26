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

#include <malloc.h>

int	available_space(t_memory *mem, void *addr, size_t *size);

int main(int ac, char **av)
{
	
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
			printf("Copy de 'coco' at %p => %s\n", ptr, 	ptr);
			//sleep(2);
		}
	}
	/*
	char *ptr;
	int i = 8;
	int index = 0;
	ptr = (char*)malloc(32);

	*(ptr - 2) = 'i';
	printf("%p\n", ptr);
	while (index < 500)
	{
		//printf("%c(%d)\n", *(ptr - i), *(ptr - i));
		printf("ptr:%p\n", (ptr - i));
		printf("pointer:%p\n", (void*)(*(unsigned long*)(ptr - i)));
		printf("size_t:%zd\n", (size_t*)(*(unsigned long*)(ptr - i)));
		printf("hexa:%lx\n______%d\n", *(unsigned long*)(ptr - i), index);
		index++;
		i += 8;
	}
	free(ptr);*/
	/*
	char *ptr1;
	char *ptr2;
	char *ptr3;
	char *ptr4;
	char *ptr5;

	ptr1 = malloc1(2); 	
	printf("ptr1:%p\n", ptr1);
	ptr2 = malloc1(32);
	printf("ptr2:%p\n", ptr2);
	ptr3 = malloc1(32);
	printf("ptr3:%p, ptr2 - 4:%p, char:%c\n", ptr3, ptr2 - 4, *(ptr2 - (STRUCT_BLK_SIZE - CHECKSUM_SIZE)));
	sleep(5);
	*(ptr2 - (STRUCT_BLK_SIZE - CHECKSUM_SIZE)) = 'F';
	//free1(ptr2);
	//free1(ptr2);
	//free1(ptr3);
	*(ptr2 - (16)) = 1;
	*(ptr2 - (15)) = 0;
	*(ptr2 - (14)) = 0;
	*(ptr2 - (13)) = 0;
	*(ptr2 - (12)) = 0;
	*(ptr2 - (11)) = 0;
	*(ptr2 - (10)) = 0;
	*(ptr2 - (9)) = 0;
	ptr4 = malloc1(16);
	free1(ptr2);
	free1(ptr3);
	ptr5 = malloc1(1);
	printf("ptr2:%p\n", ptr2);
	printf("ptr5:%p\n", ptr5);
	free1(ptr2);*/
	
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

static void	manage_tiny_small(t_memory *mem, size_t size)
{
	int ret;

	//mem->current = mem->root + HEADER_SIZE;
	if ((ret = available_space(mem, mem->top_page, &size) == 1))
		create_block(mem, size, get_map_size(mem->type));
	else if (ret == 0)
	{
		printf("exit 1 => mem->top_page(%p)\tmem->top_page(%p)\n", mem->top_page, mem->current);
		printf("DEBUG | CREER NEW MAP\n");
		set_next_map(mem->current, (mem->type == LARGE) ? size : get_map_size(mem->type));
		printf("%p\n", (void*)*((unsigned long*)mem->current));
		mem->top_page = (void*)*((unsigned long*)mem->current);
		mem->current = mem->top_page + HEADER_SIZE;
		printf("apres:%p\n", mem->current);
		create_block(mem, size, get_map_size(mem->type));
	}
}

void *malloc1(size_t size)
{
	t_memory			*mem;
	enum e_types		type;

	#ifndef NDEBUG
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
	#endif
	type = get_type_block(size);
	mem = get_memory_by_type(&g_data, type);
	if (mem->root == NULL)
	{
		size_t *ptr;
		mem->root = get_map(mem->root, type == LARGE ? size : get_map_size(type));
		mem->top_page = mem->root;
		mem->current = mem->root + HEADER_SIZE;
		mem->type = type;
		checksum(mem->root, STRUCT_BLK_SIZE - CHECKSUM_SIZE, (unsigned char *)(mem->current - CHECKSUM_SIZE));
		#ifndef NDEBUG
			printf("DEBUG | NEW MAP mem:'%p'\n", mem);
			printf("DEBUG | NEW MAP mem:->root:'%p'\n", mem->root);
			printf("DEBUG | mem:->top:'%p'\n", mem->top_page);
			printf("DEBUG | NEW MAP mem:->current:'%p'\n", mem->current);
			printf("%x%x\n", *(unsigned char *)(mem->top_page - CHECKSUM_SIZE), *(unsigned char *)(mem->top_page - CHECKSUM_SIZE + 1));
			//sleep(5);
		#endif
	}
	#ifndef NDEBUG
		printf("DEBUG | mem:'%p'\n", mem);
		printf("DEBUG | mem:->root:'%p'\n", mem->root);
		printf("DEBUG | mem:->top:'%p'\n", mem->top_page);
		printf("DEBUG | mem:->current:'%p'\n", mem->current);
		printf("octect alloc:%zd\t%d\n", *(size_t*)(mem->root + ADDR_SIZE * 2), get_map_size(type));
		//sleep(1);
	#endif
	(type == LARGE) ? 0 : manage_tiny_small(mem, size); 
	print_map(mem->top_page, mem->type == LARGE ? size : get_map_size(mem->type));
	return (g_data.mem_ret);
}


int		available_space(t_memory *mem, void *addr, size_t *size)
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
	while (printf("test\n") && (*(unsigned char*)mem->current == 'F' 
			|| *(unsigned char*)mem->current == 'M'
			|| *(unsigned char*)mem->current == 0))
	{
		printf("infini => %d %c\n", *(unsigned char*)mem->current, *(unsigned char*)mem->current);
		if (*(unsigned char*)mem->current == 0)
		{
			if (mem->current + STRUCT_BLK_SIZE + *size < mem->top_page + get_map_size(mem->type))
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
			mem->current = next_block(mem->current, mem->top_page, get_map_size(mem->type));
			printf("apres %p\n", mem->current);
			//if (mem->current == mem->top_page + get_map_size(mem->type))
			if (!mem->current)
				break;
		}
		else if (*(unsigned char*)mem->current == 'F')
		{
			(sum == 0) ? ptr_current = mem->current : 0;
			sum += (sum == 0) ? 0 : STRUCT_BLK_SIZE;
			sum += *(size_t*)(mem->current + FLAG_SIZE + ADDR_SIZE);
			if (sum >= *size)
			{
				mem->current = ptr_current;
				if (sum > *size)
				{
					printf("sum:%zu\tsize:%zu\tstruct_size:%lu\n", sum, *size, STRUCT_BLK_SIZE);
					if (sum - *size > STRUCT_BLK_SIZE)
					{
						size_t size_temp = (sum - *size) - STRUCT_BLK_SIZE;
						printf("place suffisante pour new block\n");
						forge_block(mem->current + *size + STRUCT_BLK_SIZE, size_temp,
							mem->current + *size + (STRUCT_BLK_SIZE * 2) + size_temp, 'F');
						//Creation new block flag=F
						//Assigner addr next 
					}
					else
					{
						printf("place insuffisante pour new block\n");
						*size += sum - *size;
					}
					//sleep(5);
				}
				return (1);
			}
			mem->current = next_block(mem->current, mem->top_page, get_map_size(mem->type));
			if (!mem->current)
				return (0);
		}
	}
	printf("par la\n");
	if (printf("mem->top_page:%p\n", mem->top_page) && *(unsigned long*)(mem->top_page) != 0L)
	{
		if (!verif_checksum(mem->top_page, HEADER_SIZE - CHECKSUM_SIZE))
		{
			printf("ABORT available_space\n");
			exit(1);
		}
		printf("PAR LA recursion\n");
		mem->current = (void*)*((unsigned long*)(mem->top_page)) + HEADER_SIZE;
		return (available_space(mem, (void*)*((unsigned long*)(mem->top_page)), size));
	}
	printf("mem->current:%p\tmem->top_page:%p\n", mem->current, mem->top_page);
	mem->current = mem->top_page;
	return (0);
}


