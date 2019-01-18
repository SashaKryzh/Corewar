/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 07:39:47 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/25 07:39:48 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(int n)
{
	size_t count;

	if (n == 0)
		return (1);
	count = n < 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*res;

	if (n == -2147483648)
	{
		res = ft_strdup("-2147483648");
		return (res);
	}
	len = ft_count(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	while (n >= 10)
	{
		res[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	res[len - 1] = n + '0';
	return (res);
}
