/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:12:31 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/15 13:12:31 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		add_sub_op(t_cell *arena, t_car *car)
{
	int reg_nums[3];
	int	to_put;
	int i;

	i = 0;
	while (i < 3)
	{
		reg_nums[i] = get_reg_num(arena, car, i + 1);
		i++;
	}
	if (car->op == 0x04)
		to_put = car->regs[reg_nums[0] - 1] + car->regs[reg_nums[1] - 1];
	else
		to_put = car->regs[reg_nums[0] - 1] - car->regs[reg_nums[1] - 1];
	car->regs[reg_nums[2] - 1] = to_put;
	car->carry = to_put == 0 ? 1 : 0;
}
