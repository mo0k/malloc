#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define ADDR_SIZE sizeof(unsigned long)
# define OCTET_ALLOC sizeof(size_t)
# define HEADER_SIZE (ADDR_SIZE * 2 + OCTET_ALLOC)

# define FLAG_SIZE sizeof(unsigned char)
# define BLK_SIZE sizeof(size_t)
# define CHECKSUM_SIZE 2
# define STRUCT_BLK_SIZE (FLAG_SIZE + ADDR_SIZE + BLK_SIZE + CHECKSUM_SIZE)

# define TINY_SIZE 16
# define SMALL_SIZE 512
# define LARGE_SIZE 4096
# define TINY_PAGE_SIZE getpagesize()
# define SMALL_PAGE_SIZE getpagesize() * 16

/*
**
**			   OCTECTS
**   NEXT PREV ALLOUE
**  |____|____|_____|.............
**
**	   
**   F NEXT SIZE  DATA  CHKM 
**  |_|____|____|______|__|
**   1  8    8     x     2   
*/

enum e_types {
	TINY,
	SMALL,
	LARGE
};

typedef struct	s_memory{
	void *root;
	void *top_page;
	void *current;
	enum e_types type;
}				t_memory;

typedef struct s_data {
	t_memory mem_tiny;
	t_memory mem_small;
	t_memory mem_large;
	void	*mem_ret;
} t_data;

t_data g_data;

void free1(void *ptr);
void *malloc1(size_t size);
void *realloc(void *ptr, size_t size);

#endif
