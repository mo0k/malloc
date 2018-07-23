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

static void	clear_all_pages(t_hdr_page *root)
{
	t_hdr_page *next;

	while (root)
	{
		next = root;
		DEL_PAGE(root);
		root = next;
	}
}

static void	clear_data(void)
{
	if (g_data.mem_tiny.page)
		clear_all_pages(g_data.mem_tiny.page);
	if (g_data.mem_small.page)
		clear_all_pages(g_data.mem_tiny.page);
	if (g_data.mem_large.page)
		clear_all_pages(g_data.mem_tiny.page);
}

void		kill_prog(int flag, int count)
{
	clear_data();
	if (flag == CHECKSUM_CORRUPED)
	{
		DEBUGV("CHECKSUM_CORRUPED Numero:%d\n", count);
	}
	kill(0, SIGABRT);
}
