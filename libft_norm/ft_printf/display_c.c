/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 08:43:27 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/13 08:43:27 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				pf_display_c(t_pf_arg *arg, va_list ap, int percent)
{
	char			s[arg->width > 0 ? arg->width : 1];
	unsigned char	c;
	int				i;

	c = percent ? '%' : (unsigned char)va_arg(ap, int);
	i = -1;
	while (++i < arg->width)
		s[i] = arg->zero_pad ? '0' : ' ';
	s[0] = arg->left_adj ? c : s[0];
	if (!arg->left_adj)
		s[arg->width > 0 ? arg->width - 1 : 0] = c;
	write(1, s, arg->width > 0 ? arg->width : 1);
	return (arg->width > 0 ? arg->width : 1);
}
