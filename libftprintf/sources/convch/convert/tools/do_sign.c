/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sign.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:06:27 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/25 10:54:00 by mo0ky            ###   ########.fr       */
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
