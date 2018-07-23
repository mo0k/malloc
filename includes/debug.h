/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:11:03 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/23 22:57:25 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <ft_printf.h>
# include <fcntl.h>
# include "malloc.h"

# define P ft_dprintf
# define FLG O_WRONLY | O_APPEND | O_CREAT
# define X "MALLOC_DEBUG"

int g_fd;

# define PATH() ((is_dbg(X) != 0) ? 1 : 0)
# define OPN() ((PATH() != 0 ? (g_fd = open(is_dbg(X), FLG, 0600)) : 0))
# define CLS() (close(g_fd))
# define DEBUG(fmt) ((OPN() > 0) ? P(g_fd, fmt) && CLS() : 0)
# define DEBUGV(fmt, ...) ((OPN() > 0) ? P(g_fd, fmt, __VA_ARGS__) && CLS() : 0)
#endif
