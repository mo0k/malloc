/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/22 23:10:51 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

char	*ft_getenv(const char *name)
{
	int		count;
	char	*sep;

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

void	kill_prog(int flag, int count)
{
	//clear data
	if (flag == CHECKSUM_CORRUPED)
	{
		P_DEBUG_FILE_VARGS(LEVEL_1, "CHECKSUM_CORRUPED Numero:%d\n", count);
	}
	kill(0, SIGABRT);
}

void	manage_large(t_hdr_page *page, size_t size)
{
	t_hdr_blk	*blk;

	if (!page)
		return ;
	if (CHK_HEADER(page, OFFSET_CHKM(HDR_PAGE_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 18);
	blk = FIRST_BLK(page);
	if (CHK_HEADER(blk, OFFSET_CHKM(HDR_BLK_SIZE)))
		kill_prog(CHECKSUM_CORRUPED, 19);
	if (blk->size == 0)
	{
		blk->size = size;
		create_new_block(blk, page);
		SET_CHKM(blk, OFFSET_CHKM(HDR_BLK_SIZE));
		g_data.mem_ret = BEGIN_BLK(blk);
	}
	else
	{
		if (!page->next)
		{
			initialize_page((t_hdr_page**)&page->next, page, LARGE_SIZE(size));
			SET_CHKM(page, OFFSET_CHKM(HDR_PAGE_SIZE));
		}
		return (manage_large(page->next, size));
	}
}

void	*malloc(size_t size)
{
	t_memory			*mem;
	enum e_types		type;

	P_DEBUG_FILE_VARGS(LEVEL_1
						, "%s call malloc(%d)\n"
						, get_progname("_")
						, size);
	type = type_block(size);
	mem = memory_by_type(&g_data, type);
	if (mem->page == NULL)
		initialize_memory(mem, type, size);
	(type == LARGE) ? manage_large(mem->page, size)
					: manage_tiny_small(mem->page, size, mem->type);
	return (g_data.mem_ret);
}
