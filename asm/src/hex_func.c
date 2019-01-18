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
	int32_t			res;
	int				i;
	int				k;

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

char		*int_to_hex(int32_t nbr, int size)
{
	unsigned int	temp;
	int				i;
	unsigned int	max;
	char			*res;

	if (size == 1)
		max = 255;
	if (size == 2)
		max = 65535;
	if (size == 4)
		max = 4294967295;
	if (nbr < 0)
		temp = max + nbr + 1;
	else
		temp = nbr;
	res = ft_strnew(size);
	i = size;
	while (--i >= 0)
	{
		res[i] = temp % 256;
		temp /= 256;
	}
	return (res);
}
