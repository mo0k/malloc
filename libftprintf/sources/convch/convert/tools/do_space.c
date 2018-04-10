/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:08:00 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/24 22:52:51 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	do_space(t_buffer_static *sbuff, int width, int *nbrlen, int *ret)
{
	if (!sbuff || !nbrlen || !ret)
		return ;
	*ret += do_filler(sbuff, " ", 1);
	if (width > -1)
		(*nbrlen)++;
}
