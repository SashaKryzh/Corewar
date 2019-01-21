/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:11:29 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/15 15:11:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		u_nbrlen(uintmax_t nbr, int base)
{
	int len;

	if (nbr == 0)
		return (1);
	len = 0;
	while (nbr != 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

char	*pf_u_itoa_base(uintmax_t nbr, int base)
{
	int		len;
	int		sign;
	char	*s;

	sign = 0;
	len = u_nbrlen(nbr, base);
	if (!(s = ft_strnew(len + sign)))
		return (NULL);
	len--;
	while (len + 1)
	{
		if (nbr % base > 9)
			s[len] = ft_abs(nbr % base) - 10 + 'A';
		else
			s[len] = ft_abs(nbr % base) + '0';
		nbr /= base;
		len--;
	}
	return (s);
}

int		pf_display_u(t_pf_arg *arg, va_list ap)
{
	uintmax_t	n;
	char		*s;
	int			ret;

	n = pf_get_unsigned(arg, ap);
	MALCH((s = pf_u_itoa_base(n, 10)));
	arg->pref = '\0';
	*s = arg->precision == 0 && n == 0 ? '\0' : *s;
	s = pf_unsigned_precision(s, arg->precision);
	ret = ft_strlen(s);
	if (arg->width > arg->precision && !arg->left_adj)
		ret += pf_padding(arg, arg->pad, ret);
	ft_putstr(s);
	if (arg->width > ret && arg->left_adj)
		ret += pf_padding(arg, ' ', ft_strlen(s));
	free(s);
	return (ret);
}
