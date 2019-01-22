/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlytvyne <vlytvyne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:45:12 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/21 17:14:51 by vlytvyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		sti_debug(t_car *car, int reg_num, int *args)
{
	int	sum;

	if (!SHOW_OPERS || g_cnt_cycles < g_start_to_show)
		return ;
	ft_printf(OPER_INFO);
	ft_printf("r%d %d %d\n", reg_num, args[0], args[1]);
	sum = args[0] + args[1];
	ft_printf("       | -> store to %d + %d = %d ", args[0], args[1], sum);
	ft_printf("(with pc and mod %d)\n", car->position + sum % IDX_MOD);
}

void		sti_op(t_cell *arena, t_car *car)
{
	int	args[2];
	int	reg_num;
	int	reg_val;
	int addr;
	int	i;

	reg_num = get_reg_num(arena, car, 1);
	reg_val = car->regs[reg_num - 1];
	i = -1;
	while (++i < 2)
		if (car->args_types[i + 1] == DIR_CODE)
			args[i] = get_value(arena, to_arg(car, i + 2),
				OP.t_dir_size);
		else if (car->args_types[i + 1] == IND_CODE)
			args[i] = get_ind(arena, car, i + 2, 4);
		else
			args[i] = car->regs[get_reg_num(arena, car, i + 2) - 1];
	addr = car->position + (args[0] + args[1]) % IDX_MOD;
	ft_memrev(&reg_val, 4);
	put_on_arena(arena, (MEM_SIZE + addr) % MEM_SIZE,
		(uint8_t *)(&reg_val), (int[]){ REG_SIZE, car->color });
	sti_debug(car, reg_num, args);
}
