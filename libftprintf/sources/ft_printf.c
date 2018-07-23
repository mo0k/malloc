/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 17:07:12 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:01:17 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_printf(const char *format, ...)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = 1;
	va_start(print.args, format);
	if (!analyze_format(&print, format))
		return (-1);
	va_end(print.args);
	return (print.ret);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = fd;
	va_start(print.args, format);
	if (!analyze_format(&print, format))
		return (-1);
	va_end(print.args);
	return (print.ret);
}

int		ft_vprintf(const char *format, va_list ap)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = 1;
	ft_memmove(&print.args, ap, sizeof(va_list));
	if (!analyze_format(&print, format))
		return (-1);
	return (print.ret);
}

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = fd;
	ft_memmove(&print.args, ap, sizeof(va_list));
	if (!analyze_format(&print, format))
		return (-1);
	return (print.ret);
}
