/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:18:04 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:01:28 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		is_flag_mlen(char *ptr)
{
	if ((ptr[0] == 'l' && ptr[1] == 'l') || (ptr[0] == 'h' && ptr[1] == 'h'))
		return (2);
	else if (ft_strchr("lhzj", *ptr))
		return (1);
	return (0);
}

static int		check_format(char **aptr)
{
	int		state;
	int		ret;
	char	*ptr;

	state = 0;
	while (**aptr)
	{
		if (ft_strchr(FLAG_CHAR, **aptr))
			++(*aptr);
		else if ((ft_isdigit(**aptr) || **aptr == '.'))
			++(*aptr);
		else if ((ptr = ft_strchr(FLAG_CONVERT, **aptr)))
		{
			++(*aptr);
			return (1);
		}
		else if ((ret = is_flag_mlen(*aptr)))
			*aptr += ret;
		else
			return (0);
	}
	return (0);
}

static int		exit_format(char **begin, char *end, int ret)
{
	*begin = end;
	return (ret);
}

int				get_format(char **begin, t_print *print)
{
	char	tmp[BUFF_SIZE_TEMP];
	char	*end;
	int		diff;

	if (!begin || !*begin)
		return (0);
	end = *begin;
	++end;
	if (!*end || !check_format(&end))
		return (exit_format(begin, end, 0));
	diff = end - *begin;
	if (diff > BUFF_SIZE_TEMP)
		return (exit_format(begin, end, 0));
	ft_strncpy(tmp, *begin, diff);
	tmp[diff] = 0;
	if (do_fmt(tmp, print) == -1)
		return (exit_format(begin, end + 1, -1));
	*begin = end;
	return (1);
}
