/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:36:29 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/11 13:36:29 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		fork_op(t_cell *arena, t_car *car)
{
	t_car	*new;
	int		where;

	where = get_value(arena, (car->position + 1) % MEM_SIZE, OP.t_dir_size);
	if (car->op == 0x0C)
		where %= IDX_MOD;
	new = (t_car *)ft_memalloc(sizeof(t_car));
	new->id = ++g_cnt_cars;
	new->carry = car->carry;
	new->last_live = car->last_live;
	new->position = (MEM_SIZE + car->position + where) % MEM_SIZE;
	ft_memcpy(new->regs, car->regs, sizeof(car->regs));
	new->next = g_carriage;
	g_carriage = new;
	// print_cars(g_carriage);
}
