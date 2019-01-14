/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:09:36 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/14 16:09:36 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int			get_ind(uint8_t *arena, t_car *car, int arg_num, int size)
{
	int addr;
	int	res;

	addr = get_value(arena, to_arg(arena, car, arg_num), IND_SIZE) % IDX_MOD;
	addr = (MEM_SIZE + car->position + addr) % MEM_SIZE;
	res = get_value(arena, addr, size);
	return (res);
}

/*
**  n[3] >> 7... for negative values when size == 2
*/

int		get_value(uint8_t *arena, int start, int size)
{
	char	n[4];
	int		res;
	int		i;

	i = 0;
	ft_bzero(n, 4);
	while (i < size)
	{
		n[i + size % 4] = arena[(start + i) % MEM_SIZE];
		i++;
	}
    if (n[3] >> 7 && size == 2)
    {
        n[0] = -1;
        n[1] = -1;
    }
	ft_memcpy(&res, n, 4);
	ft_memrev(&res, 4);
	return (res);
}
