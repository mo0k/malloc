/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:53:58 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/11 22:56:02 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FMT_TYPES_H
# define FMT_TYPES_H

enum					e_flag_mlen
{
	flag_mlen_nodef,
	flag_mlen_hh,
	flag_mlen_h,
	flag_mlen_l,
	flag_mlen_ll,
	flag_mlen_z,
	flag_mlen_j
};

union					u_type
{
	char				c;
	long				l;
	int					d;
	t_uint				u;
	char				*s;
	t_llint				ll;
	t_ullint			ull;
};

typedef struct			s_fmt
{
	int					flag_char[5];
	int					width;
	int					precision;
	enum e_flag_mlen	flag_mlen;
	char				convch;
	union u_type		type;
	int					prefix;
	int					len;
}						t_fmt;

#endif
