/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 23:39:40 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/11 22:23:40 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define C_BLACK		"\033[30m"
# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_YELLOW		"\033[33m"
# define C_BLUE			"\033[34m"
# define C_MAGENTA		"\033[35m"
# define C_CYAN			"\033[36m"
# define C_GREY			"\033[37m"
# define C_DGREY		"\033[90m"
# define C_LRED			"\033[91m"
# define C_LGREEN		"\033[92m"
# define C_LYELLOW		"\033[93m"
# define C_LBLUE		"\033[94m"
# define C_LMAGENTA		"\033[95m"
# define C_LCYAN		"\033[96m"
# define C_WHITE		"\033[97m"
# define C_CUSTOM(x)	"\033[38;5;"x"m"
# define C_DFL			"\033[39m"

#endif
