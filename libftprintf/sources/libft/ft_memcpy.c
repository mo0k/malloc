/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:25:29 by jmoucade          #+#    #+#             */
/*   Updated: 2018/01/11 23:03:19 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *ptr_dst;
	unsigned char *ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (n--)
		*(ptr_dst++) = *(ptr_src++);
	return (dst);
}
