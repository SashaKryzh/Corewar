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

void		fork_debug(t_car *car, int where)
{
	if (SHOW_OPERS)
	{
		ft_printf(OPER_INFO);
		ft_printf("%d (%d)\n", where, car->position + where);
	}
}

void		fork_op(t_cell *arena, t_car *car)
{
	t_car	*new;
	int		where;

	where = get_value(arena, (car->position + 1) % MEM_SIZE, OP.t_dir_size);
	if (car->op == 0x0C)
		where %= IDX_MOD;
	fork_debug(car, where);
	new = (t_car *)ft_memalloc(sizeof(t_car));
	ft_memcpy(new, car, sizeof(t_car));
	new->id = ++g_cnt_cars;
	new->position = (MEM_SIZE + car->position + where) % MEM_SIZE;
	new->next = g_carriage;
	g_carriage = new;
}
