/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:08:00 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:04:03 by jmoucade         ###   ########.fr       */
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
