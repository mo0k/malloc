/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 23:23:27 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:02:55 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char			*uitoa_base(char nb[128], t_uint value, int base, \
																int *len)
{
	static char		hex[] = "0123456789abcdef";
	t_ulint			lvalue;
	int				i;

	lvalue = (t_ulint)value;
	i = 0;
	nb += 127;
	*nb = '\0';
	if (value == 0)
		return (uitoa_return_null(nb, len, base));
	while (lvalue)
	{
		++(*len);
		--nb;
		*nb = hex[lvalue % base];
		lvalue /= base;
		if (base == 2 && lvalue && !(*len % 8))
			uitoa_do_binary(&nb, ' ', &i);
	}
	while (base == 2 && *len % 8)
		uitoa_do_binary(&nb, '0', len);
	*len += i;
	return (nb);
}

static char			*uiltoa_base(char nb[128], t_ulint value, int base, \
																	int *len)
{
	static char		hex[] = "0123456789abcdef";
	t_ullint		lvalue;
	int				i;

	lvalue = (t_ullint)value;
	i = 0;
	nb += 127;
	*nb = '\0';
	if (value == 0)
		return (uitoa_return_null(nb, len, base));
	while (lvalue)
	{
		++(*len);
		--nb;
		*nb = hex[lvalue % base];
		lvalue /= base;
		if (base == 2 && lvalue && !(*len % 8))
			uitoa_do_binary(&nb, ' ', &i);
	}
	while (base == 2 && *len % 8)
		uitoa_do_binary(&nb, '0', len);
	*len += i;
	return (nb);
}

static char			*uilltoa_base(char nb[128], t_ullint value, int base, \
																	int *len)
{
	static char		hex[] = "0123456789abcdef";
	t_ullint		lvalue;
	int				i;

	lvalue = (t_ullint)value;
	i = 0;
	nb += 127;
	*nb = '\0';
	if (value == 0)
		return (uitoa_return_null(nb, len, base));
	while (lvalue)
	{
		++(*len);
		--nb;
		*nb = hex[lvalue % base];
		lvalue /= base;
		if (base == 2 && lvalue && !(*len % 8))
			uitoa_do_binary(&nb, ' ', &i);
	}
	while (base == 2 && *len % 8)
		uitoa_do_binary(&nb, '0', len);
	*len += i;
	return (nb);
}

static t_ullint		get_nbr(int flag_mlen, va_list *args)
{
	if (flag_mlen < flag_mlen_l)
	{
		if (flag_mlen == flag_mlen_nodef)
			return ((t_uint)va_arg(*args, t_ullint));
		else if (flag_mlen == flag_mlen_hh)
			return ((t_uchar)va_arg(*args, t_ullint));
		else
			return ((t_ushortint)va_arg(*args, t_ullint));
	}
	else
	{
		if (flag_mlen == flag_mlen_l)
			return ((t_ulint)va_arg(*args, t_ullint));
		else if (flag_mlen == flag_mlen_ll)
			return ((t_ullint)va_arg(*args, t_ullint));
		else if (flag_mlen == flag_mlen_z)
			return ((t_ullint)va_arg(*args, size_t));
		else
			return ((t_ullint)va_arg(*args, t_uint));
	}
}

char				*init_unbr(t_fmt *fmt, va_list *args, char nb[128], \
																	int base)
{
	fmt->type.ull = get_nbr(fmt->flag_mlen, args);
	fmt->len = 0;
	if (fmt->flag_mlen < flag_mlen_l)
	{
		if (fmt->flag_mlen == flag_mlen_nodef)
			return (uitoa_base(nb, (t_uint)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_hh)
			return (uitoa_base(nb, (t_uchar)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_h)
			return (uitoa_base(nb, (t_ushortint)fmt->type.ull, base, \
																&fmt->len));
	}
	else
	{
		if (fmt->flag_mlen == flag_mlen_l)
			return (uiltoa_base(nb, (t_ulint)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_ll)
			return (uilltoa_base(nb, (t_ullint)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_z)
			return (uilltoa_base(nb, (t_ullint)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_j)
			return (uilltoa_base(nb, (t_ullint)fmt->type.ull, base, &fmt->len));
	}
	return (NULL);
}
