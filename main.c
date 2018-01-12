/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 09:44:01 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/10 19:35:01 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int main(int ac, char **av)
{
	//free(1);
	(void)ac;
	(void)av;
	char **root;
	char *ptr1;
	char *ptr2;
	char *ptr3;

	int i = 0;
	int j = 64;
	int x = 351;
	root = (char**)malloc(sizeof(char*) * x);
	//sleep(4);
	while (i <= x)
	{
		root[i] = (char*)malloc(j);
		//j = j + 10;
		//free(ptr - 100000);
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
			strcpy(root[i], "coc");
			printf("%d Copy de 'coco' at %p => %s\n", i, root[i], 	root[i]);
		}
		i++;
		//sleep(1);
	}
	//strcpy(root[12], "cococococococok");
	//free(root[13]);
	//free(root[12]);
	/*free(root[2]);
	free(root[3]);
	free(root[4]);
	free(root[20]);
	free(root[21]);
	free(root[22]);
	free(root[23]);
	free(root[24]);
	root[2] = (char*)malloc(64);
	root[20] = (char*)malloc(128);*/
	//free(root[499]);
	//ptr1 = (char*)malloc(1);
	//ptr1 = (char*)malloc(1);
	//ptr1 = (char*)malloc(1);
	//free(ptr1);
	//show_alloc_mem();
	//return (1);
	i = x;
	while (i >= x - 2)
	{
		printf("i:%d\n", i);
		free(root[i-20]);
		i--;
	}
	//show_alloc_mem();
	//return (1);
	//ptr1 = (char*)malloc(64);
	ptr1 = (char*)malloc(128);
	ptr1 = (char*)malloc(18);
	//ptr1 = (char*)malloc(36);
	//ptr1 = (char*)malloc(20);
	//ptr1 = (char*)malloc(17);
	//ptr1 = (char*)malloc(1);
	//ptr1 = (char*)malloc(8);
	//ptr1 = (char*)malloc(12);
	//ptr1 = (char*)malloc(7);
	//show_alloc_mem();
	return (1);
	ptr2 = (char*)malloc(32);
	ptr3 = (char*)malloc(17);
	//ptr2 = (char*)malloc(128);
	//ptr2 = (char*)malloc(64);
	//show_alloc_mem();
	sleep(5);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	ptr1 = (char*)malloc(60);
	//free(root);
	//free(root);
	//root[51] = (char*)malloc(1024);
	//show_alloc_mem();
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

	ptr1 = malloc(2); 	
	printf("ptr1:%p\n", ptr1);
	ptr2 = malloc(32);
	printf("ptr2:%p\n", ptr2);
	ptr3 = malloc(32);
	printf("ptr3:%p, ptr2 - 4:%p, char:%c\n", ptr3, ptr2 - 4, *(ptr2 - (STRUCT_BLK_SIZE - CHECKSUM_SIZE)));
	sleep(5);
	*(ptr2 - (STRUCT_BLK_SIZE - CHECKSUM_SIZE)) = 'F';
	//free(ptr2);
	//free(ptr2);
	//free(ptr3);
	*(ptr2 - (16)) = 1;
	*(ptr2 - (15)) = 0;
	*(ptr2 - (14)) = 0;
	*(ptr2 - (13)) = 0;
	*(ptr2 - (12)) = 0;
	*(ptr2 - (11)) = 0;
	*(ptr2 - (10)) = 0;
	*(ptr2 - (9)) = 0;
	ptr4 = malloc(16);
	free(ptr2);
	free(ptr3);
	ptr5 = malloc(1);
	printf("ptr2:%p\n", ptr2);
	printf("ptr5:%p\n", ptr5);
	free(ptr2);*/
	
	/*int i = 0;
	while (++i)
	{
		ptr1 = malloc(16);
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
