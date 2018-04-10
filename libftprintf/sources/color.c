/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 09:53:15 by mo0ky             #+#    #+#             */
/*   Updated: 2017/10/01 21:47:54 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static t_colors		*init_tab_color(void)
{
	static t_colors		tab_colors[TAB_COLOR_LEN] = {
		{"BLACK", C_BLACK},
		{"RED", C_RED},
		{"GREEN", C_GREEN},
		{"YELLOW", C_YELLOW},
		{"BLUE", C_BLUE},
		{"MAGENTA", C_MAGENTA},
		{"CYAN", C_CYAN},
		{"GREY", C_GREY},
		{"WHITE", C_WHITE},
		{"LRED", C_LRED},
		{"LGREEN", C_LGREEN},
		{"LYELLOW", C_LYELLOW},
		{"LBLUE", C_LBLUE},
		{"LMAGENTA", C_LMAGENTA},
		{"LCYAN", C_LCYAN},
		{"LGREY", C_DGREY},
		{"EOC", C_DFL}
	};

	return (tab_colors);
}

static char			*apply_color(char *value, t_colors *tab_color)
{
	int					i;

	if (!value || !tab_color)
		return (NULL);
	i = -1;
	while (++i < TAB_COLOR_LEN)
		if (!ft_strcmp(tab_color[i].color, value))
			return (tab_color[i].value);
	return (NULL);
}

char				*add_color(char *ptr, t_buffer_static *sbuff)
{
	char				temp[COLOR_LEN + 1];
	int					i;
	char				*color;
	t_colors			*tab_color;

	tab_color = init_tab_color();
	i = 0;
	while (*ptr && *ptr != '}' && i < COLOR_LEN)
	{
		temp[i++] = *ptr;
		++ptr;
	}
	if (*ptr != '}')
		return (NULL);
	temp[i] = 0;
	i = -1;
	while (temp[++i])
		temp[i] = ft_toupper(temp[i]);
	if (!(color = apply_color(temp, tab_color)))
		return (NULL);
	do_filler(sbuff, color, ft_strlen(color));
	return (++ptr);
}
