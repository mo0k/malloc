/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:53:32 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:04:11 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			fix_count_signed(t_fmt *fmt, int nbrlen)
{
	if (!fmt)
		return (0);
	if (fmt->precision > fmt->len)
	{
		return ((nbrlen > fmt->len ||
			(fmt->type.ll >= 0 && fmt->flag_char[3]) ||
			fmt->type.ll < 0) ? fmt->precision + 1 : fmt->precision);
	}
	else
	{
		if (((fmt->type.ll >= 0 && fmt->flag_char[3]) ||
			fmt->type.ll < 0))
			return (fmt->len + 1);
		else if (fmt->precision == 0 && fmt->type.ll == 0)
			return (0);
		else
			return (nbrlen);
	}
}

int			fix_count_unsigned(t_fmt *fmt, int nbrlen, char *ptr)
{
	if (!fmt)
		return (0);
	if (fmt->precision > fmt->len)
	{
		if ((nbrlen > fmt->len) && ((fmt->convch == 'p' ||
									(fmt->flag_char[0] && *ptr != '0'))))
			return (fmt->precision + 2);
		return (nbrlen > fmt->len ? fmt->precision + 1 : fmt->precision);
	}
	else
		return ((fmt->precision == 0 && fmt->type.ull == 0) ? 0 : nbrlen);
}
