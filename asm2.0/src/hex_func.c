/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:20:30 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/13 11:45:14 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int32_t		hex_to_int(char *hex)
{
	int32_t	res;
	int		i;
	int		k;

	res = 0;
	i = -1;
	while (hex[++i])
	{
		if (hex[i] >= 'A' && hex[i] <= 'F')
			k = hex[i] - 'A' + 10;
		else
			k = hex[i] - '0';
		res = res * 16 + k;
	}
	return (res);
}

char		*int_to_hex(int32_t nbr, int i)
{
	char	*res;

	res = ft_strnew(i);
	while (--i >= 0)
	{
		res[i] = nbr % 256;
		nbr /= 256;
	}
	return (res);
}
