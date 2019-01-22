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
	int tmp;

	if (SHOW_OPERS && g_cnt_cycles >= g_start_to_show)
	{
		ft_printf(OPER_INFO);
		tmp = car->op == 0x0C ? where % IDX_MOD : where;
		tmp = car->position + tmp;
		ft_printf("%d (%d)\n", where, tmp);
	}
}

void		fork_op(t_cell *arena, t_car *car)
{
	t_car	*new;
	int		where;

	where = get_value(arena, (car->position + 1) % MEM_SIZE, OP.t_dir_size);
	fork_debug(car, where);
	if (car->op == 0x0C)
		where %= IDX_MOD;
	new = (t_car *)ft_memalloc(sizeof(t_car));
	ft_memcpy(new, car, sizeof(t_car));
	new->id = ++g_cnt_cars;
	new->position = (MEM_SIZE + (new->position + where) % MEM_SIZE) % MEM_SIZE;
	new->next = g_carriage;
	g_carriage = new;
}
