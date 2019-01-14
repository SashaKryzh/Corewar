/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:00:12 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/11 17:00:12 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		zjmp_op(uint8_t *arena, t_car *car)
{
	int arg;

	if (!car->carry)
		return ;
	arg = get_value(arena, (car->position + 1) % MEM_SIZE, OP.t_dir_size);
	ft_printf("%d + %d = ", car->position, arg); //
	car->position = (MEM_SIZE + car->position + arg) % MEM_SIZE;
	ft_printf("%d\n", car->position); //
	car->no_jump = 1;
}
