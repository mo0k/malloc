/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:53:58 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/11 22:56:30 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FMT_H
# define FMT_H

# define FLAG_CHAR "#0-+ "
# define FLAG_CONVERT "spdDioOuUxXcb%"
# define BUFF_SIZE_TEMP 1024
# define TAB_COLOR_LEN 17
# define COLOR_LEN 10
# include <fmt_types.h>

int		parse_fmt(t_fmt *f, char *f_string);
char	*init_nbr(t_fmt *f, va_list *args, char nb[128], int base);
char	*init_unbr(t_fmt *f, va_list *args, char nb[128], int base);
int		init_fmt(t_fmt *f);
int		init_fmt_spec(t_fmt *f, char convch);
int		add_prefix_hexa(t_buffer_static *sbuff, char convch, int *len);
int		do_preci_and_fill(t_fmt *f, t_buffer_static *buff, char *s, char sign);
int		do_preci_and_fill_spec(t_fmt *f, t_buffer_static *buff, char *s);
int		do_preci_and_fill_spec2(t_fmt *f, t_buffer_static *buff, char *s);
int		fix_count_signed(t_fmt *f, int nbrlen);
int		fix_count_unsigned(t_fmt *f, int nbrlen, char *ptr);
int		do_sign(t_fmt *f, t_buffer_static *buff, t_llint nbr, int *ret);
void	do_space(t_buffer_static *buff, int width, int *nbrlen, int *ret);
void	more_speed_signed(t_fmt *f, t_buffer_static *buff, char *s, int *ret);
void	more_speed_hexa(t_fmt *f, t_buffer_static *buff, char *ptr, int *ret);
void	uitoa_do_binary(char **nb, char value, int *len);
char	*uitoa_return_null(char *nb, int *len, int base);
void	ret_error(int *ret);
void	noconvert(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_str(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_char(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_int(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_uint(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_octal(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_hexa(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_wchar(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_wstr(t_fmt *f, t_buffer_static *buff, va_list *args, int *ret);
void	convert_binary(t_fmt *f, t_buffer_static *buff, va_list *args, \
																	int *ret);

#endif
