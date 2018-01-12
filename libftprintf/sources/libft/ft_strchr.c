/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:36:34 by jmoucade          #+#    #+#             */
/*   Updated: 2018/01/11 23:04:08 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char			*ft_strchr(const char *s, int c)
{
	char		*ptr;

	if (!s)
		return (0);
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == c)
			return ((char *)s + (ptr - s));
		++ptr;
	}
	return (0);
}