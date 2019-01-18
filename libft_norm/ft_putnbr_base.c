/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:03:05 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/21 13:03:05 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_base(intmax_t n, int base)
{
	int		i;
	int		ret;
	char	s[ft_nbrlen(n, base) + (n < 0 && base == 10)];

	ret = ft_nbrlen(n, base) + (n < 0 && base == 10);
	s[0] = n == 0 ? '0' : s[0];
	s[0] = n < 0 && base == 10 ? '-' : s[0];
	i = ret - 1;
	while (n != 0)
	{
		if (ABS(n % base) > 9)
			s[i--] = ABS(n % base) - 10 + 'A';
		else
			s[i--] = ABS(n % base) + '0';
		n /= base;
	}
	write(1, s, ret);
	return (ret);
}
