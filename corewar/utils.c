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

void		skip_op(t_cell *arena, t_car *car)
{
	int i;

	i = 0;
	if (car->no_jump)
	{
		car->no_jump = 0;
		return ;
	}
	ft_printf("id: %d, args type byte: ", car->id);
	ft_print_bits(arena[car->position + 1].v);
	ft_printf(" - %d %d %d -> ", car->args_sizes[0], car->args_sizes[1], car->args_sizes[2]);
	ft_printf("from: %d ", car->position);
	car->position += 1 + (OP.is_args_types ? 1 : OP.t_dir_size);
	while (i < OP.args_num && OP.is_args_types)
	{
		car->position += car->args_sizes[i];
		i++;
	}
	car->position %= MEM_SIZE;
	ft_printf("to: %d -> ", car->position);
	putbyte_hex(arena[car->position].v);
	ft_printf("\n");
}

/*
**	Sets the pointer on the first byte of needed arg
**	Use it only when args type byte is there, otherwise do position + 1 
*/

int			to_arg(t_cell *arena, t_car *car, int arg_num)
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
	return ((car->position + to_jump) % MEM_SIZE);
}

/*
**	Puts bytes on arena
*/

void		put_on_arena(t_cell *arena, int start, uint8_t *val, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		arena[(start + i) % MEM_SIZE].v = val[i];
		i++;
	}
}
