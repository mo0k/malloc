/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:06:27 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:03:52 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			do_sign(t_fmt *fmt, t_buffer_static *sbuff, long long int nbr, \
																	int *ret)
{
	if (!sbuff || !ret)
		return (0);
	if (nbr < 0)
	{
		*ret += do_filler(sbuff, "-", 1);
		return (1);
	}
	else if (nbr >= 0 && fmt->flag_char[3])
	{
		*ret += do_filler(sbuff, "+", 1);
		return (2);
	}
	return (0);
}
