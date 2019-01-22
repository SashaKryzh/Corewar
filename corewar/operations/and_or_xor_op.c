/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:00:25 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/15 15:00:25 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void			and_or_xor_debug(t_car *car, int reg_num, int *args)
{
	if (SHOW_OPERS && g_cnt_cycles >= g_start_to_show)
	{
		ft_printf(OPER_INFO);
		ft_printf("%d %d r%d\n", args[0], args[1], reg_num);
	}
}

static int		and_op(uint32_t n1, uint32_t n2)
{
	uint32_t	check;
	uint32_t	res;

	res = 0;
	check = MOST_LEFT_BIT;
	while (check != 0)
	{
		if (n1 & check && n2 & check)
			res += check;
		check >>= 1;
	}
	return (res);
}

static int		or_op(uint32_t n1, uint32_t n2)
{
	uint32_t	check;
	uint32_t	res;

	res = 0;
	check = MOST_LEFT_BIT;
	while (check != 0)
	{
		if (n1 & check || n2 & check)
			res += check;
		check >>= 1;
	}
	return (res);
}

static int		xor_op(uint32_t n1, uint32_t n2)
{
	uint32_t	check;
	uint32_t	res;

	res = 0;
	check = MOST_LEFT_BIT;
	while (check != 0)
	{
		if ((n1 & check || n2 & check) && ((n1 & check) != (n2 & check)))
			res += check;
		check >>= 1;
	}
	return (res);
}

void			and_or_xor_op(t_cell *arena, t_car *car)
{
	int reg_num;
	int	args[2];
	int	i;

	reg_num = get_reg_num(arena, car, 3);
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i] == DIR_CODE)
			args[i] = get_value(arena, to_arg(car, i + 1),
				OP.t_dir_size);
		else if (car->args_types[i] == IND_CODE)
			args[i] = get_ind(arena, car, i + 1, 4);
		else if (car->args_types[i] == REG_CODE)
			args[i] = car->regs[get_reg_num(arena, car, i + 1) - 1];
		i++;
	}
	if (car->op == 0x06)
		car->regs[reg_num - 1] = and_op(args[0], args[1]);
	else if (car->op == 0x07)
		car->regs[reg_num - 1] = or_op(args[0], args[1]);
	else
		car->regs[reg_num - 1] = xor_op(args[0], args[1]);
	car->carry = car->regs[reg_num - 1] == 0 ? 1 : 0;
	and_or_xor_debug(car, reg_num, args);
}
