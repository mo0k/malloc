/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:52 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/11 22:54:40 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

int				do_convch(t_fmt *fmt, t_print *p)
{
	char				*ptr;
	static t_convfunc	convfunc[15] = {
		&convert_str,
		&convert_hexa,
		&convert_int,
		&convert_int,
		&convert_int,
		&convert_octal,
		&convert_octal,
		&convert_uint,
		&convert_uint,
		&convert_hexa,
		&convert_hexa,
		&convert_char,
		&convert_binary,
		&noconvert
	};

	if (!fmt || !p || !(ptr = ft_strchr(FLAG_CONVERT, fmt->convch)))
		return (-1);
	if (convfunc[ptr - FLAG_CONVERT])
		convfunc[ptr - FLAG_CONVERT](fmt, &p->sbuff, &p->args, &p->ret);
	return (p->ret);
}

static void		ajust_fmt(t_fmt *fmt)
{
	if (!fmt)
		return ;
	if (fmt->convch == 'D' || fmt->convch == 'U' || fmt->convch == 'O')
	{
		fmt->convch += 32;
		fmt->flag_mlen = flag_mlen_l;
	}
	else if ((fmt->convch == 'c' || fmt->convch == 's') &&
											fmt->flag_mlen == flag_mlen_l)
	{
		fmt->convch -= 32;
		fmt->flag_mlen = flag_mlen_nodef;
	}
	else if (fmt->convch == 'p')
		fmt->flag_mlen = flag_mlen_ll;
	if (fmt->flag_char[1] && fmt->flag_char[2])
		fmt->flag_char[1] = 0;
	if (fmt->flag_char[4] && fmt->flag_char[3])
		fmt->flag_char[4] = 0;
}

int				do_fmt(char *fmt_string, t_print *print)
{
	t_fmt				fmt;

	if (!fmt_string || !print)
		return (0);
	init_fmt(&fmt);
	if (!parse_fmt(&fmt, fmt_string))
		return (0);
	ajust_fmt(&fmt);
	if (do_convch(&fmt, print) > -1)
		return (1);
	return (-1);
}
