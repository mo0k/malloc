/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:41:38 by jmoucade          #+#    #+#             */
/*   Updated: 2018/01/11 23:01:01 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t		ft_strlen(const char *str)
{
	char	*cur;

	if (!str)
		return (0);
	cur = (char *)str;
	while (1)
	{
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
		if (!*(cur++))
			break ;
	}
	return (cur - str - 1);
}
