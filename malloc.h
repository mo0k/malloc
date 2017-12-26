#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define CHECKSUM_SIZE 2

# define ADDR_SIZE sizeof(unsigned long)
# define OCTET_ALLOC sizeof(size_t)
# define HEADER_SIZE (ADDR_SIZE * 2 + OCTET_ALLOC + CHECKSUM_SIZE)

# define FLAG_SIZE sizeof(unsigned char)
# define BLK_SIZE sizeof(size_t)
# define STRUCT_BLK_SIZE (FLAG_SIZE + ADDR_SIZE + BLK_SIZE + CHECKSUM_SIZE)

# define TINY_SIZE 16
# define SMALL_SIZE 512
# define LARGE_SIZE 4096
# define TINY_PAGE_SIZE getpagesize()
# define SMALL_PAGE_SIZE getpagesize() * 16

/*
**
**			   OCTECTS
**   NEXT PREV ALLOUE CKM
**  |____|____|_____|__|.............
**
**	   
**   F NEXT SIZE CHM DATA   
**  |_|____|____|__|______|
**   1  8    8    2   x   
*/

enum e_types {
	TINY,
	SMALL,
	LARGE
};

typedef struct		s_memory{
	void 			*root;
	void 			*top_page;
	void 			*current;
	enum e_types 	type;
}					t_memory;

typedef struct 		s_data {
	t_memory 		mem_tiny;
	t_memory 		mem_small;
	t_memory 		mem_large;
	void			*mem_ret;
} 					t_data;

t_data g_data;

void 				free1(void *ptr);
void 				*malloc1(size_t size);
void 				*realloc(void *ptr, size_t size);

void 				print_map(void *page, size_t size);
void 				*get_map(void *addr, size_t size);
int 				get_map_size(enum e_types type);
void 				set_next_map(void *addr, size_t size);

void				create_block(t_memory *mem, size_t size, int page_size);
void 				forge_block(void *addr_begin, size_t size, void *next, unsigned char flag);
void 				*next_block(void *addr, void *root_page, int page_size);
enum e_types 		get_type_block(size_t size);

//void 				checksum(void *addr, unsigned char *checksum);
void 				checksum(void *addr, size_t size, unsigned char *checksum);
int	verif_checksum(void *addr, size_t size);

#endif
