/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:03:29 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/12 13:03:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_display_s(t_pf_arg *arg, va_list ap)
{
	int		len;
	char	*s;

	if (!(s = (char *)va_arg(ap, const char *)))
		s = "(null)";
	len = ft_strlen(s);
	len = arg->precision < len && arg->precision != -1 ? arg->precision : len;
	if (arg->width > len && !arg->left_adj)
		pf_padding(arg, arg->pad, len);
	ft_putnstr(s, len);
	if (arg->width > len && arg->left_adj)
		pf_padding(arg, ' ', len);
	return (arg->width > len ? arg->width : len);
}
