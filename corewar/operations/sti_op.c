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

void		sti_debug(t_cell *arena, t_car *car, int reg_val, int *args)
{
	int	sum;

	if (!SHOW_OPERS)
		return ;
	ft_printf(OPER_INFO);
	ft_printf("r%d %d %d ", get_reg_num(arena, car, 1), args[0], args[1]);
	ft_printf("\n");
	sum = args[0] + args[1];
	ft_printf("       | -> store to %d + %d = %d ", args[0], args[1], sum);
	ft_printf("(with pc and mod %d)\n", car->position + sum % IDX_MOD);
}

void		sti_op(t_cell *arena, t_car *car)
{
	int	args[2];
	int	reg_val;
	int addr;
	int	i;

	reg_val = car->regs[get_reg_num(arena, car, 1) - 1];
	i = 0;
	while (i < 2)
	{
		if (car->args_types[i + 1] == DIR_CODE)
			args[i] = get_value(arena, to_arg(arena, car, i + 2),
				OP.t_dir_size);
		else if (car->args_types[i + 1] == IND_CODE)
			args[i] = get_ind(arena, car, i + 2, OP.t_dir_size);
		else
			args[i] = car->regs[get_reg_num(arena, car, i + 2) - 1];
		i++;
	}
	addr = car->position + (args[0] + args[1]) % IDX_MOD;
	ft_memrev(&reg_val, 4);
	put_on_arena(arena, (MEM_SIZE + addr) % MEM_SIZE,
		(uint8_t *)(&reg_val), REG_SIZE);
	if (g_visual)
		show_on_arena(arena, (MEM_SIZE + addr) % MEM_SIZE, REG_SIZE);
	sti_debug(arena, car, reg_val, args);
}
