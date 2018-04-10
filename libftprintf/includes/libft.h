/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2018/04/02 22:37:09 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <colors.h>

# define BUFF_SIZE_INIT 4096
# define ABS(x) (x<0) ? (x*-1) : (x)

typedef long int				t_lint;
typedef long long int			t_llint;
typedef unsigned int			t_uint;
typedef unsigned long int		t_ulint;
typedef unsigned long long int	t_ullint;
typedef unsigned short int		t_ushortint;
typedef unsigned char			t_uchar;

typedef struct		s_controler_buffer_static
{
	char			buffer[BUFF_SIZE_INIT];
	char			*current;
	size_t			buff_size;
	size_t			remaining_size;
	size_t			used_size;
}					t_buffer_static;

void				init_buffer_static(t_buffer_static *controler);
int					fill_buffer_static(t_buffer_static *controler, \
													void *input, size_t size);
int					filln_buffer_static(t_buffer_static *ctrl, void *c, \
																size_t n);
int					available_space(size_t new_size, size_t remaining_size);
size_t				ft_strlen(const char *str);
void		*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memrcpy(void *dst, const void *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_isdigit(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
char				*ft_strtoupper(char *str);


#endif
