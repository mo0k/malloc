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
#include <limits.h>
int	available_space(t_memory *mem, void *addr, size_t *size);

int main(int ac, char **av)
{
	//free(1);
	char **root;
	char *ptr1;
	char *ptr2;

	int i = 0;
	root = (char**)malloc1(sizeof(char*) * 500);
	//sleep(4);
	while (i < 500)
	{
		root[i] = (char*)malloc1(128);
		//free1(ptr - 100000);
		//printf("ok\n");
		//free(ptr);
		if (!root[i])
		{
			printf("i:%d\n", i);
			exit(127);
			printf("malloc ok\n");
		}
		else
		{
			strcpy(root[i], "cococococococok");
			printf("%d Copy de 'coco' at %p => %s\n", i, root[i], 	root[i]);
		}
		i++;
		//sleep(1);
	}
	/*free1(root[2]);
	free1(root[3]);
	free1(root[4]);
	free1(root[20]);
	free1(root[21]);
	free1(root[22]);
	free1(root[23]);
	free1(root[24]);
	free1(root[200]);
	root[2] = (char*)malloc1(64);
	root[20] = (char*)malloc1(128);*/
	show_alloc_mem();
	//return (1);
	i = 500;
	while (i >= 0)
	{
		printf("i:%d\n", i);
		free1(root[i]);
		i--;
	}
	show_alloc_mem();
	ptr1 = (char*)malloc1(515);
	ptr2 = (char*)malloc1(513);
	free1(ptr1);
	free1(ptr2);
	free1(root);
	//free1(root);
	//root[51] = (char*)malloc1(1024);
	show_alloc_mem();
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

	if (!mem)
		return ;
	//mem->current = mem->root + HEADER_SIZE;
	if ((ret = available_space(mem, mem->map, &size) == 1))
		create_block(mem, size, get_map_size(mem->type));
	else if (ret == 0)
	{
		printf("exit 1 => mem->map(%p)\tmem->current(%p)\n", mem->map, mem->current);
		printf("DEBUG | CREER NEW MAP\n");
		set_next_map(mem->map, get_map_size(mem->type));
		printf("%p\n", (void*)*((unsigned long*)mem->map));
		mem->map = (void*)*((unsigned long*)mem->map);
		mem->current = mem->map + HEADER_SIZE;
		printf("apres:%p\n", mem->current);
		create_block(mem, size, get_map_size(mem->type));
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
		printf("ABORT fix map\n");
		exit_abort(*map);
	}
}

static void	manage_large(t_memory *mem, size_t size)
{
	static int i;
	int ret;

	printf("2 size:%zd\n", size);
	if (!mem)
		return ;
	//mem->current = mem->root + HEADER_SIZE;
	if (i++ == 0 && *(unsigned long *)mem->map == 0)
		create_block(mem, size, size);
	else
	{
		fix_map(&mem->map);
		printf("mem->map(%p)\tmem->current(%p)\n", mem->map, mem->current);
		printf("DEBUG | CREER NEW MAP\n");
		set_next_map(mem->map, size + HEADER_SIZE + STRUCT_BLK_SIZE);
		printf("%p\n", (void*)*((unsigned long*)mem->map));
		mem->map = (void*)*((unsigned long*)mem->map);
		mem->current = mem->map + HEADER_SIZE;
		printf("apres:%p\n", mem->current);
		create_block(mem, size, size);
	}
	i = (i >= 1) ? 1 : 0;
}

void *malloc1(size_t size)
{
	t_memory			*mem;
	enum e_types		type;

	#ifndef NDEBUG
		printf("DEBUG | BEGIN MALLOC\n");
		printf("size:'%zd'\n", size);
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
		mem->root = get_map(mem->root, type == LARGE ? 
			size + HEADER_SIZE + STRUCT_BLK_SIZE : get_map_size(type));
		mem->map = mem->root;
		mem->current = mem->root + HEADER_SIZE;
		mem->type = type;
		checksum(mem->root, HEADER_SIZE - CHECKSUM_SIZE, (unsigned char *)(mem->current - CHECKSUM_SIZE));
		//checksum(mem->root, STRUCT_BLK_SIZE - CHECKSUM_SIZE, (unsigned char *)(mem->current - CHECKSUM_SIZE));
		#ifndef NDEBUG
			printf("DEBUG | NEW MAP mem:'%p'\n", mem);
			printf("DEBUG | NEW MAP mem:->root:'%p'\n", mem->root);
			printf("DEBUG | mem:->top:'%p'\n", mem->map);
			printf("DEBUG | NEW MAP mem:->current:'%p'\n", mem->current);
			printf("%x%x\n", *(unsigned char *)(mem->map - CHECKSUM_SIZE), *(unsigned char *)(mem->map - CHECKSUM_SIZE + 1));
			//sleep(5);
		#endif
	}
	#ifndef NDEBUG
		printf("DEBUG | mem:'%p'\n", mem);
		printf("DEBUG | mem:->root:'%p'\n", mem->root);
		printf("DEBUG | mem:->top:'%p'\n", mem->map);
		printf("DEBUG | mem:->current:'%p'\n", mem->current);
		printf("octect alloc:%zd\t%d\t%zd\n", *(size_t*)(mem->root + ADDR_SIZE * 2), get_map_size(type), size);
		//sleep(1);
	#endif
	//printf("1 size:%zd\n", size);
	(type == LARGE) ? manage_large(mem, size) : manage_tiny_small(mem, size); 
	//print_map(mem->map, mem->type == LARGE ? size : get_map_size(mem->type));
	return (g_data.mem_ret);
}

int		available_space(t_memory *mem, void *addr, size_t *size)
{
	printf("DEBUG available_space\n");
	size_t	sum;
	size_t	map_size;
	void	*ptr_current;

	if (!mem)
		return (-1);
	sum = 0;
	ptr_current = mem->current;
	map_size = get_map_size(mem->type);
	printf("mem->map:%p\taddr:%p\n", mem->map, addr);
	mem->map = addr;
	while (mem->current < mem->map + map_size)
	{
		printf("infini => %d %c\n", *(unsigned char*)mem->current, *(unsigned char*)mem->current);
		if (*(unsigned char*)mem->current == 0)
		{
			if (mem->current + STRUCT_BLK_SIZE + *size < mem->map + map_size)
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
			mem->current = next_block(mem->current, mem->map, map_size);
			printf("apres %p\n", mem->current);
			/*if (mem->current == mem->map + map_size)
			{
				printf("par la\n");
				break;
			}*/
			if (!mem->current)
			{
				printf("par ici\n");
				break;
			}
		}
		else if (*(unsigned char*)mem->current == 'F')
		{
			//ajouter verif_checksum
			if (!verif_checksum(mem->current, STRUCT_BLK_SIZE - CHECKSUM_SIZE))
			{
				printf("ABORT available_space free block\n");
				exit_abort(mem->current + STRUCT_BLK_SIZE);
			}
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
						//optimiser en regardant next
						*size += sum - *size;
					}
					//sleep(5);
				}
				return (1);
			}
			mem->current = next_block(mem->current, mem->map, map_size);
			//if (!mem->current)
			if (mem->current == mem->map + map_size)
			{
				sum = 0;
				break ;
				return (0);
			}
		}
	}
	printf("par la\n");
	if (printf("mem->map:%p\n", mem->map) && *(unsigned long*)(mem->map) != 0L)
	{
		if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			printf("ABORT available_space\n");
			exit(1);
		}
		printf("PAR LA recursion\n");
		mem->current = (void*)*((unsigned long*)(mem->map)) + HEADER_SIZE;
		return (available_space(mem, (void*)*((unsigned long*)(mem->map)), size));
	}
	printf("mem->current:%p\tmem->map:%p\n", mem->current, mem->map);
	mem->current = mem->map;
	return (0);
}

int		available_space1(t_memory *mem, void *addr, size_t *size)
{
	printf("DEBUG available_space\n");
	size_t	sum;
	size_t	map_size;
	void	*ptr_current;

	if (!mem)
		return (-1);
	sum = 0;
	ptr_current = mem->current;
	map_size = get_map_size(mem->type);
	printf("mem->map:%p\taddr:%p\n", mem->map, addr);
	mem->map = addr;
	while (printf("test\n") && (*(unsigned char*)mem->current == 'F' 
			|| *(unsigned char*)mem->current == 'M'
			|| *(unsigned char*)mem->current == 0))
	{
		printf("infini => %d %c\n", *(unsigned char*)mem->current, *(unsigned char*)mem->current);
		if (*(unsigned char*)mem->current == 0)
		{
			if (mem->current + STRUCT_BLK_SIZE + *size < mem->map + get_map_size(mem->type))
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
			mem->current = next_block(mem->current, mem->map, get_map_size(mem->type));
			printf("apres %p\n", mem->current);
			/*if (mem->current == mem->map + get_map_size(mem->type))
			{
				printf("par la\n");
				break;
			}*/
			if (!mem->current)
			{
				printf("par ici\n");
				break;
			}
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
						//optimiser en regardant next
						*size += sum - *size;
					}
					//sleep(5);
				}
				return (1);
			}
			mem->current = next_block(mem->current, mem->map, get_map_size(mem->type));
			//if (!mem->current)
			if (mem->current == mem->map + get_map_size(mem->type))
			{
				sum = 0;
				break ;
				return (0);
			}
		}
	}
	printf("par la\n");
	if (printf("mem->map:%p\n", mem->map) && *(unsigned long*)(mem->map) != 0L)
	{
		if (!verif_checksum(mem->map, HEADER_SIZE - CHECKSUM_SIZE))
		{
			printf("ABORT available_space\n");
			exit(1);
		}
		printf("PAR LA recursion\n");
		mem->current = (void*)*((unsigned long*)(mem->map)) + HEADER_SIZE;
		return (available_space(mem, (void*)*((unsigned long*)(mem->map)), size));
	}
	printf("mem->current:%p\tmem->map:%p\n", mem->current, mem->map);
	mem->current = mem->map;
	return (0);
}
