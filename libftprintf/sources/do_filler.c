/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:13:52 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 23:00:43 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	do_one_by_one(t_buffer_static *sbuff, void *str, size_t size)
{
	int				ret;
	unsigned int	i;

	ret = 0;
	i = -1;
	write(g_fd, sbuff->buffer, sbuff->used_size);
	ret += sbuff->used_size;
	init_buffer_static(sbuff);
	while (++i < size)
	{
		while (!fill_buffer_static(sbuff, str + i, 1))
		{
			write(g_fd, sbuff->buffer, sbuff->used_size);
			ret += sbuff->used_size;
			init_buffer_static(sbuff);
		}
	}
	return (ret);
}

int			do_filler(t_buffer_static *sbuff, void *str, size_t size)
{
	int				ret;

	if (!str)
		return (0);
	if (size <= BUFF_SIZE_INIT)
	{
		ret = 0;
		while (!fill_buffer_static(sbuff, str, size))
		{
			write(g_fd, sbuff->buffer, sbuff->used_size);
			ret += sbuff->used_size;
			init_buffer_static(sbuff);
		}
		return (ret);
	}
	else
		return (do_one_by_one(sbuff, str, size));
}

static int	do_one_by_one_n(t_buffer_static *sbuff, void *c, size_t n)
{
	int				ret;
	unsigned int	i;

	ret = 0;
	i = -1;
	write(g_fd, sbuff->buffer, sbuff->used_size);
	ret += sbuff->used_size;
	init_buffer_static(sbuff);
	while (++i < n)
	{
		while (!filln_buffer_static(sbuff, (void*)c, 1))
		{
			write(g_fd, sbuff->buffer, sbuff->used_size);
			ret += sbuff->used_size;
			init_buffer_static(sbuff);
		}
	}
	return (ret);
}

int			do_filler_n(t_buffer_static *sbuff, void *c, size_t n)
{
	int				ret;

	ret = 0;
	if (n <= BUFF_SIZE_INIT)
	{
		while (!filln_buffer_static(sbuff, (void*)c, n))
		{
			write(g_fd, sbuff->buffer, sbuff->used_size);
			ret += sbuff->used_size;
			init_buffer_static(sbuff);
		}
	}
	else
		return (do_one_by_one_n(sbuff, c, n));
	return (ret);
}
