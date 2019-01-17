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

void	ldi_op(t_cell *arena, t_car *car)
{
	int reg_num;
	int	args[2];
	int	addr;
	int	i;

	// print_args_type(car);
	// ft_printf("\n");
	reg_num = get_reg_num(arena, car, 3);
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i] == DIR_CODE)
			args[i] = get_value(arena, to_arg(arena, car, i + 1),
				OP.t_dir_size);
		else if (car->args_types[i] == IND_CODE)
			args[i] = get_ind(arena, car, to_arg(arena, car, i + 1), 4);
		else if (car->args_types[i] == REG_CODE)
			args[i] = car->regs[get_reg_num(arena, car, i + 1) - 1];
		i++;
	}
	addr = args[0] + args[1];
	addr = car->op == 0x0A ? addr % IDX_MOD : addr;
	addr = (MEM_SIZE + car->position + addr) % MEM_SIZE;
	car->regs[reg_num - 1] = get_value(arena, addr, 4);
	car->carry = car->op == 0x0E && car->regs[reg_num - 1] == 0 ? 1 : 0;
	// ft_printf("%d\n", g_cnt_cycles);
	// ft_printf("addr: %d + %d, reg_num: %d, put in reg: %d\n", args[0], args[1], reg_num, car->regs[reg_num - 1]); //
	// putfile_hex(MEM_SIZE, arena, 1, 32); //
	// exit(1); //
}
