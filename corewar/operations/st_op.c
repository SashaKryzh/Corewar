/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:25:45 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/15 13:25:45 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		st_op(t_cell *arena, t_car *car)
{
	int reg_num;
	int	where;

	reg_num = get_reg_num(arena, car, 1);
	if (car->args_types[1] == REG_CODE)
	{
		where = get_reg_num(arena, car, 2);
		car->regs[where - 1] = car->regs[reg_num - 1];
	}
	else
	{
		where = get_value(arena, to_arg(arena, car, 2), IND_SIZE) % IDX_MOD;
		where = (MEM_SIZE + car->position + where) % MEM_SIZE;
		put_on_arena(arena, where, (uint8_t *)(&car->regs[reg_num - 1]), REG_SIZE);
	}
}
