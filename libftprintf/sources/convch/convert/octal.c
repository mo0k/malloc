/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:49 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:05:32 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		add_zero(char **ptr, int *len)
{
	if (**ptr == '0')
		return ;
	--*ptr;
	**ptr = '0';
	++*len;
}

void			convert_octal(t_fmt *fmt, t_buffer_static *sbuff, \
														va_list *args, int *ret)
{
	int		nbrlen;
	char	test[128];
	char	*ptr;
	int		diff;

	if (!(ptr = init_unbr(fmt, args, test, 8)))
		return ;
	if (fmt->flag_char[0])
		add_zero(&ptr, &fmt->len);
	nbrlen = fmt->len;
	if (fmt->flag_char[4])
		do_space(sbuff, fmt->width, &nbrlen, ret);
	if (fmt->precision == -1 && fmt->width == -1)
	{
		*ret += do_filler(sbuff, ptr, fmt->len);
		return ;
	}
	*ret += (fmt->flag_char[2]) ? do_preci_and_fill_spec2(fmt, sbuff, ptr) : 0;
	if (fmt->width > fmt->precision)
		if ((diff = fmt->width - fix_count_unsigned(fmt, nbrlen, ptr)) >= 0)
			*ret += (fmt->flag_char[1] && fmt->precision == -1) ?
											do_filler_n(sbuff, "0", diff) :
											do_filler_n(sbuff, " ", diff);
	if (!fmt->flag_char[2])
		*ret += do_preci_and_fill_spec2(fmt, sbuff, ptr);
}
