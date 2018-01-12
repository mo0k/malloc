/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:47:22 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/12 17:48:58 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void *reallocf(void *ptr, size_t size)
{
	ft_printf("REALLOCF\n");
	(void)ptr;
	(void)size;
	return (0);
}

void *valloc(size_t size)
{
	ft_printf("VALLOC\n");
	(void)size;
	return (0);
}