/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:54:57 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/15 10:54:57 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_display_p(t_pf_arg *arg, va_list ap)
{
	uintmax_t	p;
	char		*s;
	int			ret;

	p = (size_t)va_arg(ap, uintmax_t);
	MALCH((s = pf_u_itoa_base(p, 16)));
	*s = p == 0 && !arg->precision ? '\0' : *s;
	s = pf_unsigned_precision(s, arg->precision);
	pf_to_lowercase(s);
	ret = ft_strlen(s) + 2;
	if (arg->width > arg->precision && !arg->left_adj)
		ret += pf_padding(arg, arg->pad, ret);
	ft_putstr("0x");
	ft_putstr(s);
	if (arg->width > ret && arg->left_adj)
		ret += pf_padding(arg, ' ', ret);
	free(s);
	return (ret);
}
