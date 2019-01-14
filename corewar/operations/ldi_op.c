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

void	ldi_op(uint8_t *arena, t_car *car)
{
	int reg_num;
	int	args[2];
	int	addr;
	int	i;

	print_args_type(car);
	ft_printf("\n");
	reg_num = get_reg_num(arena, car, 3);
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i] == DIR_CODE)
			args[i] = get_value(arena, to_arg(arena, car, i + 1), OP.t_dir_size);
		else if (car->args_types[i] == IND_CODE)
			args[i] = get_ind(arena, car, to_arg(arena, car, i + 1), 4);
		else if (car->args_types[i] == REG_CODE)
			args[i] = car->regs[get_reg_num(arena, car, i + 1) - 1];
		i++;
	}
	addr = (MEM_SIZE + car->position + ((args[0] + args[1]) % IDX_MOD)) % MEM_SIZE;
	car->regs[reg_num - 1] = get_value(arena, addr, 4);
	ft_printf("%d %d %d, %d\n", args[0], args[1], reg_num, car->regs[reg_num - 1]); //
	putfile_hex(MEM_SIZE, arena, 1, 32); //
	exit(1);
}
