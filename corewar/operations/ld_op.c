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

void		ld_op(uint8_t *arena, t_car *car)
{
	int	arg;
	int reg_num;

	// putfile_hex(MEM_SIZE, arena, 1, 32); //
	// print_args_type(car);
	print_args_type(car);
	reg_num = get_reg_num(arena, car, 2);
	if (car->args_types[0] == DIR_CODE)
		arg = get_dir(arena, car, to_arg(arena, car, 1));
	else
	{
		arg = get_ind(arena, car, to_arg(arena, car, 1)) % IDX_MOD;
		arg = get_dir(arena, car, (MEM_SIZE + car->position + arg) % MEM_SIZE);
	}
	ft_printf("arg: %d, reg num: %d\n", arg, reg_num);
	car->carry = arg == 0 ? 1 : 0;
	car->regs[reg_num - 1] = arg;
}
