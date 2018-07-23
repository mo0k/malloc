/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 00:33:06 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 20:56:03 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	DEBUGV("%s call calloc(%zd, %zd)\n"
						, get_progname("_")
						, count
						, size);
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(ptr = malloc(count * size)))
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
