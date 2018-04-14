/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/14 10:50:40 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <ft_printf.h>
# include <debug.h>

# define HDR_PAGE_SIZE 32
# define HDR_BLK_SIZE 16
# define CHKM_SIZE 2
# define TINY_MAX 512
# define SMALL_MAX 2048
# define TINY_PAGE_SIZE getpagesize() * 13
# define SMALL_PAGE_SIZE getpagesize() * 50

typedef struct 		s_header_block
{
	short int		bprev;
	short int		bnext;
	short int 		fprev;
	short int 		fnext;
	unsigned int	size;
	short int		align;
	//char 			padding[2];
	unsigned char	chkm[CHKM_SIZE];
}					t_hdr_blk;

typedef struct		s_header_page 
{
	void			*prev;
	void			*next;
	unsigned int	size;
	unsigned int 	last_blk;
	unsigned int 	free;
	short int 		nbr_blk;
	unsigned char	chkm[CHKM_SIZE];	
}					t_hdr_page;


# define AVAILABLE_BLK(blk, page) ((void*)((void*)(blk) + HDR_BLK_SIZE + (blk)->size + (blk)->align) < \
									(void*)((void*)(page) + (page)->size))
# define MIN_SIZE(type) ((type) == TINY ? 1 : TINY_MAX + 1)
# define MIN_SIZE_REMAINING(blk, page, type) (HDR_BLK_SIZE + MIN_SIZE(type) > \
										END_PAGE((page)) - END_BLK((blk)))
# define LARGE_SIZE(size) ((size) + HDR_PAGE_SIZE + HDR_BLK_SIZE)

# define NEW_PAGE(size) (mmap(NULL, (size), PROT_WRITE | PROT_READ,\
			MAP_ANON | MAP_PRIVATE, -1, 0))
# define DEL_PAGE(ptr) (munmap((ptr), (ptr)->size))
# define NEXT_PAGE(page) ((page)->next)
# define PREV_PAGE(page) ((page)->prev)
# define END_PAGE(page) ((void*)(page) + (page)->size) //not use for lange
# define IN_PAGE(pg, pt) ((pt) > (void*)(FIRST_BLK((pg))) && (pt) < END_PAGE((pg)))
# define SET_LAST_BLK(p, b) ((p)->last_blk = (void*)(b) - (void*)(p))
# define FIRST_FREE(p) ((p)->free ? (t_hdr_blk*)((void*)(p) + (p)->free) : 0)
# define SET_FIRST_FREE(p, b) ((p)->free = (void*)(b) - (void*)(p))

# define FIRST_BLK(p) ((t_hdr_blk*)((void*)(p) + HDR_PAGE_SIZE))
# define LAST_BLK(p) ((t_hdr_blk*)((void*)(p) + (p)->last_blk))
# define BEGIN_BLK(b) ((void*)(b) + HDR_BLK_SIZE + (b)->align)
# define END_BLK(b) (((void*)(b) + HDR_BLK_SIZE + (b)->align + (b)->size))
# define LEN_BLK(b) (HDR_BLK_SIZE + (b)->align + (b)->size)
# define NEXT_BLK(b) ((b)->bnext ? (void*)(b) + (b)->bnext : 0)
# define PREV_BLK(b) ((b)->bprev ? (void*)(b) - (b)->bprev : 0)
# define NEXT_FBLK(b) ((b)->fnext ? (void*)(b) + (b)->fnext: 0)
# define PREV_FBLK(b) ((b)->fprev ? (void*)(b) - (b)->fprev: 0)
# define IS_NEXT_BLK(blk, next) (blk + (blk)->size + HDR_BLK_SIZE == next ? 0 : 1)

# define INIT_HEADER(header, n) (memset(header, 0, n))
# define CHK_HEADER(x, n) (ft_memcmp((void*)(x) + (n), checksum((x), (n)), CHKM_SIZE))
# define SET_CHKM(x, n) (ft_memmove((void*)(x) + (n), checksum((x), (n)), CHKM_SIZE))
# define OFFSET_CHKM(n) ((n) - CHKM_SIZE)
# define OFFSET(p1, p2) ((void*)(p1) - (void*)(p2))
# define ALIGN(blk) ((unsigned long)BEGIN_BLK((blk)) % 16UL != 0)

# define FALSE 0
# define TRUE 1

enum e_ret
{
	ERROR_MEMORY_MANAGER = 1,
	ERROR_ARGS,
	CREATE_NEW_PAGE,
	CREATE_NEW_BLOCK,
	FREE_USED,
	FREE_NO_USED,
	NO_PAGE_FOUND,
	NO_BLOCK_FOUND,
	BLOCK_FREE_PLACED,
	BLOCK_FREE_NOPLACED,
	ALIGN,
	NO_ALIGN,
	CHECKSUM_CORRUPED
};

typedef struct		s_ret_manager
{
	enum e_ret		value;
	t_hdr_page		*page;
}					t_ret_manager;

enum e_types
{
	NO_TYPE,
	TINY,
	SMALL,
	LARGE
};

typedef struct		s_memory{
	t_hdr_page		*page;
	enum e_types 	type;
}					t_memory;

typedef struct 		s_data {
	t_memory 		mem_tiny;
	t_memory 		mem_small;
	t_memory 		mem_large;
	void			*mem_ret;
} 					t_data;

t_data 				g_data;

void 				*malloc(size_t size);
void				free(void *ptr);
void 				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

/*
**	Memory
*/
void 				initialize_memory(t_memory *mem, enum e_types type, size_t size);
t_memory 			*memory_by_type(t_data *data, enum e_types type);

/*
**	Page
*/
void 				initialize_page(t_hdr_page **page, t_hdr_page *prev, unsigned int page_size);
int 				page_size(enum e_types type);
t_hdr_page			*find_page(t_data *data, void *ptr, enum e_types *type);
void 				display_hdr_page(t_hdr_page *hdr_page);
void 				print_page(void *page, size_t size);//DEBUG
void				del_page(t_hdr_page *page, enum e_types type);


/*
**	Block
*/
enum e_types 		type_block(size_t size);
void				create_new_block(t_hdr_blk *block, t_hdr_page *page);
t_hdr_blk			*find_blk(t_hdr_page *page, void *ptr);
void 				display_hdr_blk(t_hdr_blk *hdr_blk);

/*
**	Free block
*/
void				create_free_blk(t_hdr_blk *blk, t_hdr_page *page, enum e_types type);
int 				place_free_blk(t_hdr_blk *blk, t_hdr_blk *free, t_hdr_page *page);

//int 				place_free_blk(t_hdr_blk *blk, t_hdr_blk *free);

/*
**	Checksum
*/
void 				*checksum(void *header, size_t size);

/*
**	Tiny - Small
*/
void				manage_tiny_small(t_hdr_page *page, size_t size, enum e_types type);
t_ret_manager		*memory_manager(t_hdr_page *page, size_t blk_size, enum e_types type, t_ret_manager *ret, int count);

/*
**	Large
*/


/*
**	Utils
*/
void				kill_prog(int flag, int count);
int 				check_space_and_align(t_hdr_page *page, t_hdr_blk *blk, enum e_types type);
int 				check_align(t_hdr_blk *new_blk, void *limit_end, size_t min_size);


#endif
