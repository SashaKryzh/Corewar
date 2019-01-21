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

/*
**	Return id of needed reg, so you must do (num - 1) : 1 -> 0 for array of regs
*/

uint8_t		get_reg_num(t_cell *arena, t_car *car, int arg_num)
{
	int i;
	int	to_jump;

	i = 0;
	to_jump = 1 + OP.is_args_types;
	while (i < arg_num - 1)
	{
		to_jump += car->args_sizes[i];
		i++;
	}
	return (arena[(car->position + to_jump) % MEM_SIZE].v);
}

/*
**	Use this function to get data from IND address
**	0x0D - lld
*/

int			get_ind(t_cell *arena, t_car *car, int arg_num, int size)
{
	int addr;
	int	res;

	addr = get_value(arena, to_arg(car, arg_num), IND_SIZE);
	if (car->op != 0x0D)
		addr %= IDX_MOD;
	addr = (MEM_SIZE + (car->position + addr) % MEM_SIZE) % MEM_SIZE;
	res = get_value(arena, addr, size);
	return (res);
}

/*
**	Use this function to get data from the operation
**  n[3] >> 7... for negative values when size == 2
*/

int			get_value(t_cell *arena, int start, int size)
{
	char	n[4];
	int		res;
	int		i;

	i = 0;
	ft_bzero(n, 4);
	while (i < size)
	{
		n[i + size % 4] = arena[(start + i) % MEM_SIZE].v;
		i++;
	}
	if (n[2] >> 7 && size == 2)
	{
		n[0] = -1;
		n[1] = -1;
	}
	ft_memcpy(&res, n, 4);
	ft_memrev(&res, 4);
	return (res);
}

void		get_op_code(t_car *car, uint8_t op)
{
	car->op = op;
	if (op >= 0x01 && op <= 0x10)
		car->remain_cycles = g_op[op - 1].to_wait;
}
