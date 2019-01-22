/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:25:45 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 17:14:46 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		st_debug(t_car *car, int reg_num, int where)
{
	if (!SHOW_OPERS || g_cnt_cycles < g_start_to_show)
		return ;
	ft_printf(OPER_INFO);
	ft_printf("r%d ", reg_num);
	ft_printf("%d\n", where);
}

void		st_op(t_cell *arena, t_car *car)
{
	int reg_num;
	int	reg_val;
	int	where;
	int	tmp;

	reg_num = get_reg_num(arena, car, 1);
	reg_val = car->regs[reg_num - 1];
	if (car->args_types[1] == REG_CODE)
	{
		where = get_reg_num(arena, car, 2);
		tmp = where;
		car->regs[where - 1] = reg_val;
	}
	else
	{
		where = get_value(arena, to_arg(car, 2), IND_SIZE);
		tmp = where;
		where = (MEM_SIZE + (car->position + where % IDX_MOD)
			% MEM_SIZE) % MEM_SIZE;
		ft_memrev(&reg_val, 4);
		put_on_arena(arena, where, (uint8_t *)(&reg_val),
			(int[]){ REG_SIZE, car->color });
	}
	st_debug(car, reg_num, tmp);
}
