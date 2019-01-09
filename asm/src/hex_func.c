/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoroziu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:20:30 by amoroziu          #+#    #+#             */
/*   Updated: 2019/01/09 16:50:52 by amoroziu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int32_t			hex_to_int(char *hex)
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

static int 	get_size(int32_t nbr)
{
	int		size;

	size = 0;
	while (nbr && ++size)
		nbr /= 16;
	return (size);
}

char		*int_to_hex(int32_t nbr)
{
	int		temp;
	int		i;
	char	*res;

	if (nbr < 0)
		temp = 4294967296 + nbr;
	else
		temp = nbr;
	i = get_size(nbr);
	res = ft_strnew(i);
	while (--i >= 0)
	{
		if (temp % 16 >= 10)
			res[i] = temp % 16 - 10 + 'A';
		else
			res[i] = '0' + temp % 16;
		temp /= 16;
	}
	return (res);
}
