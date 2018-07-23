/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:18:38 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:02:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		init_fmt(t_fmt *fmt)
{
	if (!fmt)
		return (0);
	fmt->width = -1;
	fmt->precision = -1;
	fmt->flag_mlen = flag_mlen_nodef;
	fmt->convch = 0;
	fmt->len = 0;
	fmt->flag_char[0] = 0;
	fmt->flag_char[1] = 0;
	fmt->flag_char[2] = 0;
	fmt->flag_char[3] = 0;
	fmt->flag_char[4] = 0;
	return (1);
}

int		init_fmt_spec(t_fmt *fmt, char convch)
{
	if (!fmt)
		return (0);
	fmt->width = -1;
	fmt->precision = -1;
	fmt->flag_mlen = flag_mlen_nodef;
	fmt->convch = convch;
	fmt->len = 0;
	fmt->flag_char[0] = 0;
	fmt->flag_char[1] = 0;
	fmt->flag_char[2] = 0;
	fmt->flag_char[3] = 0;
	fmt->flag_char[4] = 0;
	return (1);
}
