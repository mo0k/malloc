/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 23:23:27 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:02:46 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char		*itoa_base(char nb[128], int value, int base, int *len)
{
	long			lvalue;
	static char		hex[] = "0123456789abcdef";

	lvalue = (long)value;
	nb += 127;
	*nb = '\0';
	if (value == 0)
	{
		*len = 1;
		--nb;
		*nb = '0';
		return (nb);
	}
	if (value < 0)
		lvalue *= -1;
	while (lvalue)
	{
		++(*len);
		--nb;
		*nb = hex[lvalue % base];
		lvalue /= base;
	}
	return (nb);
}

static char		*iltoa_base(char nb[128], long value, int base, int *len)
{
	static char		hex[] = "0123456789abcdef";
	t_llint			lvalue;

	lvalue = (t_llint)value;
	nb += 127;
	*nb = '\0';
	if (value == 0)
	{
		*len = 1;
		--nb;
		*nb = '0';
		return (nb);
	}
	if (value < 0)
		lvalue *= -1;
	while (lvalue)
	{
		++(*len);
		--nb;
		*nb = hex[lvalue % base];
		lvalue /= base;
	}
	return (nb);
}

static char		*illtoa_base(char nb[128], t_llint value, int base, int *len)
{
	static char		hex[] = "0123456789abcdef";
	t_ullint		lvalue;

	lvalue = (t_ullint)value;
	nb += 127;
	*nb = '\0';
	if (value == 0)
	{
		*len = 1;
		--nb;
		*nb = '0';
		return (nb);
	}
	if (value < 0)
		lvalue *= -1;
	while (lvalue)
	{
		++(*len);
		--nb;
		*nb = hex[lvalue % base];
		lvalue /= base;
	}
	return (nb);
}

static t_llint	get_nbr(int flag_mlen, va_list *args)
{
	if (flag_mlen < flag_mlen_l)
	{
		if (flag_mlen == flag_mlen_nodef)
			return ((int)va_arg(*args, t_llint));
		else if (flag_mlen == flag_mlen_hh)
			return ((signed char)va_arg(*args, t_llint));
		else
			return ((short int)va_arg(*args, t_llint));
	}
	else
	{
		if (flag_mlen == flag_mlen_l)
			return ((t_lint)va_arg(*args, t_llint));
		else if (flag_mlen == flag_mlen_ll)
			return ((t_llint)va_arg(*args, t_llint));
		else if (flag_mlen == flag_mlen_z)
			return ((t_llint)va_arg(*args, size_t));
		else
			return ((t_llint)va_arg(*args, int));
	}
}

char			*init_nbr(t_fmt *fmt, va_list *args, char nb[128], int base)
{
	fmt->type.ll = get_nbr(fmt->flag_mlen, args);
	fmt->len = 0;
	if (fmt->flag_mlen < flag_mlen_l)
	{
		if (fmt->flag_mlen == flag_mlen_nodef)
			return (itoa_base(nb, (int)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_hh)
			return (itoa_base(nb, (signed char)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_h)
			return (itoa_base(nb, (short int)fmt->type.ll, base, &fmt->len));
	}
	else
	{
		if (fmt->flag_mlen == flag_mlen_l)
			return (iltoa_base(nb, (long)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_ll)
			return (illtoa_base(nb, (long long)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_z)
			return (illtoa_base(nb, (long long)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == flag_mlen_j)
			return (illtoa_base(nb, (long long)fmt->type.ll, base, &fmt->len));
	}
	return (NULL);
}
