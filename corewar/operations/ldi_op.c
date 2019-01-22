/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 18:14:52 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/14 18:14:52 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void	ldi_debug(t_car *car, int reg_num, int *args)
{
	if (!SHOW_OPERS || g_cnt_cycles < g_start_to_show)
		return ;
	ft_printf(OPER_INFO);
	ft_printf("%d %d r%d\n", args[0], args[1], reg_num);
	ft_printf("       | -> load from ");
	ft_printf("%d + %d = %d ", args[0], args[1], args[0] + args[1]);
	if (car->op == 0x0A)
		ft_printf("(with pc and mod %d)\n", car->position +
			(args[0] + args[1]) % IDX_MOD);
	else
		ft_printf("(with pc %d)\n", car->position +
			args[0] + args[1]);
}

void	ldi_op(t_cell *arena, t_car *car)
{
	int reg_num;
	int	args[2];
	int	addr;
	int	i;

	reg_num = get_reg_num(arena, car, 3);
	i = -1;
	while (++i < 2)
		if (car->args_types[i] == DIR_CODE)
			args[i] = get_value(arena, to_arg(car, i + 1),
				OP.t_dir_size);
		else if (car->args_types[i] == IND_CODE)
			args[i] = get_ind(arena, car, i + 1, 4);
		else if (car->args_types[i] == REG_CODE)
			args[i] = car->regs[get_reg_num(arena, car, i + 1) - 1];
	addr = args[0] + args[1];
	addr = car->op == 0x0A ? addr % IDX_MOD : addr;
	addr = (MEM_SIZE + (car->position + addr) % MEM_SIZE) % MEM_SIZE;
	car->regs[reg_num - 1] = get_value(arena, addr, 4);
	if (car->op == 0x0E)
		car->carry = car->regs[reg_num - 1] == 0 ? 1 : 0;
	ldi_debug(car, reg_num, args);
}
