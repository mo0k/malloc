/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space_and_align.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:12:43 by jmoucade          #+#    #+#             */
/*   Updated: 2018/07/23 20:56:15 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	check_align(t_hdr_blk *new_blk, void *limit_end, size_t min_size)
{
	t_hdr_blk		*addr;

	if (!new_blk || !limit_end)
		return (ERROR_ARGS);
	addr = (void*)new_blk + HDR_BLK_SIZE;
	new_blk->align = 0;
	while ((void*)addr + min_size + new_blk->align < limit_end
			&& ALIGN(new_blk))
		++new_blk->align;
	if ((void*)addr + min_size + new_blk->align < limit_end)
		return (ALIGN);
	return (NO_ALIGN);
}

int	check_space_and_align(t_hdr_page *page, t_hdr_blk *blk, enum e_types type)
{
	if (page == 0 || blk == 0)
		return (-1);
	while (AVAILABLE_BLK(blk, page) && ALIGN(blk))
		blk->align += 1;
	if (AVAILABLE_BLK(blk, page))
	{
		if (IS_MIN_SIZE(blk, page, type))
		{
			blk->size += END_PAGE(page) - END_BLK(blk);
		}
		return (CREATE_NEW_BLK);
	}
	return (CREATE_NEW_PAGE);
}
