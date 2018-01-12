/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:35 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 23:00:50 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	convert_uint(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, \
																	int *ret)
{
	int		nbrlen;
	int		state;
	char	nb[128];
	char	*ptr;
	int		diff;

	state = 0;
	if (!(ptr = init_unbr(fmt, args, nb, 10)))
		return ;
	nbrlen = fmt->len;
	if (fmt->flag_char[2])
		*ret = do_preci_and_fill(fmt, sbuff, ptr, 0);
	if (fmt->width > fmt->precision)
	{
		if ((diff = fmt->width - fix_count_unsigned(fmt, nbrlen, ptr)) >= 0)
			*ret += (fmt->flag_char[1] && fmt->precision == -1) ?
											do_filler_n(sbuff, "0", diff) :
											do_filler_n(sbuff, " ", diff);
	}
	if (!fmt->flag_char[2])
		*ret = do_preci_and_fill(fmt, sbuff, ptr, 0);
}
