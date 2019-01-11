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

void		sti_op(uint8_t *arena, t_car *car)
{
	int addr;
	int	i;
	int	reg;
	int	args[2];

	print_args_type(car);
	reg = car->regs[get_reg_num(arena, car, 1) - 1];
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i + 1] == DIR_CODE)
			args[i] = get_dir(arena, car, to_arg(arena, car, i + 2));
		else if (car->args_types[i + 1] == IND_CODE)
			args[i] = get_ind(arena, car, to_arg(arena, car, i + 2));
		else
			args[i] = car->regs[get_reg_num(arena, car, i + 2) - 1];
		i++;
	}
	ft_printf("reg: %d, arg2: %d, arg3: %d\n", reg, args[0], args[1]); //
	// putbytes_bit((char *)(&reg), sizeof(reg));
	addr = (args[0] + args[1]) % IDX_MOD;
	ft_memrev(&reg, sizeof(reg));
	put_on_arena(arena, (car->position + addr) % MEM_SIZE, (uint8_t *)(&reg), REG_SIZE);
}
