/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:45:58 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:40:58 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		do_precision_convert(t_fmt *fmt, t_buffer_static *sbuff,
																	int *ret)
{
	if (fmt->precision <= fmt->len)
		*ret += do_filler(sbuff, fmt->type.s, fmt->precision);
	else
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
}

static void		do_width_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	if (fmt->flag_char[2])
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
	if (fmt->len < fmt->width)
	{
		if (fmt->flag_char[1])
			*ret += do_filler_n(sbuff, "0", fmt->width - fmt->len);
		else
			*ret += do_filler_n(sbuff, " ", fmt->width - fmt->len);
	}
	if (!fmt->flag_char[2])
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
}

static void		do_full_convert(t_fmt *fmt, t_buffer_static *sbuff, int *ret)
{
	int				tmp;

	if (fmt->flag_char[2])
	{
		tmp = (fmt->precision < fmt->len) ? fmt->precision : fmt->len;
		*ret += do_filler(sbuff, fmt->type.s, tmp);
	}
	if (fmt->precision <= fmt->len)
	{
		if (fmt->precision < fmt->width)
			*ret += (fmt->flag_char[1]) ?
					do_filler_n(sbuff, "0", fmt->width - fmt->precision) :
					do_filler_n(sbuff, " ", fmt->width - fmt->precision);
	}
	else if (fmt->len < fmt->width)
		*ret = (fmt->flag_char[1]) ?
				do_filler_n(sbuff, "0", fmt->width - fmt->len) :
				do_filler_n(sbuff, " ", fmt->width - fmt->len);
	if (!fmt->flag_char[2])
	{
		tmp = (fmt->precision < fmt->len) ? fmt->precision : fmt->len;
		*ret += do_filler(sbuff, fmt->type.s, tmp);
	}
}

void			convert_str(t_fmt *fmt, t_buffer_static *sbuff, va_list *args,
																	int *ret)
{
	static char		null[] = "(null)";

	if (!(fmt->type.s = va_arg(*args, char*)))
		fmt->type.s = null;
	fmt->len = ft_strlen(fmt->type.s);
	if (fmt->width == -1 && fmt->precision == -1)
		*ret += do_filler(sbuff, fmt->type.s, fmt->len);
	else if (fmt->width > -1 && fmt->precision > -1)
		do_full_convert(fmt, sbuff, ret);
	else if (fmt->width > -1 && fmt->precision == -1)
		do_width_convert(fmt, sbuff, ret);
	else
		do_precision_convert(fmt, sbuff, ret);
}
