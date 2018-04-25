/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 00:33:06 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/25 18:58:07 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *calloc(size_t count, size_t size)
{
	void	*ptr;

	P_DEBUG_VARGS(LEVEL_1, "CALLOC cout:%d, size:%d\n", count, size);
	if (!count || !size)
		return (NULL);
	if (!(ptr = malloc(count * size)))
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}	