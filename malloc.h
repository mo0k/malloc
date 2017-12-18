#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define ADDR_SIZE sizeof(unsigned long)
# define OCTET_ALLOC sizeof(size_t)
# define HEADER_SIZE ADDR_SIZE * 2 + OCTET_ALLOC;

# define FLAG_SIZE sizeof(unsigned char)
# define BLOCK_SIZE sizeof(size_t)
# define CHECKSUM 0xF00D7007
# define CHECKSUM_SIZE sizeof(long)
# define STRUCT_BLOCK_SIZE FLAG_SIZE + ADDR_SIZE + BLOCK_SIZE + (CHECKSUM_SIZE * 2) 

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
**	   ADDR
**   F PAGE SIZE CHKM  DATA  CHKM 
**  |_|____|____|____|______|____|
**   1  8    8     x     8    8   
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
}				t_memory;

typedef struct s_data {
	t_memory mem_tiny;
	t_memory mem_small;
	t_memory mem_large;
	void	*mem_ret;
} t_data;

void free(void *ptr);
void *malloc1(size_t size);
void *realloc(void *ptr, size_t size);

#endif
