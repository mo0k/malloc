/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 11:18:04 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:49:37 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		color_text(t_print *print, char **ptr)
{
	char	*temp;

	if (!(temp = add_color(*ptr + 1, &print->sbuff)))
	{
		print->ret += do_filler(&print->sbuff, *ptr, 1);
		if (**ptr)
			++(*ptr);
	}
	else
		*ptr = temp;
}

static void		go_shortcut(t_print *print, char **ptr)
{
	t_fmt	fmt;

	init_fmt_spec(&fmt, *(*ptr + 1));
	do_convch(&fmt, print);
	*ptr += 2;
}

static int		do_analyze(t_print *print, char **ptr)
{
	if (*(*ptr + 1) == '%')
	{
		print->ret += do_filler(&print->sbuff, "%", 1);
		*ptr += 2;
		return (1);
	}
	else if (ft_strchr("dsxucoib", *(*ptr + 1)))
	{
		go_shortcut(print, ptr);
		return (1);
	}
	else
	{
		if (get_format(ptr, print) == -1)
			return (0);
		return (1);
	}
}

int				analyze_format(t_print *print, const char *format)
{
	char	*ptr;

	ptr = (char *)format;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			if (!do_analyze(print, &ptr))
				return (0);
		}
		else if (*ptr == '{')
			color_text(print, &ptr);
		else
		{
			if (*ptr)
				print->ret += do_filler(&print->sbuff, ptr++, 1);
			else
				break ;
		}
	}
	write(g_fd, print->sbuff.buffer, print->sbuff.used_size);
	print->ret += print->sbuff.used_size;
	return (1);
}
