/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 20:56:26 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*chkm(void *header, size_t size)
{
	static unsigned char	chkm[2];
	size_t					i;
	int						j;
	unsigned int			sum1;
	unsigned int			sum2;

	if (!header)
		return (NULL);
	i = 0;
	j = 0;
	sum1 = 0;
	sum2 = 0;
	while (i < size)
	{
		sum1 += *(unsigned char*)(header + i);
		sum2 += *(unsigned char*)(header + i) * ++j;
		++i;
	}
	chkm[0] = sum1 & 0xFF;
	chkm[1] = sum2 & 0xFF;
	return ((void*)chkm);
}
