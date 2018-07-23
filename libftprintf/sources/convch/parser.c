/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:22:05 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:02:15 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static enum e_flag_mlen	is_flag_mlen(char *ptr)
{
	if (ptr[0] == 'l' && ptr[1] == 'l')
		return (flag_mlen_ll);
	else if (*ptr == 'l')
		return (flag_mlen_l);
	else if (ptr[0] == 'h' && ptr[1] == 'h')
		return (flag_mlen_hh);
	else if (*ptr == 'h')
		return (flag_mlen_h);
	else if (*ptr == 'z')
		return (flag_mlen_z);
	else if (*ptr == 'j')
		return (flag_mlen_j);
	return (flag_mlen_nodef);
}

static void				set_flag_char(int flag_char[5], char *ptr)
{
	int				i;

	if (!flag_char || !ptr)
		return ;
	i = -1;
	while (FLAG_CHAR[++i])
	{
		if (*ptr == FLAG_CHAR[i])
		{
			flag_char[i] = TRUE;
			return ;
		}
	}
}

static void				set_width(int *width, char **aptr)
{
	char			c;
	char			*start;

	if (!width || !aptr || !*aptr)
		return ;
	start = *aptr;
	while (**aptr && ft_isdigit(**aptr))
		++(*aptr);
	if (start < *aptr)
	{
		c = **aptr;
		**aptr = 0;
		*width = ft_atoi(start);
		if (*width < 0)
			*width = 0;
		**aptr = c;
		--(*aptr);
	}
}

static void				set_precision(int *precision, char **aptr)
{
	char			c;
	char			*start;
	char			*tmp;

	if (!precision || !aptr || !*aptr)
		return ;
	tmp = *aptr;
	if (*(*aptr + 1) != '.' && !ft_strchr(FLAG_CONVERT, *(*aptr + 1)))
		++(*aptr);
	start = *aptr;
	while (**aptr && ft_isdigit(**aptr))
		++(*aptr);
	if (start < *aptr)
	{
		c = **aptr;
		**aptr = 0;
		*precision = ft_atoi(start);
		if (*precision < 0)
			*precision = 0;
		**aptr = c;
	}
	else
		*precision = 0;
	if (tmp < *aptr)
		--(*aptr);
}

int						parse_fmt(t_fmt *f, char *fmt_string)
{
	unsigned int	temp;

	if (!fmt_string)
		return (0);
	++fmt_string;
	temp = 0;
	while (*fmt_string)
	{
		if (ft_strchr(FLAG_CHAR, *fmt_string))
			set_flag_char(f->flag_char, fmt_string);
		else if (*fmt_string == '.')
			set_precision(&f->precision, &fmt_string);
		else if (ft_isdigit(*fmt_string))
			set_width(&f->width, &fmt_string);
		else if (*fmt_string && !*(fmt_string + 1))
			f->convch = *fmt_string;
		else if ((temp = is_flag_mlen(fmt_string)) > f->flag_mlen)
		{
			f->flag_mlen = temp;
			if (f->flag_mlen == flag_mlen_ll || f->flag_mlen == flag_mlen_hh)
				++fmt_string;
		}
		++fmt_string;
	}
	return (1);
}
