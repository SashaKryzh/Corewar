/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_byte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:00:11 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/10 16:00:11 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

/*
**	Return id of needed reg, so you must do (num - 1) : 1 -> 0 for array of regs
*/

uint8_t		get_reg_num(uint8_t *arena, t_car *car, int arg_num)
{
	int i;
	int	to_jump;

	i = 0;
	to_jump = 1 + OP.is_args_types;
	while (i < arg_num - 1)
	{
		to_jump += car->args_sizes[i];
		i++;
	}
	return (arena[(car->position + to_jump) % MEM_SIZE]);
}

/*
**	Check for valid reg number
*/

static int	check_reg_num(uint8_t *arena, t_car *car, int arg_num)
{
	uint8_t		reg_num;

	reg_num = get_reg_num(arena, car, arg_num);
	// ft_printf("reg num: %d\n", reg_num); //
	if (reg_num <= 0 || reg_num > REG_NUMBER)
	{
		ft_printf("Invalid REG NUMBER\n");
		return (0);
	}
	return (1);
}

/*
**	Parses data from args type byte
**	(byte >> i) % 4 - take needed 2 bits in args byte
**	!(OP.args_types[j] >> ((byte >> i) % 4 - 1)) - dont remember how, but it checks if it is valid arg type
*/

int			get_op_data(uint8_t *arena, t_car *car)
{
	uint8_t		byte;
	uint8_t		i;
	uint8_t		j;
	uint8_t		ret;

	i = 6;
	j = -1;
	ret = 1;
	// arena[(car->position + 1) % MEM_SIZE] += 128; //
	// arena[(car->position + 1) % MEM_SIZE] -= 32; //
	byte = arena[(car->position + 1) % MEM_SIZE];
	ft_bzero(car->args_sizes, sizeof(car->args_sizes));
	while (++j < OP.args_num)
	{
		car->args_types[j] = (byte >> i) % 4;
		if (car->args_types[j] == IND_CODE)
			car->args_sizes[j] = IND_SIZE;
		else if (car->args_types[j] == DIR_CODE)
			car->args_sizes[j] = OP.t_dir_size;
		else if (car->args_types[j] == REG_CODE)
		{
			car->args_sizes[j] = 1;
			if (!check_reg_num(arena, car, j + 1))
				ret = 0;
		}
		if (!((OP.args_types[j] >> (car->args_types[j] - 1)) & 1))
		{
			ft_printf("Error in ARGS TYPES\n");
			ret = 0;
		}
		i -= 2;
	}
	return (ret);
}
