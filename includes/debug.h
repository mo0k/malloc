/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 15:11:03 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 22:12:04 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <ft_printf.h>
# include <fcntl.h>

# define DEBUG 0
# define LEVEL_1 1
# define LEVEL_2 2
# define LEVEL_3 3

int g_fd;
//ajouter global flag_open

# define OPEN_DEBUG() (g_fd = open("/Users/jmoucade/Desktop/DEBUG", O_WRONLY | O_APPEND | O_CREAT, 0600)) // a modifer
# define CLOSE_DEBUG() (close(g_fd))
# define P_DEBUG(lvl, fmt) ((DEBUG) >= lvl  ? ft_dprintf(g_fd, fmt) : 0)
# define P_DEBUG_VARGS(lvl, fmt, ...) ((DEBUG) >= lvl ? ft_dprintf(g_fd, fmt, __VA_ARGS__): 0)
# define P_DEBUG_FILE(lvl, fmt) ((DEBUG >= lvl && OPEN_DEBUG() > 0) ? ft_dprintf(g_fd, fmt) && CLOSE_DEBUG() : 0)
# define P_DEBUG_FILE_VARGS(lvl, fmt, ...) \
				((DEBUG >= lvl && OPEN_DEBUG() > 0) ? ft_dprintf(g_fd, fmt, __VA_ARGS__) && CLOSE_DEBUG() : 0)

#endif
