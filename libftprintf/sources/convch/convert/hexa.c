/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:45 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 23:02:08 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		func(t_fmt *fmt, t_buffer_static *sbuff, char *ptr, \
																int *nbrlen)
{
	if (fmt->convch == 'p' || (fmt->flag_char[0] && *ptr != '0'))
		add_prefix_hexa(sbuff, fmt->convch, nbrlen);
	return (1);
}

static int		fix_diff(t_fmt *fmt, char *ptr, int *diff)
{
	if ((fmt->convch == 'p' || (fmt->flag_char[0] && *ptr != '0')) &&
													!fmt->flag_char[2])
		*diff = (*diff - 2 < 0) ? 0 : *diff - 2;
	return (1);
}

static char		*init_ptr(t_fmt *fmt, va_list *args, char nb[128])
{
	char	*ptr;

	ptr = init_unbr(fmt, args, nb, 16);
	if (fmt->convch == 'X')
		ptr = ft_strtoupper(ptr);
	return (ptr);
}

static int		do_width(t_fmt *fmt, t_buffer_static *sbuff, char *ptr, \
																	int *nbrlen)
{
	int		diff;

	if ((diff = fmt->width - fix_count_unsigned(fmt, *nbrlen, ptr)) >= 0)
	{
		return (fix_diff(fmt, ptr, &diff) && fmt->flag_char[1] &&
				fmt->precision == -1 && !fmt->prefix && (fmt->prefix = 1) &&
				func(fmt, sbuff, ptr, nbrlen) ?
											do_filler_n(sbuff, "0", diff) :
											do_filler_n(sbuff, " ", diff));
	}
	return (0);
}

void			convert_hexa(t_fmt *fmt, t_buffer_static *sbuff, \
													va_list *args, int *ret)
{
	int		nbrlen;
	char	nb[128];
	char	*ptr;

	ptr = init_ptr(fmt, args, nb);
	if (fmt->precision == -1 && fmt->width == -1)
		return (more_speed_hexa(fmt, sbuff, ptr, ret));
	fmt->prefix = 0;
	nbrlen = fmt->len;
	if (fmt->flag_char[2])
	{
		if ((fmt->convch == 'p' || (fmt->flag_char[0] && *ptr != '0')) &&
														(fmt->prefix = 1))
			add_prefix_hexa(sbuff, fmt->convch, &nbrlen);
		*ret += do_preci_and_fill_spec(fmt, sbuff, ptr);
	}
	if (fmt->width > fmt->precision)
		ret += do_width(fmt, sbuff, ptr, &nbrlen);
	if (!fmt->flag_char[2])
	{
		if (!fmt->prefix && (fmt->convch == 'p' ||
								(fmt->flag_char[0] && *ptr != '0')))
			add_prefix_hexa(sbuff, fmt->convch, &nbrlen);
		*ret += do_preci_and_fill_spec(fmt, sbuff, ptr);
	}
}
