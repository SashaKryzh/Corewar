/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:13:35 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/15 13:13:35 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	pf_get_unsigned(t_pf_arg *arg, va_list ap)
{
	uintmax_t n;

	n = va_arg(ap, uintmax_t);
	if (arg->pf_length == hh)
		n = (unsigned char)n;
	if (arg->pf_length == h)
		n = (unsigned short)n;
	if (arg->pf_length == ll)
		n = (unsigned long long)n;
	if (arg->pf_length == l)
		n = (unsigned long)n;
	if (arg->pf_length == j)
		n = (uintmax_t)n;
	if (arg->pf_length == z)
		n = (size_t)n;
	if (arg->pf_length == no_lenght)
		n = (unsigned int)n;
	return (n);
}

intmax_t	pf_get_signed(t_pf_arg *arg, va_list ap)
{
	intmax_t n;

	n = va_arg(ap, intmax_t);
	if (arg->pf_length == hh)
		n = (char)n;
	if (arg->pf_length == h)
		n = (short)n;
	if (arg->pf_length == ll)
		n = (long long)n;
	if (arg->pf_length == l)
		n = (long)n;
	if (arg->pf_length == j)
		n = (intmax_t)n;
	if (arg->pf_length == z)
		n = (ssize_t)n;
	if (arg->pf_length == no_lenght)
		n = (int)n;
	return (n);
}
