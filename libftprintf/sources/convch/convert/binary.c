/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:38 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:48:55 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	convert_binary(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, \
																	int *ret)
{
	int		nbrlen;
	int		state;
	char	nb[128];
	char	*ptr;
	int		diff;

	state = 0;
	if (!(ptr = init_unbr(fmt, args, nb, 2)))
		return ;
	nbrlen = fmt->len;
	if (fmt->flag_char[4] && fmt->type.ll >= 0)
		do_space(sbuff, fmt->width, &nbrlen, ret);
	if (fmt->precision == -1 && fmt->width == -1)
	{
		*ret += do_filler(sbuff, ptr, fmt->len);
		return ;
	}
	*ret += (fmt->flag_char[2]) ? do_preci_and_fill(fmt, sbuff, ptr, 1) : 0;
	if (fmt->width > fmt->precision)
		if ((diff = fmt->width - fix_count_signed(fmt, nbrlen)) >= 0)
			*ret += (fmt->flag_char[1] && fmt->precision == -1) ?
				do_filler_n(sbuff, "0", diff) :
				do_filler_n(sbuff, " ", diff);
	*ret += (!fmt->flag_char[2]) ? do_preci_and_fill(fmt, sbuff, ptr, 1) : 0;
}
