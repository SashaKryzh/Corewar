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

void		skip_op(t_car *car)
{
	int i;

	i = 0;
	if (car->no_jump)
	{
		car->no_jump = 0;
		return ;
	}
	car->position += 1 + (OP.is_args_types ? 1 : OP.t_dir_size);
	while (i < OP.args_num && OP.is_args_types)
	{
		car->position += car->args_sizes[i];
		i++;
	}
	car->position %= MEM_SIZE;
}

/*
**	Sets the pointer on the first byte of needed arg
**	Use it only when args type byte is there, otherwise do position + 1
*/

int			to_arg(t_car *car, int arg_num)
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
	to_jump++;
	return ((car->position + to_jump) % MEM_SIZE);
}

/*
**	Puts bytes on arena
*/

void		put_on_arena(t_cell *arena, int start, uint8_t *val, int s_c[2])
{
	int i;

	i = 0;
	while (i < s_c[0])
	{
		arena[(start + i) % MEM_SIZE].v = val[i];
		arena[(start + i) % MEM_SIZE].id = s_c[1];
		i++;
	}
}
