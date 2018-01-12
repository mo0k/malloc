/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 08:50:33 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/11 22:56:48 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <libft.h>
# include <fmt.h>

# define FALSE 0
# define TRUE 1

typedef struct		s_colors
{
	char			color[COLOR_LEN];
	char			*value;
}					t_colors;

typedef void		(*t_convfunc)(t_fmt*, t_buffer_static*, va_list*, int*);

typedef struct		s_print
{
	t_buffer_static	sbuff;
	va_list			args;
	int				ret;
}					t_print;

int					g_fd;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_vprintf(const char *format, va_list ap);
int					ft_vdprintf(int fd, const char *format, \
																va_list ap);

int					analyze_format(t_print *print, const char *format);
int					get_format(char **begin, t_print *print);
int					do_fmt(char *format_string, t_print *print);
int					do_convch(t_fmt *fmt, t_print *print);
int					do_filler(t_buffer_static *sbuff, void *str, size_t size);
int					do_filler_n(t_buffer_static *sbuff, void *c, size_t n);
char				*add_color(char *ptr, t_buffer_static *sbuff);

#endif
