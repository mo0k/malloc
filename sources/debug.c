/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 20:56:55 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	*ft_getenv(const char *name)
{
	int				count;
	char			*sep;
	extern char		**environ;

	count = 0;
	if (!name)
		return (0);
	while (environ && environ[count])
	{
		if (!(sep = ft_strchr(environ[count], '=')))
			return (0);
		else
			*sep = 0;
		if (!ft_strcmp(name, environ[count]))
		{
			*sep = '=';
			return (sep + 1);
		}
		*sep = '=';
		++count;
	}
	return (0);
}

char	*get_progname(char *env_key)
{
	static char		ret[48];
	static char		*value;

	if (value)
		return (value);
	if (!(value = ft_getenv(env_key)))
	{
		strcpy(ret, "Unknow");
		return (ret);
	}
	return (value);
}

char	*is_dbg(char *env_key)
{
	static char		*path;

	if (path)
		return (path);
	if (!(path = ft_getenv(env_key)))
	{
		return (0);
	}
	return (path);
}
