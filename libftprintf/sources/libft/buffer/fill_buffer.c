/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 23:59:17 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/11 23:11:59 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		fill_buffer(t_buffer_static *ctrl, void *input, size_t size)
{
	if (!ctrl || !input)
		return (0);
	ft_memmove(ctrl->buffer + ctrl->used_size, input, size);
	ctrl->remaining_size -= size;
	ctrl->used_size += size;
	ctrl->buffer[ctrl->used_size] = 0;
	return (1);
}

int				fill_buffer_static(t_buffer_static *ctrl, void *input,
																size_t size)
{
	if (!ctrl || !input)
		return (0);
	return (available_space(size, ctrl->remaining_size) ?
										fill_buffer(ctrl, input, size) : 0);
}
