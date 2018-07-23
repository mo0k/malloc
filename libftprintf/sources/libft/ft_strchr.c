/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:36:34 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:06:14 by jmoucade         ###   ########.fr       */
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
