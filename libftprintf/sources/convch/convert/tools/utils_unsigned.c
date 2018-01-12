/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 00:30:11 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:57:26 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		add_prefix_hexa(t_buffer_static *sbuff, char convch, int *len)
{
	char	c[2];

	*len += 2;
	c[0] = '0';
	c[1] = (convch == 'p') ? 'x' : convch;
	return (do_filler(sbuff, c, 2));
}

void	uitoa_do_binary(char **nb, char value, int *len)
{
	++(*len);
	--(*nb);
	**nb = value;
}

char	*uitoa_return_null(char *nb, int *len, int base)
{
	--nb;
	if (base == 2)
	{
		*len = 9;
		nb -= 8;
		ft_memmove(nb, "00000000", 8);
	}
	else
	{
		*len = 1;
		*nb = '0';
	}
	return (nb);
}
