/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 23:25:38 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <ft_printf.h>
# include "debug.h"

# define HDR_PAGE_SIZE sizeof(t_hdr_page)
# define HDR_BLK_SIZE sizeof(t_hdr_blk)
# define CHKM_SIZE 2U
# define TINY_MAX 1024U
# define SMALL_MAX 2048U
# define TINY_PAGE_SIZE getpagesize() * 25
# define SMALL_PAGE_SIZE getpagesize() * 50
# define MIN_SIZE_OBJ 16

typedef struct		s_header_block
{
	unsigned int	bprev;
	unsigned int	bnext;
	unsigned int	fprev;
	unsigned int	fnext;
	unsigned int	size;
	short int		align;
	char			padding[8];
	unsigned char	chkm[CHKM_SIZE];
}					t_hdr_blk;

typedef struct		s_header_page
{
	void			*prev;
	void			*next;
	t_hdr_blk		*last_blk;
	t_hdr_blk		*free;
	size_t			size;
	unsigned int	nbr_blk;
	char			align[2];
	unsigned char	chkm[CHKM_SIZE];
}					t_hdr_page;

# define V (void*)
# define UL (unsigned long)
# define AVAILABLE_BLK(b, p) (V(END_BLK(b)) < V(V(p) + (p)->size))
# define MIN_SIZE(type) ((type) == TINY ? 1U : TINY_MAX + 1U)
# define SPACE(p, b) UL(OFFSET(END_PAGE(p), END_BLK(b)))
# define IS_MIN_SIZE(b, p, t) (HDR_BLK_SIZE + MIN_SIZE(t) > SPACE(p, b))
# define LARGE_SIZE(size) ((size) + HDR_PAGE_SIZE + HDR_BLK_SIZE)

# define MMAP_PROT PROT_WRITE | PROT_READ
# define MMAP_FLG MAP_ANON | MAP_PRIVATE
# define NEW_PAGE(size) (mmap(NULL, (size), MMAP_PROT, MMAP_FLG, -1, 0))
# define DEL_PAGE(ptr) (munmap((ptr), (ptr)->size))
# define NEXT_PAGE(page) ((page)->next)
# define PREV_PAGE(page) ((page)->prev)
# define END_PAGE(page) (V(page) + (page)->size)
# define IN_PAGE(pg, pt) ((pt) > V(FIRST_BLK((pg))) && (pt) < END_PAGE((pg)))
# define ISSUE(p, b) (b ? (unsigned int)(p->free = 0) : (b->fnext = 0))

# define FIRST_BLK(p) ((t_hdr_blk*)(V(p) + HDR_PAGE_SIZE))
# define BEGIN_BLK(b) (V(b) + HDR_BLK_SIZE + (b)->align)
# define END_BLK(b) ((V(b) + HDR_BLK_SIZE + (b)->align + (b)->size))
# define LEN_BLK(b) (HDR_BLK_SIZE + (b)->align + (b)->size)
# define NEXT_BLK(b) ((b)->bnext ? V(b) + (b)->bnext : 0)
# define PREV_BLK(b) ((b)->bprev ? V(b) - (b)->bprev : 0)
# define NEXT_FBLK(b) ((b)->fnext ? V(b) + (b)->fnext: 0)
# define PREV_FBLK(b) ((b)->fprev ? V(b) - (b)->fprev: 0)
# define IS_NEXT_BLK(b, next) (b + (b)->size + HDR_BLK_SIZE == next ? 0 : 1)

# define INIT_HEADER(header, n) (memset(header, 0, n))
# define CHK_HEADER(x, n) (ft_memcmp(V(x) + (n), chkm((x), (n)), CHKM_SIZE))
# define SET_CHKM(x, n) (ft_memmove(V(x) + (n), chkm((x), (n)), CHKM_SIZE))
# define OFFSET_CHKM(n) ((n) - CHKM_SIZE)
# define OFFSET(p1, p2) (V(p1) - V(p2))
# define ALIGN(blk) ((unsigned long)BEGIN_BLK((blk)) % 16UL != 0)

# define FALSE 0
# define TRUE 1

enum				e_ret
{
	ERROR_MEMORY_MANAGER = 1,
	ERROR_ARGS,
	CREATE_NEW_PAGE,
	CREATE_NEW_BLK,
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

enum				e_types
{
	NO_TYPE,
	TINY,
	SMALL,
	LARGE
};

typedef struct		s_info
{
	t_hdr_page		*page;
	t_hdr_blk		*blk;
	enum e_types	type;
}					t_info;

typedef struct		s_free
{
	t_hdr_page		*page;
	t_hdr_blk		*blk;
	enum e_types	type;
}					t_free;

typedef struct		s_memory{
	t_hdr_page		*page;
	enum e_types	type;
}					t_memory;

typedef struct		s_data {
	t_memory		mem_tiny;
	t_memory		mem_small;
	t_memory		mem_large;
	void			*mem_ret;
}					t_data;

t_data				g_data;
pthread_mutex_t		g_mutex;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem(void);

/*
**	Memory
*/
void				initialize_memory(t_memory *mem, enum e_types type, \
																size_t size);
t_memory			*memory_by_type(t_data *data, enum e_types type);

/*
**	Page
*/
void				initialize_page(t_hdr_page **page, t_hdr_page *prev, \
														unsigned int page_size);
int					page_size(enum e_types type);
t_hdr_page			*find_page(t_data *data, void *ptr, enum e_types *type);
void				display_hdr_page(t_hdr_page *hdr_page);
void				del_page(t_hdr_page *page, enum e_types type);

/*
**	Block
*/
enum e_types		type_block(size_t size);
void				create_new_block(t_hdr_blk *block, t_hdr_page *page);
t_hdr_blk			*find_blk(t_hdr_page *page, void *ptr);
void				display_hdr_blk(t_hdr_blk *hdr_blk);

/*
**	Free block
*/
int					manage_free_block(t_hdr_page *page, t_hdr_blk *free, \
														size_t blk_sz);
void				create_free_blk(t_hdr_blk *blk, t_hdr_page *page, \
															enum e_types type);
int					place_free_blk(t_hdr_blk *blk, t_hdr_blk *free, \
															t_hdr_page *page);

/*
**	Checksum
*/
void				*chkm(void *header, size_t size);

/*
**	Tiny - Small
*/
void				manage_tiny_small(t_hdr_page *page, size_t size, \
															enum e_types type);
t_ret_manager		*memory_manager(t_hdr_page *page, size_t blk_size, \
										enum e_types type, t_ret_manager *ret);

/*
**	Large
*/
void				manage_large(t_hdr_page *page, size_t size);

/*
**	Utils
*/
void				kill_prog(int flag, int count);
int					check_space_and_align(t_hdr_page *page, t_hdr_blk *blk, \
															enum e_types type);
int					check_align(t_hdr_blk *new_blk, void *limit_end, \
															size_t min_size);
char				*getenv(char *name);
char				*get_progname(char *env_key);
char				*is_dbg(char *env_key);

#endif
