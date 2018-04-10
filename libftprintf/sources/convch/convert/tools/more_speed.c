/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_speed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:24:40 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:45:07 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	more_speed_signed(t_fmt *fmt, t_buffer_static *sbuff, char *val, \
																	int *ret)
{
	do_sign(fmt, sbuff, fmt->type.ll, ret);
	*ret += do_filler(sbuff, val, fmt->len);
	return ;
}

void	more_speed_hexa(t_fmt *fmt, t_buffer_static *sbuff, char *ptr, \
																	int *ret)
{
	int		nbrlen;

	nbrlen = 0;
	if (fmt->convch == 'p' || (fmt->flag_char[0] && *ptr != '0'))
		add_prefix_hexa(sbuff, fmt->convch, &nbrlen);
	*ret += do_filler(sbuff, ptr, fmt->len);
	return ;
}
