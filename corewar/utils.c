/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:56:03 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/10 15:56:03 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

/*
**	Skips command with invalid args types or reg number
*/

void		skip_op(uint8_t *arena, t_carriage *car)
{
	int i;

	i = 0;
	ft_print_bits(arena[car->position + 1]);
	ft_printf(" - %d %d %d\n", car->args_sizes[0], car->args_sizes[1], car->args_sizes[2]);
	ft_printf("from: %d ", car->position);
	car->position += 1 + OP.is_args_types;
	while (i < g_op[car->op - 1].args_num)
	{
		car->position += car->args_sizes[i];
		i++;
	}
	car->position %= MEM_SIZE;
	ft_printf("to: %d\n", car->position);
}

/*
**	Sets the pointer on the first byte of needed arg
*/

uint8_t		*to_arg(uint8_t *arena, t_carriage *car, int arg_num)
{
	int i;
	int	to_jump;

	i = 0;
	to_jump = 1;
	while (i < arg_num - 1)
	{
		to_jump += car->args_sizes[i];
		i++;
	}
	to_jump++; // to got on the next byte
	// putbyte_hex(arena[(car->position + to_jump) % MEM_SIZE]); // points on ...
	return (&arena[(car->position + to_jump) % MEM_SIZE]);
}
