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
	int reg_val;
	int	where;

	reg_val = car->regs[get_reg_num(arena, car, 1) - 1];
	if (car->args_types[1] == REG_CODE)
	{
		where = get_reg_num(arena, car, 2);
		car->regs[where - 1] = reg_val;
	}
	else
	{
		where = get_value(arena, to_arg(arena, car, 2), IND_SIZE) % IDX_MOD;
		// if (g_cnt_cycles == g_dump - 1)
		// 	ft_printf("%d\n", where);
		where = (MEM_SIZE + car->position + where) % MEM_SIZE;
		ft_memrev(&reg_val, 4);
		put_on_arena(arena, where, (uint8_t *)(&reg_val), REG_SIZE);
	}
	// if (g_cnt_cycles == g_dump - 1)
	// {
	// 	// ft_printf("pos: %d, %02x %02x %02x %02x\n", car->position, arena[car->position + 1].v, arena[car->position + 2].v, arena[car->position + 3].v, arena[car->position + 4].v);
	// 	print_args_type(car);
	// 	ft_memrev(&reg_val, 4);
	// 	ft_printf("num: %d, val: %d\n", get_reg_num(arena, car, 1), reg_val);
	// 	ft_printf("where %d\n", where);
	// 	ft_printf("car id : %d\n", car->id);
	// }
}
