/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:34:15 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/12 17:14:22 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *calloc(size_t count, size_t size)
{
	write(1, "CALLOC\n", 7);
	ft_printf("count:%zd, size:%zd\n", count, size);
	void *ptr;

	if (count == 0 || size == 0)
		return (0);
	if (!(ptr = malloc(count * size)))
		return (0);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}