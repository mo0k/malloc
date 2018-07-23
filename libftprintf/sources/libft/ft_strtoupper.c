/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 22:57:16 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:06:28 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtoupper(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
	return (str);
}
