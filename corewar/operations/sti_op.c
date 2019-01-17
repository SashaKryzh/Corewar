/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:45:12 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/11 13:45:12 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		sti_op(t_cell *arena, t_car *car)
{
	int	args[2];
	int	reg_val;
	int addr;
	int	i;

	// print_args_type(car);
	reg_val = car->regs[get_reg_num(arena, car, 1) - 1];
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i + 1] == DIR_CODE)
			args[i] = get_value(arena, to_arg(arena, car, i + 2), OP.t_dir_size);
		else if (car->args_types[i + 1] == IND_CODE)
			args[i] = get_ind(arena, car, i + 2, OP.t_dir_size);
		else
			args[i] = car->regs[get_reg_num(arena, car, i + 2) - 1];
		i++;
	}
	// ft_printf("reg: %d, arg2: %d, arg3: %d\n", reg_val, args[0], args[1]); //
	addr = (args[0] + args[1]) % IDX_MOD;
	ft_memrev(&reg_val, 4); // BIG ENDIAN
	put_on_arena(arena, (MEM_SIZE + car->position + addr) % MEM_SIZE,
		(uint8_t *)(&reg_val), REG_SIZE);
	// if (g_cnt_cycles == 164)
	// {
	// 	print_args_type(car);
	// 	ft_printf("reg_val: %d, arg1: %d, arg2: %d\n", reg_val, args[0], args[1]);
	// }
}
