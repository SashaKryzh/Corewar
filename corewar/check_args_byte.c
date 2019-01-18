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
**	Check for arg type
*/

static int	is_ok_arg_type(t_car *car, int j, int ret)
{
	if (!((OP.args_types[j] >> (car->args_types[j] - 1)) & 1))
		ret = 0;
	return (ret);
}

/*
**	Check for valid reg number
*/

static int	check_reg_num(t_cell *arena, t_car *car, int arg_num, int ret)
{
	uint8_t		reg_num;

	reg_num = get_reg_num(arena, car, arg_num);
	if (reg_num <= 0 || reg_num > REG_NUMBER)
		ret = 0;
	return (ret);
}

/*
**	Parses data from args type byte
**	(byte >> i) % 4 - take needed 2 bits in args byte
*/

static void	init_local(int *i, int *j, int *ret)
{
	*i = 6;
	*j = -1;
	*ret = 1;
}

int			get_op_data(t_cell *arena, t_car *car)
{
	uint8_t		byte;
	int			i;
	int			j;
	int			ret;

	init_local(&i, &j, &ret);
	byte = arena[(car->position + 1) % MEM_SIZE].v;
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
			ret = check_reg_num(arena, car, j + 1, ret);
		}
		ret = is_ok_arg_type(car, j, ret);
		i -= 2;
	}
	return (ret);
}
