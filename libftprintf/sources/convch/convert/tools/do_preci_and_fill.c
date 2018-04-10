/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_preci_and_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:52:26 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 23:02:40 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			do_preci_and_fill(t_fmt *fmt, t_buffer_static *sbuff, char *val, \
																	char sign)
{
	t_llint		nb;
	int			ret;

	if (!fmt || !sbuff)
		return (0);
	ret = 0;
	nb = (!sign ? fmt->type.ll : fmt->type.ull);
	if (fmt->precision > fmt->len)
		ret += do_filler_n(sbuff, "0", fmt->precision - fmt->len);
	if (fmt->precision == 0 && nb == 0)
		return (0);
	return (do_filler(sbuff, val, fmt->len) + ret);
}

int			do_preci_and_fill_spec(t_fmt *fmt, t_buffer_static *sbuff, \
																	char *val)
{
	t_llint		nb;
	int			ret;

	if (!fmt || !sbuff)
		return (0);
	ret = 0;
	nb = fmt->type.ull;
	if (fmt->precision > fmt->len)
		ret += do_filler_n(sbuff, "0", fmt->precision - fmt->len);
	if (fmt->precision == 0 && nb == 0)
		return (0);
	return (do_filler(sbuff, val, fmt->len) + ret);
}

int			do_preci_and_fill_spec2(t_fmt *fmt, t_buffer_static *sbuff, \
																	char *val)
{
	t_llint		nb;
	int			ret;

	if (!fmt || !sbuff)
		return (0);
	ret = 0;
	nb = fmt->type.ull;
	if (fmt->precision > fmt->len)
		ret += do_filler_n(sbuff, "0", fmt->precision - fmt->len);
	if (fmt->precision == 0 && nb == 0)
		return (fmt->flag_char[0] ? do_filler(sbuff, "0", 1) : 0);
	return (do_filler(sbuff, val, fmt->len) + ret);
}
