/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:40:20 by okryzhan          #+#    #+#             */
/*   Updated: 2019/01/11 14:40:20 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void		live_debug(t_car *car, int arg)
{
	if (SHOW_OPERS && g_cnt_cycles >= g_start_to_show)
	{
		ft_printf(OPER_INFO);
		ft_printf("%d\n", arg);
	}
}

void		live_op(t_cell *arena, t_car *car)
{
	int arg;

	arg = get_value(arena, (car->position + 1) % MEM_SIZE, OP.t_dir_size);
	if (arg < 0 && ft_abs(arg) <= g_cnt_players)
		g_last_alive = ft_abs(arg);
	car->last_live = g_cnt_cycles;
	g_cnt_live++;
	live_debug(car, arg);
}
