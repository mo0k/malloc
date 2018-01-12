/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 13:34:15 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/12 17:55:23 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *realloc(void *ptr, size_t size)
{
	(void)size;
	//write(1, "REALLOC\n", 8);
	ft_printf("REALLOC\n");
	return (ptr);
}