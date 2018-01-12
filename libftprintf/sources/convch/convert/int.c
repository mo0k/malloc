/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:38 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/25 22:50:58 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	do_width(t_fmt *fmt, t_buffer_static *sbuff, int nbrlen, int *ret)
{
	int diff;

	if ((diff = fmt->width - fix_count_signed(fmt, nbrlen)) >= 0)
	{
		*ret += (fmt->flag_char[1] && fmt->precision == -1) ?
			do_filler_n(sbuff, "0", diff) : do_filler_n(sbuff, " ", diff);
	}
}

void	convert_int(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	int		nbrlen;
	int		state;
	char	test[128];
	char	*ptr;

	state = 0;
	if (!(ptr = init_nbr(fmt, args, test, 10)))
		return ;
	nbrlen = fmt->len;
	if (fmt->flag_char[4] && fmt->type.ll >= 0)
		do_space(sbuff, fmt->width, &nbrlen, ret);
	if (fmt->precision == -1 && fmt->width == -1)
		return (more_speed_signed(fmt, sbuff, ptr, ret));
	if ((fmt->flag_char[1] && fmt->precision == -1) || fmt->flag_char[2])
		if ((state = 1) && do_sign(fmt, sbuff, fmt->type.ll, ret) == 2
						&& fmt->width > -1)
			nbrlen++;
	if (fmt->flag_char[2])
		*ret += do_preci_and_fill(fmt, sbuff, ptr, 1);
	if (fmt->width > fmt->precision)
		do_width(fmt, sbuff, nbrlen, ret);
	if (!state)
		do_sign(fmt, sbuff, fmt->type.ll, ret);
	if (!fmt->flag_char[2])
		*ret += do_preci_and_fill(fmt, sbuff, ptr, 1);
}
