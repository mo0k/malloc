/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:45:30 by jmoucade          #+#    #+#             */
/*   Updated: 2018/01/11 23:04:44 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	len;
	int		state;

	state = 0;
	len = 0;
	while (len < n)
	{
		if (!state && !src[len])
			state = 1;
		if (state)
			dest[len] = '\0';
		else
			dest[len] = src[len];
		len++;
	}
	return (dest);
}
