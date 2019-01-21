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

void		st_debug(t_car *car, int reg_num, int where)
{
	if (!SHOW_OPERS || g_cnt_cycles < g_start_to_show)
		return ;
	printf(OPER_INFO);
	printf("r%d ", reg_num);
	printf("%d\n", where);
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
		where = (MEM_SIZE + car->position + where % IDX_MOD) % MEM_SIZE;
		ft_memrev(&reg_val, 4);
		put_on_arena(arena, where, (uint8_t *)(&reg_val),
			(int[]){ REG_SIZE, car->color });
		if (g_visual)
			show_on_arena(arena, where, REG_SIZE);
	}
	st_debug(car, reg_num, tmp);
}
