/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:23:39 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/11 16:23:39 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		ld_debug(t_car *car, int reg_num, int arg)
{
	if (!SHOW_OPERS || g_cnt_cycles < g_start_to_show)
		return ;
	ft_printf(OPER_INFO);
	ft_printf("%d r%d\n", arg, reg_num);
}

/*
**	If lld called it: get_ind wont do % IDX_MOD
*/

void		ld_op(t_cell *arena, t_car *car)
{
	int reg_num;
	int	arg;

	reg_num = get_reg_num(arena, car, 2);
	if (car->args_types[0] == DIR_CODE)
		arg = get_value(arena, to_arg(car, 1), REG_SIZE);
	else
		arg = get_ind(arena, car, 1, REG_SIZE);
	car->regs[reg_num - 1] = arg;
	car->carry = arg == 0 ? 1 : 0;
	ld_debug(car, reg_num, arg);
}
