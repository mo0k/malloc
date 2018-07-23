/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:35:29 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:04:57 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		convert_char(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, \
																	int *ret)
{
	int		len;

	len = 1;
	fmt->type.c = va_arg(*args, int);
	if (fmt->width > -1)
	{
		if (fmt->flag_char[2])
			ret += do_filler(sbuff, &fmt->type.c, 1);
		if (len < fmt->width)
			ret += fmt->flag_char[1] ?
				do_filler_n(sbuff, "0", fmt->width - len) :
				do_filler_n(sbuff, " ", fmt->width - len);
		if (!fmt->flag_char[2])
			ret += do_filler(sbuff, &fmt->type.c, 1);
	}
	else
		ret += do_filler(sbuff, &fmt->type.c, 1);
}
