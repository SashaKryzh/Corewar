/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:59:51 by okryzhan          #+#    #+#             */
/*   Updated: 2018/11/16 13:59:52 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*itostr(uintmax_t n, int after)
{
	char	*s;
	int		i;

	MALCH((s = ft_strnew(after)));
	i = 0;
	while (n)
	{
		s[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i < after)
	{
		s[i] = '0';
		i++;
	}
	ft_strrev(s);
	return (s);
}

char		*pf_dtoa(long double n, int after)
{
	char		*is;
	char		*fs;
	char		*tmp;
	intmax_t	ipart;
	long double	fpart;

	ipart = (intmax_t)n;
	fpart = n - (intmax_t)n;
	MALCH((is = ft_itoa_base(n, 10)));
	if (n < 0 && ipart == 0)
	{
		MALCH((tmp = ft_strjoin("-", is)));
		free(is);
		is = tmp;
	}
	if (after != 0)
	{
		ft_strcat(is, ".");
		fpart = fpart * ft_power(10, after);
		fpart = fpart < 0 ? -fpart : fpart;
		fs = itostr((uintmax_t)fpart, after);
		ft_strcat(is, fs);
		free(fs);
	}
	return (is);
}
