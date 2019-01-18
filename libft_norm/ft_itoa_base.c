/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:22:35 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/14 17:22:36 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(intmax_t nbr, int base)
{
	int		len;
	int		sign;
	char	*s;

	sign = 0;
	len = ft_nbrlen(nbr, base);
	len += nbr < 0 && base == 10 ? 1 : 0;
	sign = nbr < 0 && base == 10 ? 1 : 0;
	if (!(s = ft_strnew(len + sign)))
		return (NULL);
	len--;
	while (len + 1)
	{
		if (ft_abs(nbr % base) > 9)
			s[len] = ft_abs(nbr % base) - 10 + 'A';
		else
			s[len] = ft_abs(nbr % base) + '0';
		nbr /= base;
		len--;
	}
	*s = sign ? '-' : *s;
	return (s);
}
