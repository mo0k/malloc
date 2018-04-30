/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 00:33:06 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/29 23:22:15 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *calloc(size_t count, size_t size)
{
	void	*ptr;

	//P_DEBUG_FILE_VARGS(LEVEL_1, "CALLOC cout:%d, size:%d\n", count, size);
	P_DEBUG_FILE_VARGS(LEVEL_1, "%s call calloc(%zd, %zd)\n", get_progname("_"), count, size);
	if (!count || !size)
		return (NULL);
	if (!(ptr = malloc(count * size)))
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}	